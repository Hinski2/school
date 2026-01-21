# zad 3

---

* `instrukcja atomowa` - operacka która jest niepodzielna
* `blokada wirująca` (spin lock) - blokada która używa aktywnego czekania, kręcąc sie w kółko
* `round-robin` - sprawiedliwy algorytm planowania w którym każdy proces dostaje dostępd do procesora na krótki, róœny wyniken czasu (kwant), po czym wraca na koniec kolejki 
* `sprawiedliwość` - wątki oczekąjące na dostęp do zasobu otrzymuja go w kolejności zgłoszenia. 

--- 

### Compara-and-swap 

``` c

// modyfikacja TestAndSet z 28.7 (tamta nie przyjmowałą expected)
int compareAndSwap(int *ptr, int expected, int new_val) { 
    int original = *ptr;
    if(original == expected) {
        *ptr = new_val;
    }

    return original;
}

typedef int spint_t;

void lock(spint_t *lock) {
    while(compareAndSwap(lock, 0, 1) == 1) {}
}

void unlock(spint_t *lock) {
    *lock = 0;
}

```

### czemu blokada wirująca nie jest sprawiedliwa
bo:
* najpierw splin locka się kręci
* potem wątek zwalnia ten lock
* wątki które czekały na locka rzucają sie na niego jednocześnie i wygrywa ten, który pierwszy go zamknie
    więc o tym kto wygra wyścig deyduje scheduler

### uruchamiany n identycznych wątków. Kolejno każdy z nich wchodzi do sekcji krytycznej, p czym zostaje wywłaszzony przez jądro. Ile czasu zajmie wszystkim wątkom jednokrotne przejście przez sekcje krytyczną - algorytm planisty to round - robin, kwant czasu wynosi 1ms

Odp: $\frac{(n + 1) * (n + 2)}{2}  \ ms$ 
* wątek 1 dosataje procesor, wchodzi do sekcji krtycznej, kończy mu się kwant czasu i zostaje wywłaszczony zanim zwolni locka
* wątek 2 dostaje procesor i próbuje wejśc do sekcji krytycznej ale nie może bo jest lock. marjuje 1ms
* wątek 3 .. n tak samo wiec marnujemy n - 1 ms
* wracamy do wątku 1. kończy on swoja prace i zwalnia lock

więc na wątek 1 zuzyliśmy n + 1 kwantów czasu
jeśli założymy że po przejściu sekcji krytycznej wątek umiera to wątek 2 zużyje n, 3 zużyje n - 1... 

