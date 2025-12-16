#include <avr/io.h>
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

// buf
#define BUF_SIZE 100u
static uint8_t buf[BUF_SIZE];
static uint8_t buf_pos;


static uint8_t handle_button(void) {
    // pos = 0 -> wciśnięty btn
    static uint8_t last_pos = 1;

    uint8_t pos = BTN_PIN & _BV(BTN);
    buf[buf_pos++] = pos || last_pos;
    if(buf_pos >= BUF_SIZE) buf_pos -= BUF_SIZE;
    
    last_pos = pos;
    return !buf[buf_pos];
}

int main() {
    LED_DDR |= _BV(LED);  // output
    BTN_DDR &= ~_BV(BTN); // input
    BTN_PORT |= _BV(BTN); // pull up

    for(;;) {
        _delay_ms(10); // 10 ms
        uint8_t pressed = handle_button(); // zwraca stan z przed 1s i zapisuje stan obecny

        if(pressed) LED_PORT |= _BV(LED);
        else LED_PORT &= ~_BV(LED);
    }
}
