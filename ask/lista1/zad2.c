//zad2
#include <stdio.h>
#include <stdint.h>

//hamming weight algorithm
int main(){
    uint32_t x; scanf("%u", &x);

    uint32_t b1 = 0x55555555;
    uint32_t b2 = 0x33333333;
    uint32_t b4 = 0x0F0F0F0F;
    uint32_t b8 = 0x00FF00FF;
    uint32_t b16 = 0x0000FFFF;
    

    x = (x & b1) + ((x >> 1) & b1); // Sumowanie 2 bitowch bloków
    x = (x & b2) + ((x >> 2) & b2); // Sumowanie 4 bitowych bloków
    x = (x & b4) + ((x >> 4) & b4); // Sumowanie 8 bitowych bloków
    x = (x & b8) + ((x >> 8) & b8); // Sumowanie 16 bitowych bloków
    x = (x & b16) + ((x >> 16) & b16); // Sumowanie 32 bitowych bloków

    printf("%u\n", x);
}

/* 
    0101 1011 91    x
    0101 0110 86    suma na 2 bitach
    0010 0011 35    suma na 4 bitach
    0000 0101 5     suma na 8 bitach 
*/

