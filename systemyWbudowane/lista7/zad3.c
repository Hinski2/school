#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

// uart 
#define BAUD 9600                          
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   


// transmisja jednego znaku
int uart_transmit(char data, FILE *stream) {
    while(!(UCSR0A & _BV(UDRE0)));
    UDR0 = data;
    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream) {
    while (!(UCSR0A & _BV(RXC0)));
    int data = UDR0;
    printf("%c", data);
    return data;
}

void init() {
    // uart 8n1, bez parity bit
    UBRR0 = UBRR_VALUE;                 // ustawienie Baud rate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // 8 bitów danych w ramce

    // i2c 
    i2cInit();
}

uint8_t get_op(uint16_t *day, uint16_t *month, uint16_t *year, uint16_t *hour, uint16_t *minute, uint16_t *second) {
    static char buff[10];
    scanf("%9s", buff);
    if(buff[0] == 'd') return 0;
    else if(buff[0] == 't') return 1;

    scanf("%9s", buff);
    if(buff[0] == 'd') {
        scanf("%"SCNu16"-%"SCNu16"-%"SCNu16, day, month, year);
        return 2;
    } else {
        scanf("%"SCNu16":%"SCNu16":%"SCNu16, hour, minute, second);
        return 3;
    }
}

#define W_MSG 0b11010000
#define R_MSG 0b11010001

#define SECOND_ADDR 0x00
#define MINUTE_ADDR 0x01
#define HOUR_ADDR 0x02

#define DAY_ADDR 0x04 
#define MONTH_ADDR 0x05
#define YEAR_ADDR 0x06

uint8_t bcd_decode(uint8_t bcd) {
    return (bcd >> 4) * 10 + (bcd & 0xF);
}

uint8_t bcd_encode(uint16_t num) {
    uint8_t x = 0;
    while(num >= 10) {
        num -= 10;
        x++;
    }

    return (x << 4) | num;
}

void get_time() {
    i2cStart();
    i2cSend(W_MSG);
    i2cSend(SECOND_ADDR);
    
    i2cStart();
    i2cSend(R_MSG);

    uint8_t sec_bcd = i2cReadAck();
    uint8_t min_bcd = i2cReadAck();
    uint8_t hour_bcd = i2cReadNoAck();

    i2cStop();

    uint8_t sec = bcd_decode(sec_bcd & 0x7F);
    uint8_t min = bcd_decode(min_bcd & 0x7F);
    uint8_t hour = bcd_decode(hour_bcd & 0x3F);

    printf("%02"PRIu8":%02"PRIu8":%02"PRIu8"\r\n", hour, min, sec);
}

void get_date() {
    i2cStart();
    i2cSend(W_MSG);
    i2cSend(DAY_ADDR);
    
    i2cStart();
    i2cSend(R_MSG);

    uint8_t day_bcd = i2cReadAck();
    uint8_t month_bcd = i2cReadAck();
    uint8_t year_bcd = i2cReadNoAck();

    i2cStop();
    
    uint8_t day = bcd_decode(day_bcd & 0x3F);
    uint8_t month = bcd_decode(month_bcd & 0x1F);
    uint16_t year = bcd_decode(year_bcd & 0xFF) + 2000u + (month_bcd >> 7) * 100;
    
    printf("%02"PRIu8"-%02"PRIu8"-%04"PRIu16"\r\n", day, month, year);
} 

void set_date(uint16_t day, uint16_t month, uint16_t year) {
    year -= 2000;
    uint8_t century = year >= 100;
    if(century) year -= 100;

    uint8_t day_bcd = bcd_encode(day);
    uint8_t month_bcd = bcd_encode(month) | (century << 7);
    uint8_t year_bcd = bcd_encode(year);

    i2cStart();
    i2cSend(W_MSG);
    i2cSend(DAY_ADDR);

    i2cSend(day_bcd);
    i2cSend(month_bcd);
    i2cSend(year_bcd);
    
    i2cStop();
}

void set_time(uint16_t hour, uint16_t minute, uint16_t second) {
    uint8_t sec_bcd = bcd_encode(second);
    uint8_t min_bcd = bcd_encode(minute);
    uint8_t hour_bcd = bcd_encode(hour);

    i2cStart();
    i2cSend(W_MSG);
    i2cSend(SECOND_ADDR);
    
    i2cSend(sec_bcd);
    i2cSend(min_bcd);
    i2cSend(hour_bcd);

    i2cStop();
}

FILE uart_file;
int main() {
    init();

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    uint16_t day, month, year, hour, minute, second;
    while(1) {
        uint8_t op = get_op(&day, &month, &year, &hour, &minute, &second);
        puts("\r\n");

        switch(op) {
            case 0: get_date(); break;
            case 1: get_time(); break; 
            case 2: set_date(day, month, year); break;
            case 3: set_time(hour, minute, second); break;
            default: printf("invalid op:");
        }
    }
}
