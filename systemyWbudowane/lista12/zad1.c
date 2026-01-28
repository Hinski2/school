#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdio.h>
#include <stdlib.h>
#include "stdint.h"
#include "pid.h"

#define K_P     1.00
#define K_I     0.00
#define K_D     0.00

volatile struct GLOBAL_FLAGS {
  //! True when PID control loop should run one time
  uint8_t pidTimer:1;
  uint8_t dummy:7;
} gFlags = {0, 0};

struct PID_DATA pidData;
#define TIME_INTERVAL   157

volatile int16_t target;
volatile float currentTemperature = 0.0f;

//////////////////////////////////////////// uart jak w lista 6 zad 2

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define BUF_SIZE 10

volatile uint8_t rx_buf[BUF_SIZE], rx_buf_head, rx_buf_tail;
volatile uint8_t tx_buf[BUF_SIZE], tx_buf_head, tx_buf_tail;

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
    uint8_t next = tx_buf_head + 1;
    if(next >= BUF_SIZE) next -= BUF_SIZE;

    while(next == tx_buf_tail)
        continue; // pełny

    cli();
    tx_buf[tx_buf_head] = data;
    tx_buf_head = next;
    UCSR0B |= _BV(UDRIE0);

    sei();
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
    while(rx_buf_head == rx_buf_tail) 
        continue; // pusty
    
    cli();

    uint8_t data = rx_buf[rx_buf_tail++];
    if(rx_buf_tail >= BUF_SIZE) rx_buf_tail -= BUF_SIZE;
    UCSR0B |= _BV(RXCIE0); // buf nie jest pełny

    sei();
    return data;
}

// gdy dostaniemy ramke danych
ISR(USART_RX_vect) {
    uint8_t data = UDR0; 
    if(UCSR0A & _BV(FE0)) // frame error
        return;
    
    uint8_t next = rx_buf_head + 1;
    if(next >= BUF_SIZE) 
        next -= BUF_SIZE;

    rx_buf[rx_buf_head] = data;
    rx_buf_head = next;
    
    next++;
    if(next >= BUF_SIZE)
        next -= BUF_SIZE;

    if(next == rx_buf_tail) // pełny buf
        UCSR0B &= ~_BV(RXCIE0);
}

// gdy możemy wysłać dane
ISR(USART_UDRE_vect) {
    if(tx_buf_head == tx_buf_tail) { // nie ma nic do wysłania
        UCSR0B &= ~_BV(UDRIE0);
    } else {
        UDR0 = tx_buf[tx_buf_tail++];
        if(tx_buf_tail >= BUF_SIZE) 
            tx_buf_tail -= BUF_SIZE;
    }
}

void process_uart() {
    static char buf[10];
    static uint8_t buf_idx = 0;


    if(rx_buf_head == rx_buf_tail) return; // nic nie dostaliśmy

    char c = uart_receive(NULL);
    if('0' <= c && c <= '9' && buf_idx < 9) {
        buf[buf_idx++] = c;
    } else if(c == '\r' || c == '\n') {
        buf[buf_idx] = '\0';

        if(buf_idx) {
            target = atoi(buf);
            buf_idx = 0;
        }
    }
}

//////////////////////////////////////////// timer 0 

ISR(TIMER0_OVF_vect) {
    static uint16_t i = 0;
    if(i < TIME_INTERVAL) {
        i++;
    } else {
        gFlags.pidTimer = 1;
        i = 0;
    }
}

//////////////////////////////////////////// adc 

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

//////////////////////////////////////////// pid

int16_t Get_Reference(void) {
    return target;
}

int16_t Get_Measurement(void) {
    uint16_t adc = read_adc();
    float v = (float)adc * 1.1f / 1024.0f;
    currentTemperature = (v - 0.5f) * 100.0f;

    return (int16_t) currentTemperature;
}

void Set_Input(int16_t inputValue) {
  if(inputValue > 1023) inputValue = 1023;
  if(inputValue < 0) inputValue = 0;

  OCR1A = inputValue;
}

////////////////////////////////////////////

void init(void) {
    // uart 
    UBRR0 = UBRR_VALUE; // ustaw baudrate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // ustaw format 8n1
    UCSR0B |= _BV(RXCIE0);              // umozliwia przerwanie gdy RCX=1

    // adc
    ADMUX   = _BV(REFS0) | _BV(REFS1); // napięcie odniesienia 1.1V
    DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128 -> 16MHz / 128 = 125 kHz dla adc
    ADCSRA |= _BV(ADEN); // włącz ADC

    // timmer 1 phase and frequency correct, 1000Hz, top=ICR1, d=OCR1A
    DDRB |= _BV(PB1); // output
    TCCR1A |= _BV(COM1A1); // fast pwm non inverting
    TCCR1B |= _BV(WGM13); // pwm phase and frequency correct, top ICR1
    TCCR1B |= _BV(CS11); // preslaler 8
    ICR1 = 1023;    // f_cpu / (2 * 8 * ICR1) ~ 1000hz
    // TIMSK1 = _BV(TOIE1); // przerwanie na bottom
    // TIMSK1 |= _BV(ICIE1); // przerwanie na top
    
    // timer 0 dla pid: normal mode, ~1000hz
    TCCR0A = 0; // normal mode 
    TCCR0B = _BV(CS01) | _BV(CS00); // preskaler 64
    TIMSK0 = _BV(TOIE0); // prerwanie dla przepełnienia

    // pid
    pid_Init(K_P * SCALING_FACTOR, K_I * SCALING_FACTOR , K_D * SCALING_FACTOR , &pidData);
}

FILE uart_file;
int main(void) {
    init();
    sei();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    for(uint8_t cnt = 0;;) {
        if(gFlags.pidTimer) {
            int16_t ref = Get_Reference();
            int16_t meas = Get_Measurement();
            int16_t out = pid_Controller(ref, meas, &pidData);
            Set_Input(out);

            gFlags.pidTimer = 0;

            cnt++;
            if(cnt >= 10) {
                int t_int = currentTemperature;
                int t_frac = (currentTemperature - t_int) * 10; 

                printf("obecnie: %d.%d C; cel: %d; pwm: %d\r\n", t_int, t_frac, target, OCR1A);                
                cnt = 0;
            }
        }

        process_uart();
    }
}
