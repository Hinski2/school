#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

// led d13
#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

// btn d2
#define BTN PD2
#define BTN_DDR DDRD
#define BTN_PORT PORTD 
#define BTN_PINR PIND

// time
#define TICK_MS 10u
#define DEBOUNCE_TICKS 2u

// buf
#define BUF_SIZE 100u
static uint8_t buf[BUF_SIZE];
static uint8_t buf_pos;

static uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

static uint8_t handle_button() {
    // pos = 0 -> btn pressed
    static uint8_t last_pos = 1, acc_signals = 0;

    uint8_t pos = BTN_PINR & _BV(BTN);
    if(pos == last_pos && !pos) acc_signals = min(DEBOUNCE_TICKS, acc_signals + 1);
    else if(!pos) acc_signals += 1;
    else acc_signals = 0;

    buf[buf_pos++] = !(acc_signals == DEBOUNCE_TICKS);
    if(buf_pos >= BUF_SIZE) buf_pos -= BUF_SIZE;

    last_pos = pos;
    return !buf[buf_pos]; // if button was pressed 1s ago
}

int main() {
    LED_DDR |= _BV(LED);  // output
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

    while(1) {
        _delay_ms(TICK_MS);
        uint8_t pressed = handle_button();

        if(pressed) LED_PORT |= _BV(LED);
        else LED_PORT &= ~_BV(LED);
    }
}
