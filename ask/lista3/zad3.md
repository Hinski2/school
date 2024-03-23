## zad3 float16 vs float32

dla float16:
* 1 bit na znak (S),
* 5 bitów na wykładnik (E),
* 10 bitów na mantysę (M), znane również jako część ułamkowa.

dla float32:
* 1 bit na znak (S),
* 8 bitów na wykładnik (E),
* 23 bity na mantysę (M).

$1.5625 · 10^{-1} = 1 + \frac{1}{2} + \frac{1}{16}$ czyli binarnie $1.1001 * 2 ^ {-4}$

(S) 1
(E) bias to $2 ^ 5 - 1 = 15$ więc wykładnik to 11, binarnie $01011$
(M) $1001000000$

Liczba to: `1010 1110 0100 0000`

