#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int f1(int32_t x){
    return (x > 0) || (x - 1 < 0);
}

int f2(int32_t x){
    return (x & 7) != 7 || (x << 29 < 0);
}

int f3(int32_t x){
    return (x * x) >= 0;
}

int f4(int32_t x){
    return x < 0 || -x <= 0;
}

int f5(int x){
    return x > 0 || -x >= 0;
}

int f6(int32_t x){
    return (x | -x) >> 31 == -1;
}

int f7(int32_t x, int32_t y){
    return x + y == (uint32_t)y + (uint32_t)x;
}

int f8(int32_t x, int32_t y){
    return x * ~y + (uint32_t)y * (uint32_t)x == -x;
}

int main(){
    // printf("%d\n", f1());        //ok
    // printf("%d\n", f2(1));       //ok
    // printf("%d\n", f3(46347));   //nie
    // printf("%d\n", f4());        //ok 
    // printf("%d\n", f5());        //ok
    // printf("%d\n", f6(0));       //nie
    // printf("%d\n", f7());        //ok
    // printf("%d\n", f8());        /ok
}
     