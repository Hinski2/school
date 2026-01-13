#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

void init() {
    // display 
    LCD_Initialize();
    LCD_Clear();

    // uart
    UBRR0 = UBRR_VALUE; // ustawienie baudrate
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   // włącz odbiornik i nadajnik
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01); // format 8n1
}

void clear_line(char *line) {
    for(int i = 0; i < 16; i++)
        line[i] = ' ';
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

int hd44780_transmit(char data, FILE *stream) {
    LCD_WriteData(data);
    return 0;
}

FILE hd44780_file;

int main() {
    init();

    fdev_setup_stream(&hd44780_file, hd44780_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &hd44780_file;

    LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
    LCD_GoTo(0, 0);

    char line[16] = {};
    uint8_t y = 0;

    while(1) {
        line[y] = getchar();
        printf("%c", line[y]);
        y++;

        if(y >= 16) {
            LCD_GoTo(0, 1);
            printf("%s", line);
            clear_line(line);

            LCD_GoTo(0, 0);
            printf("%s", line);

            y = 0;
            LCD_GoTo(0, 0);
        }
    }
}

