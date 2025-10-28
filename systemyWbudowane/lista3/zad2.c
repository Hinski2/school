#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
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

// inicjalizacja ADC
void adc_init()
{
    DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
    ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

#define LED PD2
#define LED_DDR DDRD 
#define LED_PORT PORTD

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

int main() {
    uart_init();  
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    
    adc_init();
    
    LED_DDR |= _BV(LED);

    while(1) {
        _delay_ms(1000);

        LED_PORT &= ~_BV(LED);
        uint16_t adc_val = read_adc(); 
        LED_PORT |= _BV(LED);

        float vcc = 1.1f * 1023.0f / adc_val;
        printf("adc: %d  vcc:  %.2f V \r\n", adc_val, vcc);
    }
}
