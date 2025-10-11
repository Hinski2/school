//notatka: ctrl + a, k by zabić monitor

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>

#define LED PB2
#define LED_DDR DDRD
#define LED_PORT PORTD
#define BAUD 9600                          
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)
                                           
// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

FILE uart_file;
const char morse_code[][6] = {
    "01",
    "1000",  
    "1010",  
    "100",   
    "0",     
    "0010",  
    "110",   
    "0000",  
    "00",    
    "0111",  
    "101",   
    "0100",  
    "11",    
    "10",    
    "111",   
    "0110",  
    "1101",  
    "010",   
    "000",   
    "1",     
    "001",   
    "0001",
    "011",
    "1001",
    "1011", 
    "1100",
};

const int16_t DASH_DOT_DELAY = 100;
const int16_t CHAR_DELAY = 300;
const int16_t WORDS_DELAY = 700;
const int16_t LONG_BLINK = 700;
const int16_t SHORT_BLINK = 200;


void blink_short(void) {
    LED_PORT |= _BV(LED);
    _delay_ms(SHORT_BLINK);
    LED_PORT &= ~ _BV(LED);
}
void blink_long(void) {
    LED_PORT |= _BV(LED);
    _delay_ms(LONG_BLINK);
    LED_PORT &= ~ _BV(LED);
}

void handle_char(char c) {
    if(c == '\n' || c == ' ') {
        _delay_ms(WORDS_DELAY); 
        return;
    }

    if(c < 'a' || c > 'z') {
        return;
    }

    for(int8_t i = 0; morse_code[c - 'a'][i]; i++) {
        if(morse_code[c - 'a'][i] == '0') {
            blink_short();
        } else {
            blink_long();
        }
        
        _delay_ms(DASH_DOT_DELAY);
    }
    _delay_ms(CHAR_DELAY);
}

int main() {
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    
    printf("start mikrokontrolera\r\n");
    LED_DDR |= _BV(LED);
    while(1) {
        char c = '\n';
        scanf("%c", &c);
        handle_char(c);
    }
}
