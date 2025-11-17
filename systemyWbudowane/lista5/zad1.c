#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// led 
#define LED PD3
#define LED_DDR DDRD
#define LED_PORT PORTD

// btn
#define BTN PD2
#define BTN_DDR DDRD
#define BTN_PORT PORTD 
#define BTN_PINR PIND

// time
#define TICK_MS 10u
#define DEBOUNCE_TICKS 2u

// buf
#define BUF_SIZE 100u
static uint8_t buf[BUF_SIZE + 15];
static uint8_t buf_pos;


void init() {
    // led 
    LED_DDR |= _BV(LED); // output

    // btn 
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

    // buf 
    buf_pos = 0;
    for(uint8_t i = 0; i < BUF_SIZE; i++) buf[i] = 0;

    // counter1, ctc, top = 1249, prescaler 64, -> 100hz
    TCCR1B |= _BV(WGM12); // ctc, top in OCR1A
    TCCR1B |= _BV(CS11) | _BV(CS10); // preskaler 64
    OCR1A = 2499;

    TIMSK1 |= _BV(OCIE1A); // włącza przerwanie na compare match
    
    // sleep 
    set_sleep_mode(SLEEP_MODE_IDLE);
}

// tak samo jak w lista2::zad1
static uint8_t min(uint8_t a, uint8_t b) {
    return a < b ? a : b;
}

static uint8_t handle_button() {
    // 0 => naciśnięty
    static uint8_t last_pos = 1, acc_signals = 0;

    uint8_t pos = BTN_PINR & _BV(BTN);
    if(pos == last_pos && !pos) acc_signals = min(DEBOUNCE_TICKS, acc_signals + 1);
    else if(!pos) acc_signals = 1;
    else acc_signals = 0;

    buf[buf_pos++] = !(acc_signals == DEBOUNCE_TICKS);
    if(buf_pos >= BUF_SIZE) buf_pos -= BUF_SIZE;

    last_pos = pos;
    return !buf[buf_pos]; // stan z przed 1s {0 => nie naciśnięty, 1 => naciśnięty}
}

ISR(TIMER1_COMPA_vect) {
    uint8_t pressed = handle_button();
    if(pressed) LED_PORT |= _BV(LED);
    else LED_PORT &= ~_BV(LED);
}

int main() {
    init();
    sei(); // odblokowanie przerwań

    while(1) {
        sleep_mode();
    }
}
