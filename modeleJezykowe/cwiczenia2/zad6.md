# zad 6

---

idea: 
uzywamy prawdopodobieństwa generowanego przez papuge
tokeny bardziej przewidywalne -> krótszy kod
tokeny mniej przewydywalne -> dłuższy kod 

rank := majac prawdopodobieństwa tokenów, sortujemy je i rank to idx maszego tokenu

idea: chcemy zakodować tekst jako zlepiony ciąg 0,1. czyli zapisać wszystkie rank binarnie.
probelm: nie wiemy keidy zaczyna się który token

#### pomysł 1
rozwiązanie:
zamiast używać jednego bitnu na zapis bitu będziemy używali 2:
`00` -> 0 binarnie
`01` -> 1 binarnie
`11` -> koniec tokenu / spacja


#### pomysł 2 
https://en.wikipedia.org/wiki/Elias_gamma_coding
1. zapisujemy rank w systemie binarnym bez zer z przodu 
    * b := zapis binarny który otrzymaliśmy
    * L := liczba bitów 

2. robimy prefiks z L-1 zer

3. sklejamy [prefix] + [b]

| rank | bin | L | gamma(n) |
| --- | --- | --- | --- |
| 1 | 0b1 | L = 1  | 1
| 2 | 0b10 | L = 2  | 010
| 3 | 0b11 | L = 2  | 011
| 4 | 0b100 | L = 3  | 00100

