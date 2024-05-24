#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(){
    int32_t x = INT_MIN, y = -2, s = x + y;
    int32_t ans = ((x ^ s) & (y ^ s)) >> 31;

    //1 źle, 0 jak dobrze
    
    printf("%d\n", ans);
}
