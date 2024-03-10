#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int32_t threefourths(int32_t x){
    int32_t divided = x >> 2;                       // divided = x / 4
    int32_t result = (divided << 1) + divided;      // result = x * 3/4

    // reszta z dzielenia x przez 4, bo wielekrotności 4 są postaci ...00
    int32_t remainder = x & 3; 

    // additional to reszta z dzielenia * 3/4 (ona jest dodatnia)
    int32_t additional = (remainder << 1) + remainder; 
    additional >>= 2; 

    return result + additional; 
}


int main(){
    int32_t x = -2;
    int32_t x34 = threefourths(x);
    printf("%d\n", x34);
}
