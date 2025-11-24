#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#define BUF_SIZE 10

volatile uint8_t rx_buf[BUF_SIZE], rx_buf_head, rx_buf_tail;
volatile uint8_t tx_buf[BUF_SIZE], tx_buf_head, tx_buf_tail;

void init()
{
    // uart 8n1, bez bitu parzystości 
    UBRR0 = UBRR_VALUE;
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // włącz odbiornik i nadajnik 
    UCSR0B |= _BV(RXCIE0);              // umozliwia przerwanie gdy RCX=1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // format 8n1

    // sleep
    set_sleep_mode(SLEEP_MODE_IDLE);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
    uint8_t next = tx_buf_head + 1;
    if(next >= BUF_SIZE) next -= BUF_SIZE;

    while(next == tx_buf_tail)
        continue; // pełny

    cli();
    tx_buf[tx_buf_head] = data;
    tx_buf_head = next;
    UCSR0B |= _BV(UDRIE0);

    sei();
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
    while(rx_buf_head == rx_buf_tail) 
        continue; // pusty
    
    cli();

    uint8_t data = rx_buf[rx_buf_tail++];
    if(rx_buf_tail >= BUF_SIZE) rx_buf_tail -= BUF_SIZE;
    UCSR0B |= _BV(RXCIE0); // buf nie jest pełny

    sei();
    return data;
}

// gdy dostaniemy ramke danych
ISR(USART_RX_vect) {
    uint8_t data = UDR0; 
    if(UCSR0A & _BV(FE0)) // frame error
        return;
    
    uint8_t next = rx_buf_head + 1;
    if(next >= BUF_SIZE) 
        next -= BUF_SIZE;

    rx_buf[rx_buf_head] = data;
    rx_buf_head = next;
    
    next++;
    if(next >= BUF_SIZE)
        next -= BUF_SIZE;

    if(next == rx_buf_tail) // pełny buf
        UCSR0B &= ~_BV(RXCIE0);
}

// gdy możemy wysłać dane
ISR(USART_UDRE_vect) {
    if(tx_buf_head == tx_buf_tail) { // nie ma nic do wysłania
        UCSR0B &= ~_BV(UDRIE0);
    } else {
        UDR0 = tx_buf[tx_buf_tail++];
        if(tx_buf_tail >= BUF_SIZE) 
            tx_buf_tail -= BUF_SIZE;
    }
}

FILE uart_file;
int main() {
    init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    printf("Hello world!\r\n");
    while(1) {
        long a = 1;
        scanf("%ld", &a);
        printf("Odczytano: %ld\r\n", a);
    }
}
