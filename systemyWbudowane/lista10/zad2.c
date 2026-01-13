#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.h"

const uint8_t custom_chars[] = {
    0x10,   // 16
    0x18,   
    0x1C,   
    0x1E, 
    0x1F,   // 16 + 8 + 4 + 2 + 1
};



void load_custom_chars() {
    LCD_WriteCommand(0x40); // set cgram adress to 0x40
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 8; j++)
            LCD_WriteData(custom_chars[i]);
    }

    LCD_WriteCommand(HD44780_DDRAM_SET);
}

void init() {
    LCD_Initialize();
    LCD_Clear();

    load_custom_chars();
}


int main() {
    init();

    for(;;) {
        for(int y = 0; y < 16; y++) {
            for(int i = 0; i < 5; i++) {
                LCD_GoTo(y, 0);
                LCD_WriteData(i);
                _delay_ms(100);
            }
        }

        LCD_Clear();
    }
}
