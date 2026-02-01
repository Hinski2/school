# zad 4 

--- 

* `aktywne czekanie` - czekanie na zazób w pętli
* `blokada usypiająca` - jesli wątek napaotyka na zajęty zasób to robi yield, a so budzi go dobiero gyd zasób się zwolni

---

### czemu oddanie czasu procesora funkcja yield nie rozwiazuje wszystkich problemów które mieliśmy z blokadami wirującymi
* funkcja yield jest kosztowna bo trzeba przełączać kontekst
* nadal może wystąpić głodzenie, yield nie daje gwarancji tego kto dostanie procesor jako następny ani kiedy wątek który ustąpił dostanie kolejna szanse

### zreferuj implementację podaną w 28.14 czcemu jest ona niepoprawna bez użycia funkcji setpartk

``` c
typedef struct __lock_t {
    int flag;   // właściwy lock
    int guard;  // pomocniczy lock
    queue_t *q;
} lock_t;

void lock_init(lock_t *m) {
    m->flag = 0;
    m->guard = 0;
    queue_init(m->q);
}

void lock(lock_t *m) {
    while (TestAndSet(&m->guard, 1) == 1)
        ; //acquire guard lock by spinning

    if (m->flag == 0) {
        m->flag = 1; // lock is acquired
        m->guard = 0;
    } else {
        queue_add(m->q, gettid());
        m->guard = 0;
        park();
    }
}

void unlock(lock_t *m) {
    while (TestAndSet(&m->guard, 1) == 1)
        ; //acquire guard lock by spinning
    if (queue_empty(m->q))
        m->flag = 0; // let go of lock; no one wants it
    else
        unpark(queue_remove(m->q)); // hold lock (for next thread!)
    m->guard = 0;
}
```

funkcja lock() dla prypadkui gdy zamek jest zajęty wykonjje:
* dodaje bieżący watek do kolejki oczekujących (queue_add)
* zwalnia blokadę pomocniczą (m -> guard = 0), aby inny wątek mógł operować na kolejce
* wynikuje park() by uśpić wątek

problem: występuje race condition w momencie pomiedzy zwolnieniem guard a wywołaniem park()

* wątek A chce wejści -> jest lock -> dodaje sie do kolejki 
* przełączenie konteksu, zanim a wywołał park() system oddaje proesor wątkowi B 
* wątek B zwalnia zamek 
* powrót do A . wątek a odzyskuje procesor i wykonuje instrukcje park() 

więc wątek A zasypia, ale B już wysłał pobudke wcześniej więc już nik go nie obudzi.

setpark () - pozwala zgłosić so intencje pójścia spać zanim zwolni od guard
wiec powinniśmy robić:

    setparrk()
    m -> guard -> 0 
    park() 