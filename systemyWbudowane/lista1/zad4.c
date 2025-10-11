#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

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

int main() {
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    // int8_t
    int8_t a8, b8;
    scanf("%" SCNd8 " %" SCNd8, &a8, &b8);
    printf("dodawanie %" SCNd8 "\r\n", a8 + b8);
    printf("mnożenie %" SCNd8 "\r\n", a8 * b8);
    printf("dzielenie %" SCNd8 "\r\n", a8 / b8);
    
    // int16_t
    int16_t a16, b16;
    scanf("%" SCNd16 " %" SCNd16, &a16, &b16);
    printf("dodawanie %" SCNd8 "\r\n", a16 + b16);
    printf("mnożenie %" SCNd8 "\r\n", a16 * b16);
    printf("dzielenie %" SCNd8 "\r\n", a16 / b16);
    
    // int32_t
    int32_t a32, b32;
    scanf("%" SCNd32 " %" SCNd32, &a32, &b32);
    printf("dodawanie %" SCNd32 "\r\n", a32 + b32);
    printf("mnożenie %" SCNd32 "\r\n", a32 * b32);
    printf("dzielenie %" SCNd32 "\r\n", a32 / b32);

    // int64_t
    int32_t a32temp, b32temp;
    scanf("%" SCNd32 " %" SCNd32, &a32temp, &b32temp);
    int64_t a64 = (int64_t) a32temp, b64 = (int64_t) b32temp;

    printf("dodawanie %" SCNd32 "\r\n", (int32_t)(a64 + b64));
    printf("mnożenie %" SCNd32 "\r\n", (int32_t)(a64 * b64));
    printf("dzielenie %" SCNd32 "\r\n", (int32_t)(a64 / b64));
    
    // float
    float af, bf;
    scanf("%f %f", &af, &bf);
    printf("dodawanie %f\r\n", af + bf);
    printf("mnożenie %f\r\n", af * bf);
    printf("dzielenie %f\r\n", af / bf);
}
