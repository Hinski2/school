// 24C04 ma 512 bajtów 

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
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

void read_seq(uint16_t addr, uint16_t len, uint8_t *buf) {
    i2cStart();
    i2cSend(eeprom_select(addr, 0));
    i2cSend((uint8_t) addr);
    
    i2cStart();
    i2cSend(eeprom_select(addr, 1));
    for(uint16_t i = 0; i < len - 1; i++) {
        buf[i] = i2cReadAck();
    }
    buf[len - 1] = i2cReadNoAck();
}

void write(uint16_t addr, uint8_t val) {
    i2cStart();
    i2cSend(eeprom_select(addr, 0));
    i2cSend((uint8_t) addr);
    i2cSend(val);
    i2cStop();
}

void write_seq(uint16_t addr, uint16_t len, uint8_t *buf) {
    uint8_t saved;

    for(uint16_t idx = 0; idx < len; idx += saved) {
        uint16_t rem_to_save = len - idx;
        uint16_t page_pos = addr & 0x0F;
        uint16_t page_left = 16 - page_pos;

        saved = rem_to_save > page_left ? page_left : rem_to_save;
        
        i2cStart();
        i2cSend(eeprom_select(addr, 0));
        i2cSend((uint8_t) addr);
        for(uint8_t i = 0; i < saved; i++)
            i2cSend(buf[idx + i]);
        
        i2cStop();
        _delay_ms(5);

        addr += saved;
        if(addr >= 512) addr -= 512;
    }
}

uint8_t equal_str(char* str, char* op_buff) {
    uint8_t i = 0;
    for(; str[i]; i++) {
        if(str[i] != op_buff[i]) return 0;
    }

    return op_buff[i] == '\0';
}

uint8_t hex_to_dec(char c) {
    if('0' <= c && c <= '9') return c - '0';
    return c - 'A' + 10;
}

uint8_t hex_byte(char *p) {
    return (hex_to_dec(p[0]) << 4) | hex_to_dec(p[1]);
}

/*
    0 => end. zmiena addr jeśli != 0xFF FF
    wiadomośc :[1-2 znaki][3-6 znaki adres][7-8 znaki typ][9-10 znaki dane][11-12 znaki checksum]
    praykłady:
        :02 0000 00 42 00
        :02 0001 00 42 00
        :00 0000 01 FF


:020000004200
:020001004200
:00000001FF
*/
uint8_t decode_hex(uint16_t *addr, uint8_t *data) {
    static char line[40];
    scanf("%39s", line);
    printf("%s\r\n", line);
    
    uint8_t type = hex_byte(line + 7);
    if(type == 0x01) return 0;

    if(*addr == 0xFFFF)
        *addr = ((uint16_t) hex_byte(line + 3) << 8) | hex_byte(line + 5);
    *data = hex_byte(line + 9);

    return 1;
}

void encode_hex(uint16_t addr, uint8_t data) {
    uint8_t len = 1;
    uint8_t type = 0x00; // dane

    uint8_t sum = 1;
    sum += addr >> 8;
    sum += addr & 0xFF;

    uint8_t check_sum = (uint8_t)(-sum);
    printf(":%02X %04X %02X %02X %02X\r\n", len, addr, type, data, check_sum);    
}

int main() {
    init();  

    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    char op_buff[10];
    uint8_t data_buf[512];

    while(1) {
        for(int i = 0; i < 10; i++) op_buff[i] = '\0';
        scanf("%9s", op_buff);
        printf("%s ", op_buff);

        if(equal_str("read", op_buff)) {
            uint16_t addr, len;
            scanf("%"SCNu16 " %"SCNu16, &addr, &len);
            printf("%"PRIu16 " %"PRIu16"\r\n", addr, len);
            
            if(len == 1) {
                uint8_t data = read(addr);
                encode_hex(addr, data);
            } else {
                read_seq(addr, len, data_buf);

                for(uint16_t i = 0; i < len; i++) {
                    encode_hex(addr, data_buf[i]);

                    addr++;
                    if(addr >= 512) addr -= 512;
                }
            }

        } else if(equal_str("write", op_buff)) {
            printf("\r\n");
            uint16_t addr = 0xFFFF, i = 0;
            uint8_t data;

            for(; decode_hex(&addr, &data); i++) {
                data_buf[i] = data;
            }

            write_seq(addr, i + 1, data_buf);

        } else {
            printf("invalid op\r\n");
        }
    } 
}
