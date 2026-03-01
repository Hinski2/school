#include<bits/stdc++.h>
#include <limits>
#include <print>
using namespace std;
using ld = long double;

int main() {
    println("min {}, max {}", numeric_limits<ld>::min(), numeric_limits<ld>::max());
    println("czy ma nieskończoność: {}, nieksończoność: {}", numeric_limits<ld>::has_infinity, numeric_limits<ld>::infinity());
    println("epsilon {}", numeric_limits<ld>::epsilon());
    println("różnica: {}", 1. - (numeric_limits<ld>::min() + 1));
}

/*
    
    [sign: 1][exponent: 11][mantysa: 52]

    znormalizowane:     (-1) ** sign * [1.mantysa] * 2 ** (exponent - 1023)       (1 <= exponent <= 2046)
    zdenormalizowane:   (-1) ** sign * [0.mantysa] * 2 ** (1 - 1023)              (exponent == 0 i mantysa != 0) [to jest 1 a nie 0, by nie było luki między max(subnormal) i min(normal)]

    1 przed mantysą - liczba znormalizowana
    0 przed mantysa - liczba zdenormalizowana
   
    najmniejszy wykładnik: 0b00000000001 -> 2 ** (1 - 1023)
    zerowy wykładniek: 0b01111111111 -> 2 ** (1023 - 1023)
    największy wykładnik: 0b11111111110 -> 2 ** (2046 - 1023)

    wykladnik 0b00000000000 -> reprezentuje liczby zdenormalizowane
    wykładnik 0b11111111111 -> reprezentuje inf if f == 0 else Nan
*/

