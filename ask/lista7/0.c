#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct {
    long n;
    float tab[];
}P;

int main(){
    printf("%ld\n", sizeof(__CHAR_BIT__));
}