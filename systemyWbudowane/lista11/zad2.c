#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

void init() {
    // uart 
    UBRR0 = UBRR_VALUE; // ustaw baudrate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // ustaw format 8n1

    // adc
    ADMUX   = _BV(REFS0); // napięcie odniesienia AVcc, 
    DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0 i ADC1
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128 -> 16MHz / 128 = 125 kHz dla adc
    ADCSRA |= _BV(ADEN); // włącz ADC

    // timmer 1 phase and frequency correct, 1000Hz, top=ICR1, d=OCR1A
    DDRB |= _BV(PB1); // output
    TCCR1A |= _BV(COM1A1); // fast pwm non inverting
    TCCR1B |= _BV(WGM13); // pwm phase and frequency correct, top ICR1
    TCCR1B |= _BV(CS11); // preslaler 8
    ICR1 = 1000;    // f_cpu / (2 * 8 * ICR1) = 1000hz
    TIMSK1 = _BV(TOIE1); // przerwanie na bottom
    TIMSK1 |= _BV(ICIE1); // przerwanie na top
}

uint16_t read_adc(uint8_t i) {
    ADMUX = (i ? _BV(MUX1) : 0) | _BV(REFS0); // napięcie odniesiena AVcc + odpowiedni pin

    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

volatile uint16_t i_engine, v_engine;

// przerwanei na TOP, tranzystor wyłączony
ISR(TIMER1_CAPT_vect) {
    v_engine = read_adc(1);
}

// przerwanie na BOTTOM, tranzystor włączony
ISR(TIMER1_OVF_vect) {
    i_engine = read_adc(1); 
}

FILE uart_file;
int main() {
    init();
    sei();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    
    for(uint8_t i = 0;;i++) {
        cli();
        uint16_t adc = read_adc(0);
        uint16_t i_mv = (i_engine * 5000UL) / 1024;
        uint16_t v_mv = 5000UL - (v_engine * 5000UL) / 1024;
        sei();

        if(i == 4) {
            printf("predkosc: %d mV, moment: %d mV\r\n", v_mv, i_mv);
            i = 0;
        }

        OCR1A = (adc * 1000UL) / 1023;
        _delay_ms(100);
    }
}
