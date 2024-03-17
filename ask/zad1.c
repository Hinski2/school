#include <stdint.h>
#include <stdio.h>

int32_t div3(int32_t n) {
    int64_t q, t, m = 0x55555556; // Przybliżenie 2^32/3

    // Dzielenie dla n >= 0
    q = (int64_t)n * m;        // n * 2^32 / 3
    t = (int32_t)(q >> 32);    // n / 3
    
    // Korekta wyniku dla n < 0
    t = t + ((n >> 31) & 1);   // Dodanie 1 jeśli n < 0
    
    return (int32_t) t;
}

int main(){
    printf("%d\n", div3(-5));
} 

/*
Załóżmy, że n jest liczbą, którą chcemy podzielić przez 3. Wartość 2^32/3 jest przybliżeniem stałej
"magicznej" M, która w systemie binarnym jest nieskończonym ciągiem cyfr 0.0101010101... (w systemie
dziesiętnym 0.333333...). Przybliżenie to w kodzie to M = 0x55555556.

Gdy n jest nieujemne, obliczanie n/3 można przeprowadzić przez pomnożenie n przez M i przesunięcie
wyniku o 32 bity w prawo:

q = (int64_t)n * M >> 32
q ≈ (n * (2^32/3)) / 2^32
q ≈ n / 3

Gdy n jest ujemne, musimy dodać 1 do wyniku, aby zaokrąglić w dół do najbliższej liczby całkowitej.
Wartość n >> 31 jest -1, gdy n jest ujemne, i 0 gdy n jest nieujemne. Biorąc pod uwagę, że wyrażenie
(n >> 31) & 1 jest równe 1 dla ujemnych wartości n i 0 dla nieujemnych, możemy je dodać do wyniku q
bez konieczności stosowania instrukcji warunkowej.

Wynik t powinien więc być równy n/3 po zaokrągleniu w dół do najbliższej liczby całkowitej, co spełnia
definicję dzielenia całkowitoliczbowego w C
*/