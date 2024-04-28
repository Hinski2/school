//zad2
#include <stdio.h>
#include <stdint.h>

//hamming weight algorithm
int main(){
    const uint64_t m1  = 0x5555555555555555; //binary: 0101...
    const uint64_t m2  = 0x3333333333333333; //binary: 00110011..
    const uint64_t m4  = 0x0f0f0f0f0f0f0f0f; //binary:  4 zeros,  4 ones ...
    const uint64_t m8  = 0x00ff00ff00ff00ff; //binary:  8 zeros,  8 ones ...
    const uint64_t m16 = 0x0000ffff0000ffff; //binary: 16 zeros, 16 ones ...
    const uint64_t m32 = 0x00000000ffffffff; //binary: 32 zeros, 32 ones

    uint64_t x; scanf("%ld", &x);
    x |= (x >> 1);
    x |= (x >> 2);
    x |= (x >> 4);
    x |= (x >> 8);
    x |= (x >> 16);
    x |= (x >> 32);

    x = ~x;

    x = (x & m1) + ((x >> 1) & m1); // Sumowanie 2 bitowch bloków
    x = (x & m2) + ((x >> 2) & m2); // Sumowanie 4 bitowych bloków
    x = (x & m4) + ((x >> 4) & m4); // Sumowanie 8 bitowych bloków
    x = (x & m8) + ((x >> 8) & m8); // Sumowanie 16 bitowych bloków
    x = (x & m16) + ((x >> 16) & m16); // Sumowanie 32 bitowych bloków
    x = (x & m32) + ((x >> 32) & m32);

    return  
}

/* 
    0101 1011 91    x
    0101 0110 86    suma na 2 bitach
    0010 0011 35    suma na 4 bitach
    0000 0101 5     suma na 8 bitach 
*/

