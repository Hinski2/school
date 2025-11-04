#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>


uint16_t random() { // xorshift, [0, 359]
    static uint32_t state = 42;
    state ^= state << 13;
    state ^= state << 17;
    state ^= state >> 5;

    return state % 360;
}

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} Rgb;

void convert(uint16_t h, Rgb* rgb) {
    uint8_t rem = h % 60;
    h /= 60;

    uint8_t x = h & 1 ? 255u - (255u * rem + 30) / 60 : (255u * rem + 30) / 60;

    switch(h) {
        case 0: *rgb = (Rgb){255, x, 0}; break;
        case 1: *rgb = (Rgb){x, 255, 0}; break;
        case 2: *rgb = (Rgb){0, 255, x}; break;
        case 3: *rgb = (Rgb){0, x, 255}; break;
        case 4: *rgb = (Rgb){x, 0, 255}; break;
        case 5: *rgb = (Rgb){255, 0, x}; break;
    }
}

void set(int d, Rgb* rgb) {
    if(d < 0) d = 0;
    if(d > 255) d = 255;

    OCR1A = (uint16_t) rgb -> g * d / 255;
    OCR1B = (uint16_t) rgb -> r * d / 255;
    OCR2A = (uint16_t) rgb -> b * d / 255;
}

void timers_init() {
    DDRB |= _BV(PB1) | _BV(PB2) | _BV(PB3);
    
    // counter1: fast pwm 8bit, odwracalny, częstotliwość 16e6 / 1 * (1 + 255)
    TCCR1A =  _BV(COM1A1) | _BV(COM1A0); 
    TCCR1A |= _BV(COM1B1) | _BV(COM1B0); 
    TCCR1A |= _BV(WGM10); 
    TCCR1B = _BV(WGM12) | _BV(CS10); // preskaler 1

    // counter0: fast pwm, odwracalny: częstotliwość 16e6 / (1 * 256)
    TCCR2A = _BV(COM2A1) | _BV(COM2A0); 
    TCCR2A |= _BV(WGM21) | _BV(WGM20);
    TCCR2B = _BV(CS20); // preskaler 1
}

#define DELAY 50
int main() {
    timers_init();

    Rgb rgb;
    while(1) {
        uint16_t h = random();
        convert(h, &rgb);
        
        set(8, &rgb); _delay_ms(DELAY);
        set(12, &rgb); _delay_ms(DELAY);
        set(16, &rgb); _delay_ms(DELAY);
        set(24, &rgb); _delay_ms(DELAY);
        set(32, &rgb); _delay_ms(DELAY);
        set(48, &rgb); _delay_ms(DELAY);
        set(64, &rgb); _delay_ms(DELAY);
        set(96, &rgb); _delay_ms(DELAY);
        set(128, &rgb); _delay_ms(DELAY);
        set(192, &rgb); _delay_ms(DELAY);

        set(256, &rgb); _delay_ms(DELAY);

        set(192, &rgb); _delay_ms(DELAY);
        set(128, &rgb); _delay_ms(DELAY);
        set(96, &rgb); _delay_ms(DELAY);
        set(64, &rgb); _delay_ms(DELAY);
        set(48, &rgb); _delay_ms(DELAY);
        set(32, &rgb); _delay_ms(DELAY);
        set(24, &rgb); _delay_ms(DELAY);
        set(16, &rgb); _delay_ms(DELAY);
        set(12, &rgb); _delay_ms(DELAY);
        set(8, &rgb); _delay_ms(DELAY);
    }
}
