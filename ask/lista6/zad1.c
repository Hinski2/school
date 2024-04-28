#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
  %rdi = n 
  %rsi = *p 
  %r14 = uzywany do przechowania p na czas dzialania funkcji
  %rbx = używany do przechowania n na czas dzialania funkcji
  %rax = ans


  czemu funkcja jest wyrównana do 16, bo robimy 3 pushe + call dodaje 1 wartość mowiącą gdzie powrócić z funcji

               %rdi   %rsi
long pointless(long n, long *p)
pointless:                                                            stos:       stack_frame
  pushq %r14              dodajemy r14 na stos                            %r14      zmienne lokalne: brak
  pushq %rbx              dodajemy rbx na stos                            %rbx      adres powrotu: znajduje się na stosie, zapisany przez callq
  pushq %rax              dodajemy rax na stos                            %rax      rejestry zapisane przez funkcje wolaną: rax
  movq %rsi, %r14         r14 = p
  movq %rdi, %rbx         rbx = n
  testq %rdi, %rdi        czy n & n 
  jle .L1                 skocz jeśli n <= 0

  leaq (%rbx,%rbx), %rdi  n = 2 * n                             # jeśli n > 0
  movq %rsp, %rsi         p = rax (bo rsi wskazuje na raxa)
  callq pointless         wywulujemy pointless z (2 * rbx) (rsp)
  addq (%rsp), %rax       rax += (poprzednia wartość rax ze stosu)
  jmp .L3                 

.L1: xorl %eax, %eax      wyczyść rax, rax = 0      

.L3: addq %rax, %rbx      n += rax 
  movq %rbx, (%r14)       *p = n
  addq $8, %rsp           rsp += 8 (tracimy rax)
  popq %rbx               %rbx = %rbx ze stosu
  popq %r14               %r14 = %r14 ze stosu 
  retq

  tlumacznie
  wrzucamy na stos 3 zmienne które chcemy uchronić przed zmiana
  sprawdzamy czy n = 0:
    jeśli tak to ustawiamy ans na 0  (potem go zwrócimy)
  jeśli n > 0:
    n *= 2  (i to nasz pierszy argument)
    p = rax (i to nasz drucgi argument funkcji)
    wyolujemy funkcje (wywołania się nigdy skończą i dostaniemy segfaulta)
    robimy *p += *p

  *p = n
  rax = n
  zabieramy ze stosu to co na niego wrzuciliśmy 
*/

long pointless(long n, long *p){
  if(n <= 0){
    *p = 0;
    return 0;
  }
  else{
    long res = pointless(2 * n, p);
    *p = n;
    return n;
  }
}

int main(){
  long p = 0;
  long n = 6;
  long ans = pointless(n , &p);
  printf("%ld\n", ans);

}
