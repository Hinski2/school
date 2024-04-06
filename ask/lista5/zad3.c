#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// funkcja puzzle to popcoutn dla n najmłodszych bitów
/*
    if n == 0: L4

    ile_sprawdziliśmy = 0
    ans = 0

L3: ecx = x & 1
    ans += ecx
    ile_sprawdziliśmy++
    if ile_sprawdziliśmy < n: L3
    ret
L4: ans = 0
    ret
*/

int32_t puzzle(long x, uint32_t n){
    int32_t ans = 0;
    for(int i = 0; i < n; i++){
        ans += x & 1;
        x >>= 1;
    }

    return ans;
}

int main(){
    long x = 42;
    uint32_t n = 17;
    printf("%d\n", puzzle(x, n));
}
