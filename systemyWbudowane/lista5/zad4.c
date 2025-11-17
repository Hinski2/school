#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <avr/sleep.h>
#include <stdint.h>
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

void init() {
    // counter1, normal mode
    TCCR1B = _BV(ICES1); // input capture na rising edge
    TCCR1B |= _BV(CS12); // preskaler 256

    TIMSK1 = _BV(ICIE1); // włączenie przerwania input capture
    TIMSK1 |= _BV(TOIE1); // włącza przrwanei na overflow
    
    // sleep 
    set_sleep_mode(SLEEP_MODE_IDLE);
}

volatile uint32_t f;
ISR(TIMER1_CAPT_vect) {
    static uint16_t last = 0;
    uint16_t now = ICR1;
    
    if(last) {
        uint16_t diff = now - last;
        f = 62500ul / diff;
    }

    last = now;
}

ISR(TIMER1_OVF_vect) {
    printf("f: %ld\r\n", f);
}

int main() {
    init();
    uart_init();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    sei(); // odblokowanie przerwań
    while(1) {
        sleep_mode();
    }
}
