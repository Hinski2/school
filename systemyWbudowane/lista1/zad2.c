#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD
#define DELAY 100

// DDRD - ustawia czy pin jest wejściem 0 czy wyjściem 1
// PORTD - ustawia stan logiczny wejści HIGH / LOW

void lr(void) {
    for(int8_t i = 0; i < 8; i++) {
        PORTD |= _BV(i);
        _delay_ms(DELAY);
        PORTD &= ~_BV(i);
    }
}

void rl(void) {
    for(int8_t i = 7; i >= 0; i--) {
        PORTD |= _BV(i);
        _delay_ms(DELAY);
        PORTD &= ~_BV(i);
    }
}

int main() {
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    LED_DDR = 0xFF; // ustawiamy wszystkie 8 pinów na wejście

    while (1) {
        lr();
        rl();
    }
}
