//zad3
#include <stdio.h>
#include <stdint.h>

// wyrównanie jest do długości słowa maszynowego 8 bajtów architektura 64 bitowa

struct A {
    int8_t a;   //1 bajt + 7 padding    offset 0
    void *b;    //8 bajtów              offset 8
    int8_t c;   //1 bajt                offset 16
    int16_t d;  //2 bajty + 5 padding   offset 17
};

struct A_optimized {
    void *b;    // 8 bajtów             offset 0
    int16_t d;  // 2 bajty              offset 8
    int8_t a;   // 1 bajt               offset 10
    int8_t c;   // 1 bajt + 4 padding   offset 11
};

struct B {
    uint16_t a; //2 bajty + 6 padding   offset 0
    double b;   //8 bajtów              offset 8
    void *c;    //8 bajtów              offset 16
};

struct B_optimized {
    double b;   // 8 bajtów             offset 0
    void *c;    // 8 bajtów             offset 8
    uint16_t a; // 2 bajty + 6 padding  offset 16
};

int main(){

    printf("rozmiar A i A_optimized: %lu, %lu\n", sizeof(struct A), sizeof(struct A_optimized));
    printf("rozmiar B i B_optimized: %lu, %lu\n", sizeof(struct B), sizeof(struct B_optimized));
}