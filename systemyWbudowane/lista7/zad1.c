// 24C04 ma 512 bajtów 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "i2c.h"

// uart 
#define BAUD 9600                          
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   

void init() {
    // uart 8n1, bez parity bit
    UBRR0 = UBRR_VALUE;                 // ustawienie Baud rate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // 8 bitów danych w ramce

    // i2c 
    i2cInit();
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = data;
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
    while (!(UCSR0A & _BV(RXC0)));
    return UDR0;
}

FILE uart_file;

// 0 => write, 1 => read
uint8_t eeprom_select(uint16_t addr, uint8_t rw) {
    uint8_t code = 0b10100000; // ustawienie device code 
    code |= ((addr >> 8) & 1) << 1; // ustawienie block
    code |= rw & 1; // ustawienie rw


    return code;
}

uint8_t read(uint16_t addr) {
    i2cStart();
    i2cSend(eeprom_select(addr, 0));
    i2cSend((uint8_t) addr);

    i2cStart();
    i2cSend(eeprom_select(addr, 1));
    uint8_t data = i2cReadNoAck();
    i2cStop();

    return data;
}

void write(uint16_t addr, uint8_t val) {
    i2cStart();
    i2cSend(eeprom_select(addr, 0));
    i2cSend((uint8_t) addr);
    i2cSend(val);
    i2cStop();
}

uint8_t equal_str(char* str, char* op_buff) {
    uint8_t i = 0;
    for(; str[i]; i++) {
        if(str[i] != op_buff[i]) return 0;
    }

    return op_buff[i] == '\0';
}

int main() {
    init();  

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    uint16_t addr;
    char op_buff[10];

    while(1) {
        for(int i = 0; i < 10; i++) op_buff[i] = '\0';
        scanf("%9s %"SCNu16, op_buff, &addr);
        printf("%s %"PRIu16" ", op_buff, addr);

        if(equal_str("read", op_buff)) {
            uint8_t data = read(addr);
            printf("\r\ndata = %"PRIu8"\r\n", data);

        } else if(equal_str("write", op_buff)) {
            uint8_t val;
            scanf("%"SCNu8, &val);
            printf("%"PRIu8"\r\n", val);

            write(addr, val);

        } else {
            printf("invalid op\r\n");
        }
    } 
}
