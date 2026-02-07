#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/sleep.h>
#include <math.h>
#include <stdlib.h>

///////// uart 
#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
FILE uart_file;

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

///////// adc  i timmer
// 50 ms
#define NO_SAMPLES 400
int16_t samples[NO_SAMPLES];
volatile uint16_t samples_idx = 0;
uint32_t sum = 0;
uint8_t data_ready = 0;

ISR(TIMER1_COMPA_vect) {
    ADCSRA |= _BV(ADIE); // przerwanie po obliczeniu adc
    ADCSRA |= _BV(ADSC); // zaczęcie liczenia adc
}

ISR(ADC_vect) {
    int16_t adc = ADC - 512;

    sum -= (int32_t) samples[samples_idx] * samples[samples_idx];
    samples[samples_idx] = adc;
    sum += (int32_t) adc * adc;

    samples_idx++;
    if(samples_idx >= NO_SAMPLES) {
        samples_idx = 0;
        data_ready = 1;
    }

    ADCSRA &= ~_BV(ADIE);
}

/////////
void init() {
    // uart 
    UBRR0 = UBRR_VALUE; // ustaw baudrate
    UCSR0A = 0; // wyczyść rejestr UCSR0A
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // ustaw format 8n1

    // adc 
    ADMUX = _BV(REFS0); // napięcie odniesienia AVcc, 
    ADMUX |= _BV(MUX0); // kałan adc1
    DIDR0 = _BV(ADC1D); // wyłącz wejście cyfrowe na ADC1
    ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128 -> 16MHz / 128 = 125 kHz dla adc
    ADCSRA |= _BV(ADEN); // włącz ADC

    // timmer 1 -> ctc 8khz
    TCCR1B = _BV(WGM12); // tryb 4 ctc
    OCR1A = 249; // top     f = f_cpu / 8(1 + ocr1a) = 8khz
    TIMSK1 |= _BV(OCIE1A); // przerwanie od porównania
    TCCR1B |= _BV(CS11); // preskaler 8


    // sleep
    set_sleep_mode(SLEEP_MODE_IDLE);
}


int main() {
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    init();
    sei();

    for(;;) {
        sleep_mode();

        if(data_ready) {
            data_ready = 0;
            
            cli();
            float curr_sum = sum;
            sei();
            
            int x = sqrtf(curr_sum / NO_SAMPLES);

            float db = 20.0 * log10(x / 363.0);
            int a = (int) db;
            int b = abs((int) ((db - a) * 100));

            printf("%d adc, %d.%d dBFS\r\n", x, a, b);
        }
    }
}
