#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main(){
    int32_t x = -5;

    //jeśli «b» jest wartością logiczną, to wyrażenie «b ? x : y» 
    //możnaprzetłumaczyć do «b * x + !b * y».
    // b = (x >> 31) == 0
    int32_t abs_x = ((x >> 31) == 0) * x + ((x >> 31) != 0) * (-x);

    //można to zaimenić na 
    abs_x = (x ^ (x >> 31)) - (x >> 31);

    //przesunięcie w prawo jest arytmetyczne więc jeśli x < 0 to dostajemy x ^ -1 - (-1) -> ~x + 1
    //dla x > 0 dostajemy x ^ 0 - 0 -> x
}

