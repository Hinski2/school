#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <avr/sleep.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// uart
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

// oczekiwanie na zakończenie transmisji
void uart_wait()
{
  while(!(UCSR0A & _BV(TXC0)));
}

FILE uart_file;

// btn
#define BTN PD2
#define BTN_DDR DDRD
#define BTN_PORT PORTD 
#define BTN_PINR PIND

void init() {
    // btn 
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

    // counter1, ctc, top = 15 624, prescaler 1024, -> 1hz
    TCCR1B = _BV(WGM12); // ctc, top in OCR1A
    TCCR1B |= _BV(CS12) | _BV(CS10); // preskaler 1024
    OCR1A = 15624u;

    TIMSK1 = _BV(OCIE1A); // włącza przerwanie na compare match
    
    // adc
    ADMUX = _BV(REFS0); // napięcie odniesienia A_VCC 
    ADMUX |= _BV(MUX2) | _BV(MUX0); // wybór kanału adc5
                                    
    ADCSRA = _BV(ADEN); // adc enable
    // ADCSRA |= _BV(ADATE); // automatyczna konwersja na podstawie ADCSRB
    
    // ADCSRB = _BV(ADTS1); // autmatycznak konwersja na INT0
   
    // int 
    EICRA = _BV(ISC01); // fala opadająca generuje INT0
    EIMSK = _BV(INT0); // odblokowanie INT0

    // sleep 
    set_sleep_mode(SLEEP_MODE_IDLE);
}

volatile uint16_t last_adc;
volatile uint32_t r_1;
volatile uint8_t print_r;

ISR(INT0_vect) {
    ADCSRA |= _BV(ADIE); // umożliwienie przerwań
    ADCSRA |= _BV(ADSC); // konwersja
}

ISR(TIMER1_COMPA_vect) { 
    r_1 = (uint32_t) 10000u * (1023 - last_adc) / last_adc;
    print_r = 1;
}

ISR(ADC_vect) {
    last_adc = ADC;
    ADCSRA &= ~_BV(ADIE); // wyłącznie przerwań
}

int main() {
    init();
    uart_init();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    sei(); // odblokowanie przerwań
    while(1) {
        sleep_mode();

        cli();
        if(print_r) {
            printf("resyztancja: %lu\r\n", r_1);
            print_r = 0;
        }
        sei();
    }
}
