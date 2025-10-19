#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

// led 
#define LED_DDR DDRD
#define LED_PORT PORTD

// dig 
#define DIG_DDR DDRC 
#define DIG_PORT PORTC

// front_dig
#define FRONT_DIG PC0

// back_dig
#define  BACK_DIG PC1

// time 
#define REFRESH_MS 2u

const uint8_t digit[10] = {
    0b11000000,
    0b11111001, 
    0b10100100, 
    0b10110000, 
    0b10011001, 
    0b10010010, 
    0b10000010, 
    0b11111000, 
    0b10000000, 
    0b10010000,  
};

int main(void) {
    LED_DDR = 0xFF; 
    DIG_DDR |= _BV(FRONT_DIG) | _BV(BACK_DIG);
    DIG_PORT |= _BV(FRONT_DIG) | _BV(BACK_DIG);

    while(1) {
        for(uint8_t i = 0; i < 6; i++) {
            for(uint8_t j = 0; j < 10; j++) {

                for(uint16_t t = 1000; t >= 2 * REFRESH_MS; t -= 2 * REFRESH_MS) {
                    // left 
                    LED_PORT = digit[j];
                    DIG_PORT &= ~_BV(BACK_DIG);
                    DIG_PORT |= _BV(FRONT_DIG);
                    _delay_ms(REFRESH_MS); 

                    // right
                    LED_PORT = digit[i];
                    DIG_PORT &= ~_BV(FRONT_DIG);
                    DIG_PORT |= _BV(BACK_DIG);
                    _delay_ms(REFRESH_MS); 
                }
            }
        }
    }
}
