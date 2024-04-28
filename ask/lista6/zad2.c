/*
 cqto = rozsmarowanie rdx na rdx::rdx przu użyciu najstarszego bitu raxa, nie zmienai flag
 idiv = dzielenie z zachowaniem znaku, dla 64 bitowej wersji dzieli rdx::rax by source 
    wynik jest umieszczany w rax, reszta w rdx

 jeśli zwracana wartość nie mieści się w rax i rdx to jako pierwszy argument funkcji musimy podać miejsce w ktorym
    ma zostać zapisany wynik, jako pierwszy ukryty argument funkcji (w rdi)
    
 rdi = *a
 rsi =  n
 r8 szukana minimalna wartosc
 r9 szukana maksymalna wartosc
 r10 = itr idzie od 0 do r11
 r11 = górny zakres iter
 rax = najpierw , potem zwraca wynik 
 rcx = zmienna tymczasowa przechowuje n + 8 * r10                                   !!!!!! okazuje się że pierwsza zmienna jest ukryta wię cały opis jest chujowy !!!!, kod działa ok
 rdx = rakres górny

        rdi (ukryte)  rsi      rdx
 struct T puzzle2(long *a, long n)
puzzle2:                                                // początek ustawiania zmiennych
  movq    %rdx,   %r11          r11 = rdx
  xorl    %r10d,  %r10d         r10 = 0
  xorl    %eax,   %eax          rax = 0
  movabs  $LONG_MIN,  %r8       r8 = LONG_MAX
  movabs  $LONG_MAX,  %r9       r9 = LONG_MIN           // koniec ustawiania zmiennych

.L2: cmpq %r11,   %r10          r10 i r11               // sprawdzamy czy nasz itr nie przekroczył górnego limitu
  jge .L5                       skacze jeśli r10 >= r11 
  movq    (%rsi,%r10,8), %rcx   rcx = n + 8 * r10       // ustawiamy zmienna tymczasową rcx na n + 8 * i
  cmpq    %rcx,   %r9           r9 i rcx                // r9 = max(n + 8 * i, r9) 
  wq
  cmovg   %rcx,   %r9           jeśli r9 > rcx: r9 = rcx
  cmpq    %rcx,   %r8           r8 i rcx                // r8 = min(rcx, r9)
  %rcx,   %r8                   jeśli r8 < rcx: r8 = rcx
  addq    %rcx,   %rax          rax += rcx              // do raxa dodajemy rcx na koniec rax = rdx * n + 4 * rdx * (rdx - 1) = rdx * (n + 4rdx - 4)
  incq    %r10                  r10 += 1
  jmp .L2

.L5: cqto                       rdx::rax = rax  rozsmarowuje raxa na rdx z 64 na 128
  movq    %r9,    (%rdi)        *a = r9 = szukana max_val
  idivq   %r11                  dzielnie rdx::rax przez r11, wynik w rax, reszta z dzielenia w rdx
  movq    %r8,    8(%rdi)       a[1] = r8
  movq    %rax,   16(%rdi)      a[2] = rax (czyli wynik dzielenia)
  movq    %rdi,   %rax          rax = rdi (czyli rax = a)
  ret                           zwracamy a = [r9, r8, rax] = [max_val, min_val, wynk_dzielenia]

                                                        // dzielenie to rdx * (n + 4rdx - 4) / rdx
                                                        // więc wynik to n + 4rdx - 4
                                                        // max_val to n + 8 * (idx - 1)
                                                        // min_val to n
                                                        //
                                                        // co to za dzielenie: wyznacza wartość środkową pomiędzy max_val, a min_val razy 8
                                                        //    dzięki temu można łatwo dostać się do środkowej wartości w tablicy pomiędzy l i r
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

struct srodek{
  long min;
  long max;
  long avg;
};

long MIN(long a, long b){
  return (a < b ? a : b);
}
long MAX(long a, long b){
  return (a > b ? a : b);
}

struct srodek *puzzle2(struct srodek *res, long *a, long n){
  for(int i = 0; i < n; i++){
    res -> min = MIN(res -> min, a[i]);
    res -> max = MAX(res -> max, a[i]);
    res -> avg += a[i];
  }
  
  res -> avg /= n;
  return res;
}

int main(){
  struct srodek res = {LONG_MAX, LONG_MIN, 0};
  long a[] = {2, 4, 3, 2, 1};
  struct srodek *s = puzzle2(&res, a, 5);
  printf("%ld %ld %ld\n", s -> min, s -> max, s -> avg);
}

