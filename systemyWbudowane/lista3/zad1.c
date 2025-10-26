#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// buzzer
#define BUZ_DDR DDRD 
#define BUZ_PORT PORTD
#define BUZ PD2

// nuty oktawa 4 
#define C 262
#define D 294
#define E 330
#define F 349
#define G 392
#define A 440 
#define B 494
#define PAUSE 0

// długości
#define BPM 120 
#define WHOLE   (60000U * 4 / BPM)
#define HALF    (60000U * 2 / BPM)
#define QUARTER (60000U / BPM)
#define EIGTH   (30000U / BPM)

// nuty
typedef struct {
    uint16_t freq;
    uint16_t dur;
} Note;

// melodia
const Note melody[] PROGMEM = {
    {C, QUARTER}, {D, QUARTER}, {E, QUARTER}, {F, QUARTER}, {G, QUARTER}, {A, QUARTER}, {B, QUARTER}, {PAUSE, HALF},
    {B, QUARTER}, {A, QUARTER}, {G, QUARTER}, {F, QUARTER}, {E, QUARTER}, {D, QUARTER}, {C, QUARTER}, {PAUSE, HALF},
};

const uint8_t MELODY_LEN = sizeof(melody) / sizeof(melody[0]);
void delay(uint32_t t) {
    for(; t; t--) {
        _delay_us(1);
    }
}

void play_melody_note(const uint8_t idx) {
    const uint16_t freq = pgm_read_word(&melody[idx].freq); 
    const uint16_t dur = pgm_read_word(&melody[idx].dur); 

    const uint32_t half_period = 500000 / freq; // mikrosekundy
    const uint32_t cycles = ((uint32_t)dur * 1000) / (half_period * 2);

    for(uint32_t i = 0; i < cycles; i++) {
        BUZ_PORT |= _BV(BUZ);
        delay(half_period);
        BUZ_PORT &= ~_BV(BUZ);
        delay(half_period);
    }
}

int main() {
    BUZ_DDR |= _BV(BUZ);    // output
    BUZ_PORT &= ~_BV(BUZ);  // low
    
    uint8_t idx = 0;
    while(1) {
        play_melody_note(idx);

        idx++;
        if(idx >= MELODY_LEN) idx = 0;
    }
}
