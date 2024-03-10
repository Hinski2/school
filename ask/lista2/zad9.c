#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(){
    int32_t x = -2;
    int32_t m1 = 0x55555555;
    int32_t m2 = 0x33333333;
    int32_t m4 = 0x0F0F0F0F;
    int32_t m8 = 0x00FF00FF;
    int32_t m16 = 0x0000FFFF;

    x = (x & m1) + ((x >> 1) & m1);
    x = (x & m2) + ((x >> 2) & m2);
    x = (x & m4) + ((x >> 4) & m4);
    x = (x & m8) + ((x >> 8) & m8);
    x = (x & m16) + ((x >> 16) & m16);

    printf("%d\n", x & 1);
}