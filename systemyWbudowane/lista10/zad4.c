#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>

#include "dzwiek.c"

// MOSI, SCK, CS
#define MOSI PB3
#define SCK PB5
#define CS PB2
#define DDR DDRB 
#define PORT PORTB

void init() {
    DDR = _BV(MOSI) | _BV(SCK) | _BV(CS); // output

    // SPI 
    SPCR = _BV(SPE);    // SPI enable
    SPCR |= _BV(MSTR);  // jesteśmy masterem
    SPCR |= _BV(SPR0);  // częstotoliwość f_osc / 16
}

void spi_transfer(uint8_t data) {
    SPDR = data;
    while(!(SPSR & _BV(SPIF)));
}

void dac_write(uint8_t data) {
    uint16_t msg = (0x3 << 12) | ((uint16_t) data << 4);

    PORT &= ~_BV(CS);
    spi_transfer(msg >> 8 & 0xFF);
    spi_transfer(msg & 0xFF);
    PORT |= _BV(CS);
}

int main() {
    init();

    while(1) {
        for(uint16_t i = 0; i < dzwiek_raw_len; i++) {
            uint8_t data = pgm_read_byte(&dzwiek_raw[i]);
            dac_write(data);
            _delay_us(125); // 8kHz
        }
        _delay_ms(750);
    }
}
