# zad 4

----
 
* mogą być co najwyżej trzy procesy współbieżnie korzystające z zasobu,
* jeśli w danej chwili zasób ma mniej niż trzech użytkowników, to możemy bez opóźnień przydzielić zasób kolejnemu procesowi,
* jednakże, gdy zasób ma już trzech użytkowników, to muszą oni wszyscy zwolnić zasób, zanim zaczniemy dopuszczać do niego kolejne procesy,
* operacja «acquire» wymusza porządek „pierwszy na wejściu, pierwszy na wyjściu” (ang. FIFO).

```
    mutex = semaphore(1) # implementuje sekcję krytyczną - semafor zainicjowany na 1
    block = semaphore(0) # oczekiwanie na opuszczenie zasobu - semafore zainicjowany na 0 
    active = 0 # liczba użytkowników zasobu
    waiting = 0 # liczba użytkowników oczekujących na zasób
    must_wait = False # czy kolejni użytkownicy muszą czekać?

    operacje na semaforze:
        .wait() - [P] - wątek przychodzi do putełka jeśli jest żeton to go zabiera i idzie dalej, jeśli nie ma żetonów to czeka aż ktos go wrzuci 
        .post() - [V] - wątek wrzuca żeton do skrzynki, jeśli ktoś spał przy skrzynce so budzi jeden ze śpiących  

    active - ile procesów jest teraz w śdodku dużego zasobu
    waiting - ile procesów śpi na semaforze block 
    must_wait - bo my wymóg gdy zasób ma już 3 użytkowniktó, muszą oni wszyscy zwolnić zasób zanim zaczniemy dopuszczać kolejne 
```


--- 

### przekroczenie liczby 3 procesów
używamy if zamiast while w `if must_wait`
zał:
    activate = 3
    waiting = 3 (np trzy wątki W_4, W_5, W_6 które czekają na semaforze block)
    must_wait = True

* wątek W_1, W_2, W_3 wywołują release(),
    * activate zmniejsza sie do 0
    * n = 3 
    * must_wait = false 
    * w_3 zwalnia mutex 
* zanim W_4, W_5, W_6 zostana obudzone przychodzą nowe w_7, W_8, W_9
    * must wait jest false więc skippują blok
    * ale potem budzą sie W_4, W_5, W_6 i wychodzą z bloku 
* mamy activate = 6

``` c
def acquire():
    mutex.wait()   // W_7, W_8, W_9
    if must_wait: 
        waiting += 1
        mutex.post()
        block.wait() // W_4, W_5, W_6
        mutex.wait()
        waiting -= 1

    active += 1
    must_wait = (active == 3)
    mutex.post()

def release(): // W_1, W_2, W_3 wykonują 
    mutex.wait()
    active -= 1
    if active == 0: // W_3 robi activate = 0
        n = min(waiting, 3);
        while n > 0:
            block.post()
            n -= 1
        must_wait = False
    mutex.post()
```

### brak kolejności FIFO


wymaganie mówi że acquire musi wymuszać porządek FIFO

zał:
    active = 3
    waiting = 1 (wątek W_4 czeka w kolejce)
    must_wait = True

* ostatni z aktywnych procesów zwalnia zasób
    * ustawia active = 0
    * budzie W_4 (block.post())
    * ustawia must_wait = False 
    * zwalnia mutex 
* teraz zamin W_4 zdązy się obudzieć i zająć mutex pojawia sie nowy wątek W_5 i wywołuje acquire
* W_5 sprawdza warunke w lini 3 (if must_wait). która została ustawiona na False przez release 
* W_5 omija ten blok, zwiększa activate i wchodzi do sekcji krtycznej 
* dopierao teraz W_4 odzyskuje mutex i wchodzi do zasobu 

``` c
def acquire():
    mutex.wait()    // przychodzi W_5 i robić mutex_wait zamin zrobi to W_4
    if must_wait: 
        waiting += 1
        mutex.post()
        block.wait() // W_4
        mutex.wait()
        waiting -= 1

    active += 1
    must_wait = (active == 3)
    mutex.post()

def release(): // W_1, W_2, W_3 wykonują 
    mutex.wait()
    active -= 1
    if active == 0: // W_3 robi activate = 0
        n = min(waiting, 3);
        while n > 0:
            block.post()
            n -= 1
        must_wait = False
    mutex.post()
```