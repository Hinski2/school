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
void init() {
    // adc
    ADMUX = _BV(REFS0); // AVcc jako Aref
    ADMUX |= _BV(MUX3) | _BV(MUX2) | _BV(MUX1); // input 1.1V
    ADCSRA = _BV(ADEN); // włącz adc
    ADCSRA |= _BV(ADIE); // włązca przrwanie po konwersji
    ADCSRA |= _BV(ADPS2) | _BV(ADPS1); // preskaler 64

    // sleep 
    set_sleep_mode(SLEEP_MODE_ADC);
}

ISR(ADC_vect) {
}

void eco_test() {
    float sum = 0, sum2 = 0;
    uint16_t n = 100;

    for(uint16_t i = 0; i < n; i++) {
        ADCSRA |= _BV(ADSC);
        sleep_mode();

        float v = (1.1 * 1023) / ADC;
        sum += v;
        sum2 += v * v;
    } 

    float v_mean = sum / n;
    float v_var = sum2 / n - v_mean * v_mean;

    printf("tryb eco     średnia: %f, wariancja: %f\r\n", v_mean, v_var);
}

void dem_test() {
    float sum = 0, sum2 = 0;
    uint16_t n = 100;

    for(uint16_t i = 0; i < n; i++) {
        ADCSRA |= _BV(ADSC);
        while(ADCSRA & _BV(ADSC)) continue;

        float v = (1.1 * 1023) / ADC;
        sum += v;
        sum2 += v * v;
    } 

    float v_mean = sum / n;
    float v_var = sum2 / n - v_mean * v_mean;

    printf("tryb nie eco średnia: %f, wariancja: %f\r\n", v_mean, v_var);
}

int main() {
    init();
    uart_init();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    sei(); // odblokowanie przerwań
    while(1) {
        eco_test();
        _delay_ms(3000);
        dem_test();
        _delay_ms(3000);
    }
}
