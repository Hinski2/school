#include <avr/io.h>
#include <avr/iotn84.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>

// btn a7
#define BTN PA7 
#define BTN_PORT PORTA
#define BTN_DDR DDRA 
#define BTN_PIN PINA

// led b2
#define LED PB2
#define LED_PORT PORTB
#define LED_DDR DDRB

// "spi"
#define SPI_DDR DDRA
#define SPI_PORT PORTA

#define MISO PA6
#define MOSI PA5
#define SCK PA4
#define CS PA3


void init() {
    LED_DDR |= _BV(LED);  // output
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

    SPI_DDR |= _BV(MOSI) | _BV(SCK) | _BV(CS); // output
    SPI_PORT |= _BV(MISO); // pull up
    SPI_PORT |= _BV(CS);  // zaczynamy w stanei wysokim
}

uint8_t spi_transfer(uint8_t data) {
    // załaduj dane do przesłania
    USIDR = data;
    // wyczyść flagę przerwania USI
    USISR = _BV(USIOIF);
    // póki transmisja nie została ukończona, wysyłaj impulsy zegara
    while (!(USISR & _BV(USIOIF))) {
        // wygeneruj pojedyncze zbocze zegarowe
        // zostanie wykonane 16 razy
        USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
    }
    // zwróć otrzymane dane
    return USIDR;

}

inline uint8_t handle_button() { // 1 wciśnięty
    return !(BTN_PIN & _BV(BTN));
}

int main() {
    init();    

    for(;;) {
        uint8_t attiny_btn = handle_button();
        
        // start transmisji
        SPI_PORT &= ~_BV(CS);
        uint8_t atmega_btn = spi_transfer(attiny_btn);
        SPI_PORT |= _BV(CS);

        if(atmega_btn == 1) LED_PORT |= _BV(LED);
        else LED_PORT &= ~_BV(LED);

        _delay_ms(10); // 10 ms
    }
}
