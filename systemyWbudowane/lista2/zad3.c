#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

// led d0 - d7
#define LED_DDR DDRD
#define LED_PORT PORTD

// btn d11 - d13
#define BTN_PINR PINB
#define BTN_PORT PORTB
#define BTN_DDR DDRB

// btn_rst d10
#define BTN_RST PB2

// btn_prev d11
#define BTN_PREV PB3

// btn_next d12
#define BTN_NEXT PB4


// time
#define TICK_MS 10u
#define DEBOUNCE_TICKS 2u

static uint8_t gray_code;
static uint8_t gray_encode(uint8_t n) {
    return n ^ (n >> 1);
}
static uint8_t gray_decode(uint8_t g) {
    uint8_t n = 0;
    for(; g; g /= 2)
        n ^= g;
    return n;
}

static void prev() {
    uint8_t n = gray_decode(gray_code);
    n--;
    gray_code = gray_encode(n);
}

static void next() {
    uint8_t n = gray_decode(gray_code);
    n++;
    gray_code = gray_encode(n);
}

static void reset() {
    gray_code = 0;
}

int main() {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);

    LED_DDR = 0xFF;  // output
    BTN_DDR = 0x00;  // input
    BTN_PORT = 0xFF; // pull up

    uint8_t last_state = 0xFF;
    while(1) {
        _delay_ms(TICK_MS);

        uint8_t state = BTN_PINR;
        uint8_t pressed = last_state & ~state;
        last_state = state;

        if(pressed & _BV(BTN_PREV)) {
            prev();
        } else if(pressed & _BV(BTN_NEXT)) {
            next();
        } else if(pressed & _BV(BTN_RST)) {
            reset();
        }

        LED_PORT = gray_code;
    }
}
