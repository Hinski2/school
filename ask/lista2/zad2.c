#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(){
    int32_t x, y;
    scanf("%d %d", &x, &y);

    x = x ^ y;
    y = x ^ y;
    x = x ^ y;

    printf("%d %d\n", x, y);
    // bo (x ^ y) ^ y == x
    // bo (x ^ y) ^ x == y
    //xor jest łączny i przemienny 
}