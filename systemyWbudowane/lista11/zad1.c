#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

void init() {

    // adc
    ADMUX   = _BV(REFS0); // napięcie odniesienia AVcc, 
    DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128 -> 16MHz / 128 = 125 kHz dla adc
    ADCSRA |= _BV(ADEN); // włącz ADC

    // timmer 1 fast pwm non inverting, 1000Hz, top=ICR1, d=OCR1A
    DDRB |= _BV(PB1); // output
    TCCR1A |= _BV(COM1A1); // fast pwm non inverting
    
    // top ICR1, fast pwm
    TCCR1A |= _BV(WGM11);
    TCCR1B |= _BV(WGM13) | _BV(WGM12);

    TCCR1B |= _BV(CS11); // preslaler 8
    ICR1 = 1999;    // F_pwm = F_cpu / 8 * (1 + ICR1) = 1000 Hz
}

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

int main() {
    init();
    
    for(;;) {
        uint16_t adc = read_adc();
        OCR1A = (adc * 1999UL) / 1023;

        _delay_ms(20);
    }
}
