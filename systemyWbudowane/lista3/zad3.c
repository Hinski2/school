#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

// Led
#define LED PD2 
#define LED_PORT PORTD 
#define LED_DDR DDRD 

// inicjalizacja ADC
void adc_init()
{
    DIDR0 = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
    ADMUX = _BV(REFS0); // napięcie odniesienia vcc
    ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
    ADCSRA |= _BV(ADEN); // włącz ADC
}

uint16_t read_adc() {
    ADCSRA |= _BV(ADSC);
    while(ADCSRA & _BV(ADSC)); // gdy konwersja sie skończy mikrokontroler zeruej bit ADSC
    return ADC; // wynik 10-bitowy
}

uint8_t log_convert(uint16_t v) {
    if(v <= 200) return 0;
    if(v <= 400) return 1;
    if(v <= 600) return 2;
    if(v <= 800) return 3;
    if(v <= 1000) return 4;
    return 5;
}

// cykl = 2ms 
void delay_on(uint8_t idx) {
    switch(idx) {
        case 0: _delay_us(0); break;
        case 1: _delay_us(125); break;
        case 2: _delay_us(250); break;
        case 3: _delay_us(500); break;
        case 4: _delay_us(1000); break;
        case 5: _delay_us(2000); break;
    }
}

void delay_off(uint8_t idx) {
    switch(idx) {
        case 0: _delay_us(2000); break;
        case 1: _delay_us(1875); break;
        case 2: _delay_us(1750); break;
        case 3: _delay_us(1500); break;
        case 4: _delay_us(1000); break;
        case 5: _delay_us(0); break;
    }
}

int main() {
    adc_init();
    LED_DDR |= _BV(LED);

    while(1) {
        LED_PORT &= ~_BV(LED);
        uint16_t v = read_adc();
        uint8_t idx = log_convert(v);

        LED_PORT |= _BV(LED);
        delay_on(idx);
        
        LED_PORT &= ~_BV(LED);
        delay_off(idx);
    }
}
