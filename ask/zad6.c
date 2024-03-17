#include <limits.h>
#include <stdint.h>
#include <stdio.h>

int main(){
    int32_t x = -7, y = -5;

    /* Zmiana znaku liczby `f` */
    int32_t mx = x ^ (1 << 31);

    /* Obliczenie `floor(log2(|f|))` dla `f` w postaci znormalizowanej */
    int32_t log2 = ((x >> 23) & 0xFF) - 127; //biore wykładnik 

    /* Zwróć wartość logiczną operacji `f == g` */
    int32_t equal = x == y;

    /*czy f < g*/
    uint32_t signX = x & (1 << 31); // Wyciągamy bit znaku f
    uint32_t signY = y & (1 << 31); // Wyciągamy bit znaku g
    uint32_t valueX = x & 0x7FFFFFFF; // Pozbywamy się bitu znaku f
    uint32_t valueY = y & 0x7FFFFFFF; // Pozbywamy się bitu znaku g

    uint32_t isFLessThanG = (signX & ~signY) | (~(signX ^ signY) & ((valueX - valueY) >> 31));
    //jeśli znak x to -, a y - -> true
    //jeśli znaki są takie same oraz x - y < 0
}