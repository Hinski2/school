#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define LED_DDR DDRD
#define LED_PORT PORTD

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

    while(1) {
        for(uint8_t i = 0; i < 10; i++) {
            LED_PORT = digit[i];
            _delay_ms(1000);
        }
    }
}
