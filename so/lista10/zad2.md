# zad 2

--- 

- `zakleszczenie` (Deadlock) - gdy grupa wątków czeka w nieskończoność na zasoby zajete przez siebei nawzajem
- `uwięzienie` (Livelock) - gdy wątki są aktywne i ciągle zmieniają swój stan (nie są w deadlock), ale nie robią żadnych postępów, bo w kółko readują na swoje działąnia
- `godzenie` (Starvation) - gdy watkek jest gotowy do działania i nie jest zablokowany, ale nigdy nie dostaje dostępu do zasobów (np cykle procesora) 

---

### Deadlocka
użycie wfukcji niewielobieżnej wewnatrz procedury obsługi sygnałów 

``` c
void handle_signal(int sig) { // ctrl + c
    char *ptr = (char *) malloc(42);
    free(ptr);
}

int main() {
    signal(SIGINT, handle_signal);
    for(;;) {
        void *p = malloc(1024);
        free(p);
    }
}
```

### Livelock
dwa wątki próbują zdobyć zdobyć 2 zasoby, jeśli się im nie uda to zwalniają ten który już mają 

``` c 
pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;

int foo() {
    for(;;) {
        pthread_mutex_lock(&lock_a);

        if(pthread_mutex_trylock(&lock_b) == 0) { // udało się mieć a i b
            return 1;
        } else { // nie udało się 
            pthread_mutex_unlock(&lock_a);
        }
    }
}

int bar() {
    for(;;) {
        pthread_mutex_lock(&lock_b);

        if(pthread_mutex_trylock(&lock_a) == 0) { // udało się mieć a i b
            return 1;
        } else { // nie udało się 
            pthread_mutex_unlock(&lock_b);
        }
    }
}
// wątek 1: blokuje a, próbuje zablokować b -> nie udaje się zwalania a
// wątek 2: blokuje b, próbuje zablokować a -> nie udaje się zwalania b
```

## Starvation

``` c
#define HIGH_PRIORITY 2
#define LOW_PRIORITY 1

int main(void) {
    xTaskCreate(
        vGreedy,
        "Greedy",
        configMINIMAL_STACK_SIZE,
        NULL, 
        HIGH_PRIORITY,
        NULL
    );

    xTaskCreate(
        vBlink,
        "Blink",
        configMINIMAL_STACK_SIZE,
        NULL, 
        HIGH_PRIORITY,
        NULL
    )

    vTaskStartScheduler();
    return 0;
}

static void vGready(void *pvParameters) {
    uint16_t x = 0; 
    for(;;) {
        x++;
    }
}

static void vBlink(void *pvParameters) {
    LED_DDR | _BV(LED);
    for(;;) {
        LED_PORT ^= _BV(LED);
        vTaskDelay(1000);
    }
}
```