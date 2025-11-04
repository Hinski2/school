#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}
FILE uart_file;

// dodaanie
uint16_t measure_i8a() {
    volatile int8_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a + b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i16a() {
    volatile int16_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a + b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i32a() {
    volatile int32_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a + b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i64a() {
    volatile int64_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a + b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_floata() {
    volatile float a = 2.0, b = 2.0;
    uint16_t t0 = TCNT1;

    a = a + b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

// mnożenie 
uint16_t measure_i8m() {
    volatile int8_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a * b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i16m() {
    volatile int16_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a * b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i32m() {
    volatile int32_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a * b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i64m() {
    volatile int64_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a * b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_floatm() {
    volatile float a = 2.0, b = 2.0;
    uint16_t t0 = TCNT1;

    a = a * b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}


// dzielenie 
uint16_t measure_i8d() {
    volatile int8_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a / b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i16d() {
    volatile int16_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a / b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i32d() {
    volatile int32_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a / b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_i64d() {
    volatile int64_t a = 2, b = 2;
    uint16_t t0 = TCNT1;

    a = a / b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

uint16_t measure_floatd() {
    volatile float a = 2.0, b = 2.0;
    uint16_t t0 = TCNT1;

    a = a / b;

    uint16_t t1 = TCNT1;
    return t1 - t0;
}

int main() {
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    timer1_init();
    
    printf("dodawanie:\r\n");
    // int8_t
    uint16_t i8c = measure_i8a();
    printf("int8_t: %"PRIu16"cykli\r\n", i8c);

    // int16_t 
    uint16_t i16c = measure_i16a();
    printf("int16_t: %"PRIu16"cykli\r\n", i16c);

    // int32_t
    uint16_t i32c = measure_i32a();
    printf("int32_t: %"PRIu16"cykli\r\n", i32c);

    // int64_t
    uint16_t i64c = measure_i64a();
    printf("int64_t: %"PRIu16"cykli\r\n", i64c);

    // float
    uint16_t floatc = measure_floata();
    printf("flaot: %"PRIu16"cykli\r\n", floatc);


    printf("mnożenie:\r\n");
    // int8_t
    i8c = measure_i8m();
    printf("int8_t: %"PRIu16"cykli\r\n", i8c);

    // int16_t 
    i16c = measure_i16m();
    printf("int16_t: %"PRIu16"cykli\r\n", i16c);

    // int32_t
    // i32c = measure_i32m();
    // printf("int32_t: %"PRIu16"cykli\r\n", i32c);
    
    // int64_t
    i64c = measure_i64m();
    printf("int64_t: %"PRIu16"cykli\r\n", i64c);
    
    // float
    floatc = measure_floatm();
    printf("flaot: %"PRIu16"cykli\r\n", floatc);


    printf("dzielenie:\r\n");
    // int8_t
    i8c = measure_i8d();
    printf("int8_t: %"PRIu16"cykli\r\n", i8c);

    // int16_t 
    i16c = measure_i16d();
    printf("int16_t: %"PRIu16"cykli\r\n", i16c);

    // int32_t
    i32c = measure_i32d();
    printf("int32_t: %"PRIu16"cykli\r\n", i32c);

    // int64_t
    i64c = measure_i64d();
    printf("int64_t: %"PRIu16"cykli\r\n", i64c);

    // float
    floatc = measure_floatd();
    printf("flaot: %"PRIu16"cykli\r\n", floatc);
}
