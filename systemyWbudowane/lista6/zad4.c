#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>

#define MOSI PB3 
#define SCK PB5
#define LE PB1 
#define OE PB2 
#define DDR DDRB 
#define PORT PORTB

const uint8_t digit[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F,
};

void init() {
    DDR = _BV(MOSI) | _BV(SCK) | _BV(LE) | _BV(OE); // output

    // SPI
    SPCR = _BV(SPE);    // SPI enable
    SPCR |= _BV(MSTR);  // jesteśmy masterem
    SPCR |= _BV(SPR0);  // częstotoliwość f_osc / 16
}


void spi_transfer(uint8_t data) {
    SPDR = data;
    while(!(SPSR & _BV(SPIF)));

    PORT |= _BV(LE);
    PORT &= ~_BV(LE);
}

int main() {
    init();
    
    while(1) {
        for(uint8_t i = 0; i < 10; i++) {
            spi_transfer(digit[i]);
            _delay_ms(1000);
        }
    }
}
