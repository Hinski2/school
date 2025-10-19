#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

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

// led d13
#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

// btn d2
#define BTN PD2
#define BTN_DDR DDRD
#define BTN_PORT PORTD 
#define BTN_PINR PIND

// time
#define TICK_MS 10u         
#define DEBOUNCE_TICKS 2u

#define DASH_DELAY  25u     // 500 ms
#define CHARS_DELAY 50u     // 1s
#define WORDS_DELAY 199u    // 4s

// morse code 0 short 1 long
const uint8_t morse_code[] = {
    0b110,
    0b10001,
    0b10101,
    0b1001,
    0b10,
    0b10100,
    0b1011,
    0b10000,
    0b100,
    0b11110,
    0b1101,
    0b10010,
    0b111,
    0b101,
    0b1111,
    0b10110,
    0b11011,
    0b1010,
    0b1000,
    0b11,
    0b1100,
    0b11000,
    0b1110,
    0b11001,
    0b11101,
    0b10011
};

static uint16_t min(uint16_t a, uint16_t b) {
    return a < b ? a : b;
}

static char morse_to_char(uint8_t code) {
	for(uint8_t i = 0; i < 26; i++) {
		if(code == morse_code[i]) return 'a' + i;
	}

	return '?';
}

static uint8_t pressed() {
	// 0 = pressed
	uint8_t last_pos = BTN_PINR & _BV(BTN);
    _delay_ms(TICK_MS);
    uint8_t pos = BTN_PINR & _BV(BTN);

	return last_pos || pos;
}

static void blink_sort() {
    LED_PORT |= _BV(LED);
    _delay_ms(50);
    LED_PORT &= ~_BV(LED);
}

static void blink_long() {
    LED_PORT |= _BV(LED);
    _delay_ms(150);
    LED_PORT &= ~_BV(LED);
}


int main() {
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    LED_DDR |= _BV(LED);  // output
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

	uint16_t hold_ticks = 0, gap_ticks = 0;
    uint8_t code = 0, code_pos = 0;
    
    while(1) {
        _delay_ms(TICK_MS);
        uint8_t state = pressed(); // 0 = buttion is pressed

        if(!state) {
            hold_ticks = min(hold_ticks + 1, 200);
            gap_ticks = 0;

            if(hold_ticks > DASH_DELAY)
                LED_PORT |= _BV(LED);
        } else {
            LED_PORT &= ~_BV(LED);

            if(hold_ticks) {
                if(hold_ticks >= DASH_DELAY) code |= (1u << code_pos);
                if(code_pos < 7) code_pos++;

                hold_ticks = 0;
            }

            gap_ticks = min(gap_ticks + 1, 200);
            if(gap_ticks == CHARS_DELAY) {
                if(code_pos) putchar(morse_to_char(code | (1 << code_pos)));
                code = code_pos = 0;
                blink_sort();
            } else if(gap_ticks == WORDS_DELAY) {
                putchar(' ');
                blink_long();
            }
        }
    }
}
