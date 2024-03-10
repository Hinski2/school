#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int main(){
    int32_t x = -5, is_non_zero = x;

    is_non_zero |= is_non_zero >> 16;
    is_non_zero |= is_non_zero >> 8;
    is_non_zero |= is_non_zero >> 4;
    is_non_zero |= is_non_zero >> 2;
    is_non_zero |= is_non_zero >> 1;

    is_non_zero &= 1; //dostajemy 0 dla x == 0, 1 dla x != 0
    int32_t sig_x = (x >> 31) | is_non_zero;

    //dla x < 0: -1 | 1 -> -1
    //dla x = 0: 0 | 0 -> 0
    //dla x > 0: 0 | 1 -> 1

    printf("%d\n", sig_x);
}
