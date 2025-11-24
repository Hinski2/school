#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdint.h>

// uart 
#define BAUD 9600                          
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   

void init() {
    // uart 8n1, bez parity bit
    UBRR0 = UBRR_VALUE;                 // ustawienie Baud rate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // włącz odbiornik i nadajnik
    UCSR0B |= _BV(RXCIE0);              // umozliwia przerwanie gdy RCX=1
    UCSR0B |= _BV(UDRIE0);              // umożliwia przerwanie gdy UDRE=1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // 8 bitów danych w ramce

    // sleep mode
    set_sleep_mode(SLEEP_MODE_IDLE);
}

volatile uint8_t rx_data, rx_ready;
volatile uint8_t tx_ready = 1;
void uart_send(uint8_t data) {
    tx_ready = rx_ready = 0;
    UDR0 = data;
}

ISR(USART_RX_vect) {    // przyszła nowa ramka danych
    if(UCSR0A & _BV(FE0)) return; // frame error

    rx_data = UDR0;
    rx_ready = 1;
}

ISR(USART_UDRE_vect) {  // można wypisać ramke danych
    tx_ready = 1; 
}

int main() {
    init(); 
    sei();
    
    while(1) {
        sleep_mode();

        if(rx_ready && tx_ready) {
            cli();
            uart_send(rx_data);
            sei();
        }
    }
}
