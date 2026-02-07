#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdio.h>
#include <avr/sleep.h>

#define IO PB5
#define IO_PORT PORTB
#define IO_DDR DDRB

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
uint16_t adc1, adc2;
uint16_t read_adc(uint8_t i) {
    ADMUX = (i == 1 ? _BV(MUX0) : _BV(MUX1)) | _BV(REFS0);

    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

ISR(TIMER1_COMPA_vect) {
    adc1 = read_adc(1);
    adc2 = read_adc(2);
}

/////////
void init() {
    // io
    IO_DDR |= _BV(IO); // output

    // uart 
    UBRR0 = UBRR_VALUE; // ustaw baudrate
    UCSR0A = 0; // wyczyść rejestr UCSR0A
    UCSR0B = _BV(RXEN0) | _BV(TXEN0); // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // ustaw format 8n1

    // adc 
    ADMUX = _BV(REFS0); // napięcie odniesienia AVcc, 
    DIDR0 = _BV(ADC1D) | _BV(ADC2D); // wyłącz wejście cyfrowe na ADC1 i ADC2
    ADCSRA = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128 -> 16MHz / 128 = 125 kHz dla adc
    ADCSRA |= _BV(ADEN); // włącz ADC

    // timmer 1 -> ctc 1hz
    TCCR1B = _BV(WGM12); // tryb 4 ctc
    OCR1A = 15624 ; // top     f = f_cpu / 1024(1 + ocr1a) = 1hz
    TIMSK1 |= _BV(OCIE1A); // przerwanie od porównania
    TCCR1B |= _BV(CS10) | _BV(CS12); // preskaler 1024

    // sleep
    set_sleep_mode(SLEEP_MODE_IDLE);
}


int main() {
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    init();
    sei();

    for(int i = 0;;) {
        sleep_mode();

        if(i == 0) {
            IO_PORT &= ~_BV(IO);
            printf("IO_PORT: 0, adc1: %d, adc2 %d \r\n", adc1, adc2);
        } else {
            IO_PORT |= _BV(IO);
            printf("IO_PORT: 1, adc1: %d, adc2 %d \r\n", adc1, adc2);
        }
        
        i = i ? 0 : 1;
    }
}
