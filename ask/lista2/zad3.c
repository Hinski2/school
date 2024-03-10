#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int main(){
    int32_t x = INT32_MAX, y = 1, s = x + y;
    ((x > 0) && (y > 0) && (s < 0)) || ((x < 0) && (y < 0) && (s >= 0));
}
