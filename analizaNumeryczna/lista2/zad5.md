# IEEE 754 vs model teoretyczny z wykładu

### IEEE 754
[$\pm 1$ znak][8 bitów cecha ze znakiem][23 bity mantysa]


### wykład
[$\pm 1$ znak ][$1 \ e_2 \ e_3 \ \dots \ e_t$ $t$ bitów mantysy][$d - t$ bitów na ceche z znakiem]
łącznie d + 1 bitów 

postać: $x = s \cdot m \cdot 2^c$
gdzie:
* $s \in \{+1, -1 \}$ 
* $m \in  [\frac{1}{2}, 1)$
* $c \in \Z$

### różnice 

| | IEEE 754 | model teoretyczny |
| --- | --- | --- |
| pierwszy znak mantysy | jeden którego nie zapisujemy | jeden który zapisujemy| 
| zakres normalizacji mantysy | $[1, 2)$ | $[\frac{1}{2}, 1)$
| rozmiar ogólnie | 32 bity | d + 1 bitów |
| rozmiar cechy | 8 bitów | t bitów |
| rozmiar mantysy | 23 bity | d - t bitów | 
| cecha | $c \in \N$ | $c \in \Z$ | 
| przesunięcie cechy | cecha jest zapisywana z przsunięciem równym 127 (czyli jak wychodzi c = 4 to piszemy 4 + 127) | cecha nie ma przesunięcia 
| niedomiar | liczby representowane są przez liczby zdenormalizowane (subnormal numbers), a jeśli nawe tliczby zdenormalizowane nie są w stanie reprezentować wynito to wartość jest zaokrąglana do +0 lub -0 | po prostu 0 
| reprezentacja $\infty$ | cecha = 255, mantysa = 0 | brak reprezentacji
| reprezentacja NaN | cecah = 255 mantysa $\neq$ 0 | brak reprezetacji 

--- 

#### dodatkowe info

liczby zdenormalizowane: 
* liczby zmiennoprzecinkowe o najmniejszej możniwej cesze, wktórych precyzja mantysy jest zmiejszona
* ich cecha jest równa 0 
* nie posiadają ukrytego pierwszego bitu równego 1
* mają mantyse z zakresu $[0, 1)$ a nie z $[1 ,2)$
