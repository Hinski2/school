// zad1
#include <stdio.h>
#include <stdint.h>

int main(){
    uint32_t x, i, k;
    scanf("%u%u%u", &x, &i, &k);

    //nie rozważam przypadków bo to działa
        // i == k nic nie robie
        // i > k tak jak poniżej
        // i < k tak jak ponizej 

    uint32_t bit, mask;
    mask = 1U << i; // tworze maske która ma bit na i tej pozycji
    bit = (x & mask) >> i; //sprawdzam czy bit w x jest zapalony na i tej pozycji

    mask = 1U << k; //tworze mask e która ma bit na k tej pozycji
    x = (x & ~mask); // usuwam bit z k tej pzycji
    x |= bit << k; // może dodaje bit na k tą pozycje

    printf("%u\n", x);
}

