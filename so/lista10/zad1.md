# zad 1

--- 

* `przetwarzanie równoległe` - fizyczne wykonywanie wielu instrukcji w tym samym czasie, realizowane z postaci wielu rdzeni procesora
* `przetwarzanie współberzne` - wykonywanie wielu zadań realizowane poprzez szybkie zmiany pomiędzy taskami
* `procedury wielobieżne` - funkcje, które mogą zostać bezpiecznie przerwane w trakcie wykonywania, a potem wznowione
* `prodecura wielokątkowo-bezpieczna` - funkcja która może być wywoływana jednocześnie przez wiele wątków bez ryzyka wystąpienia race condition lub niespójności danych 

--- 

### przetwarzanie róznoległe vs współbieżne 
równoległę - wykonuje wiele zadań w tym samym czasie, wymaga sprzętowego wsparcia
współbiezne - wykonuje wiele zadań szybko przełączając sie między nimi

### czym charakteryzują się procedury wielobieżne 
Procedura jest wielobieżna, jeżli jej wykonanie może zostać bezpiecznie przerwane (np przez sygnał lub przerwanie), a następnie funkcja ta może zostać wywołana ponownie z innego kontekstu zanim  pierwsze wywołanie sie zakończy

cechy:
* `brak stanu wewnętrznego` - nie używa zmiennych globalnych ani statycznych, operuje wyłącznie na danych przekazywanych przez argumenty i zmienncyh lokalnych
* `nie wywołuje innych funkcje ktore nie są wielobieżne` 
* `nie zakłada blokad` (mutexów i semaforów)

### przykłady 

* `procedura wielobieżna ale nie wielowątkowo-bezpieczna`:
    * memcpy, memset (można je używać w signal handlerach, ale może dojść do race condition)

``` c
// zwiększanie zmiennej przez wskaźnik:
void incr(int *counter) {
    (*counter)++;
}
```

* `procedura nie wielobieżna ale wielowątkowo-bezpieczna`: 
    * printf (do page size), scanf 
    * malloc, free (posiadają muteksy)