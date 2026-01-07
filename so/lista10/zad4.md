# zad 4

--- 

* `wątek złączany` (joinable) - domyślny stan. po zakończeniu pracy nie zwalnia automatycznie swoich zasobów (TID, stos, wynik), czeka aż inny wątek je odbierze funkcja pthread_join
* `wątek odczepiany` (detached) - wątek który automatycznie zwalania wszystkie swoje zasoby bez ingerencji innych wątków bo zakończeniu pracy. nie można na niego czekać ani pobrać jego wyniku

---

| funkcja procesu | funkcja posix pthreads | opis | różnice
| --- | --- | --- | --- |
| fork(2) | pthread_create | tworzy nowy wątek, który otrzymuje własny stos, rejestry i TID, ale wspłdzieli heap, zmienne globalne i otwarte pliki | fork towrzy kopie całej przestrzeni adresowej, pthread_create współdzieli przestrzeń adresową
| exit(3) | pthread_exit | kończy działanie bierzącego wątku | exit zabija cały proces, pthread_exit zabija tylko siebie a inne wątki dalej działają. pthrad_exit nie zamyka plików otwartych przez ten wątek (bo są współdzielone przez proces)
| waitpid(2) | pthread_join | blokuje wątek wywołujący do momątu zakończenia wskazanego wątku | waitpid pozwala czekać na dowolne dziecko `-1` lub grupę procesów. pthread_join czeka na konkretny wątek oraz zwraca void* (czyli dowolną strukture) zamiast int
| atexit(3) | pthread_cleanup_push | rejestruje funkcje, która zostani wywołana przy zakończeniu wątku | atexit działą dla całego procesu i działa tylko przy `exit`. pthread_cleanup_push jest lokalne dla wątku
| abort(3) | pthread_cancel | wysyła ządanie zakończenia wskazanego wątku | abort zapijap roces natyczmiast i bezwarunkowo. pthread_cancle zależy od konfiguracji wątku. wątek może mieć wyłączone anulowanie, albo może zostać odroczone w czasie, np by móc coś zapisać / posprzątać

``` c
int pthread_create(     pthread_t *restrict thread,             // miejsce na zapisanie danych nowego wątku
                        const pthread_attr_t *restrict attr,    // konfiguracja/atrybuty nowego wątku
                        typeof(void *(void *)) *start_routine,  // funkcja którą wątek ma wykonać
                        void *restrict arg                      // argument przekazywany do tej funkcji
                  );

void pthread_exit(  void *retval    // wskaźnik na wynik zwracany
                 );

int pthread_join(   pthread_t thread,   // id wątku na którego czekamy
                    void **retval       // miejsce na wskaźnik zwracany przez ten wątek
                );

void pthread_cleanup_push(  typeof(void (void *)) *routine, // funkcja sprzątająca (która się odpala przy cancle / exit)
                            void *arg                       // argument dla funkcji
                        );

int pthread_cancel(pthread_t thread     // id wątku który chcemy zakończyć
                  );
```

### wątki łączone vs wątki odczepiane

| | łączone | odczepiane |
| --- |  --- | --- |
| domyślny | tak | nie |
| zwalnianie zasobów | inny wątek z użyciem pthread_join | automatycznie przez jądro
| możliwość czekania na niego | tak | nie 


### kto odpowiada za usunięcie segmentu stowu z przestrzenie użytkownika

`pthread_join`:
```  c
#define _GNU_SOURCE
#include "pthread_impl.h"
#include <sys/mman.h>

static void dummy1(pthread_t t)
{
}
weak_alias(dummy1, __tl_sync);

static int __pthread_timedjoin_np(pthread_t t, void **res, const struct timespec *at)
{
	int state, cs, r = 0;
	__pthread_testcancel();
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	if (cs == PTHREAD_CANCEL_ENABLE) __pthread_setcancelstate(cs, 0);
	while ((state = t->detach_state) && r != ETIMEDOUT && r != EINVAL) {
		if (state >= DT_DETACHED) a_crash();
		r = __timedwait_cp(&t->detach_state, state, CLOCK_REALTIME, at, 1);
	}
	__pthread_setcancelstate(cs, 0);
	if (r == ETIMEDOUT || r == EINVAL) return r;
	__tl_sync(t);
	if (res) *res = t->result;
	if (t->map_base) __munmap(t->map_base, t->map_size);
	return 0;
}

int __pthread_join(pthread_t t, void **res)
{
	return __pthread_timedjoin_np(t, res, 0);
}

static int __pthread_tryjoin_np(pthread_t t, void **res)
{
	return t->detach_state==DT_JOINABLE ? EBUSY : __pthread_join(t, res);
}

weak_alias(__pthread_tryjoin_np, pthread_tryjoin_np);
weak_alias(__pthread_timedjoin_np, pthread_timedjoin_np);
weak_alias(__pthread_join, pthread_join);
```

`__unmapself`:
``` nasm
/* Copyright 2011-2012 Nicholas J. Kain, licensed under standard MIT license */
.text
.global __unmapself
.type   __unmapself,@function
__unmapself:
	movl $11,%eax   /* SYS_munmap */            
	syscall         /* munmap(arg2,arg3) */
	xor %rdi,%rdi   /* exit() args: always return success */
	movl $60,%eax   /* SYS_exit */
	syscall         /* exit(0) */
```
problem: wątek nie może usunąć swojego własnego stosu, bo to by było jak unicanie gałęzi na której sie siedzi
wątek złączany: 
    sprzątaniem stosu zajmuje się inny wątek, dokładniej ten, który robi pthread_join

wątek odczepiony:
    wątek usówa swój stos używając __unmapself

``` nasm
__unmapself:
	movl $11,%eax   // wątek wpisuje numer syscala SYS-munmap do rejestru
	syscall         // wywołuje munmap -> stos znika z pamięci
    // tutaj stosu już nie ma, więc nie możn robić PUSH, POP, CALL, RET ...

	xor %rdi,%rdi   // zerowanie rdi, to jest exit() args
	movl $60,%eax   // wpisywanie numer syscala SYS_exit
	syscall         // zabicie się exit(0)
```
