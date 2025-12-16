#include <avr/io.h>
#include <util/delay.h>

// LED
#define LED PD3
#define LED_DDR DDRD 
#define LED_PORT PORTD

// BTN
#define BTN PD2 
#define BTN_DDR DDRD
#define BTN_PORT PORTD
#define BTN_PIN PIND

// SPI
#define SPI_PORT PORTB
#define SPI_DDR DDRB 

#define MOSI PB3
#define MISO PB4
#define SCK PB5
#define CS PB2

void init() {
    LED_DDR |= _BV(LED);  // output
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up


    // SPI 
    SPI_DDR |= _BV(MISO); // output reszta input
    SPCR = _BV(SPE);    // SPI enable
}

uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while(!(SPSR & _BV(SPIF)));

    return SPDR;
}

inline uint8_t handle_button() { // 1 wciśnięty
    return !(BTN_PIN & _BV(BTN));
}

int main() {
    init();

    for(;;) {
        uint8_t atmega_btn = handle_button();
        
        // odbiór transmisji
        uint8_t attiny_btn = spi_transfer(atmega_btn);

        if(attiny_btn) LED_PORT |= _BV(LED);
        else LED_PORT &= ~_BV(LED);
    }
}
