#include <avr/io.h>
#include <util/delay.h>

#define LED PD2
#define LED_DDR DDRD
#define LED_PORT PORTD

// PD2 - oznazca port D z numerem bitu 2
// DDRD - ustawia czy pine jest wejściem 0 czy wyjściem 1
// PORTD - ustawia stan logiczny wejści HIGH / LOW

int main() {
  LED_DDR |= _BV(LED); // ustaw ustaw pin D z bitem 2 jako wyjście
  while (1) {
    LED_PORT |= _BV(LED); // daj HIGH 
    _delay_ms(500);
    LED_PORT &= ~_BV(LED); // daj LOW
    _delay_ms(500);
  }
}
