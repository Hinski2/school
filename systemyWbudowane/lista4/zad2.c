#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

// inicjalizacja ADC
void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}


void timer1_init() { 
    // fast pwm, top = ICR1, nie odwracalny
    TCCR1A = _BV(COM1B1) | _BV(WGM11); 
    TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10);

    DDRB |= _BV(PB2);
    ICR1 = 1024; // top
}

////////// debug (jednak działa tylko trzeba mocniejsze światło dać )
#include <stdio.h>
#include <inttypes.h>
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

FILE uart_file;

////////

uint16_t scale(int16_t x) {
    x = 2 * x - (int32_t) x * (x - 256) * (x - 512) / 98304;

    if(x >= 1023) return 1023;
    if(x < 0) return 0;

    return x;
}

int main() {
    adc_init();
    timer1_init();

    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    while(1) {
        uint16_t adc = read_adc(); // [0, 1023]
        uint16_t x = scale(adc);

        printf("adc: %"PRIu16" x: %"PRIu16"\r\n", adc, x);
        
        OCR1B = (uint32_t) x * ICR1 / 1023;

        _delay_ms(100);
    }
}
