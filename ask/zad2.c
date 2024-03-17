#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

#define N 32

uint32_t dystans(const uint32_t *x, const uint32_t *y, size_t n){
    uint64_t suma = 0;
    for (size_t i = 0; i < n; ++i) {
        int64_t roznica = (int64_t)x[i] - (int64_t)y[i];
        uint64_t kwadrat = (uint64_t)(roznica * roznica) >> N;
        
        suma += kwadrat;
    }

    uint32_t wynik = (uint32_t)(suma / n);
    return wynik;
}

int main(){
    int32_t n = 3;
    int32_t *x = malloc(n * sizeof(int32_t));
    int32_t *y = malloc(n * sizeof(int32_t));

    for(int i = 0; i < n; i++){
        x[i] = 1 << (31 - i);
        y[i] = 1 << (31 - i) | 1 << (30 - i); 
    }

    printf("%u\n", dystans(x, y, n));
    free(x);
    free(y);
}
