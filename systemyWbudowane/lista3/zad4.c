#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include <util/delay_basic.h>
#include <math.h>

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
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

#define R_FIXED 4400.0f
#define B 4000.0f 
#define T_0 298.15f
#define R_0 4560.f

float convert_to_c(float R_TERM) {
    float k = (B * T_0) / (B + T_0 * logf(R_TERM / R_0));
    return k - 273.15f;
}

int main()
{
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();

    while(1) {
        uint16_t adc = read_adc();
        if(adc == 0) {
            printf("poniżej zakresu\r\n");
            goto end;
        } else if (adc >= 1023) {
            printf("powyżej zakresu\r\n");
            goto end;
        }

        const float R_TERM = R_FIXED * ((float)adc / (1023.0f - (float)adc));
        float c = convert_to_c(R_TERM);
        printf("adc: %"PRIu16" temperatura: %.2f C\r\n", adc, c);
end:
        _delay_ms(1000);
    }
}
