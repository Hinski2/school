#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    funkcja to wyszukiwanie binarne v w tablicy
*/

/*
puzzle4:
        movq    %rcx, %rax          1 tworzenie mid
        subq    %rdx, %rax          1
        shrq    %rax                1
        addq    %rdx, %rax          1 koniec
        cmpq    %rdx, %rcx          1 sprawdzam czy l > r 
        jb      .L5                 1

        movq    (%rdi,%rax,8), %r8  2 %dodaje do %r8 a[mid] (v)
        cmpq    %rsi, %r8           2 sprawdzam czy v == a[mid]
        je      .L10                2 v == a[mid]
        jg      .L11                3 v > a[mid] 

        leaq    1(%rax), %rdx       4 gdy v < a[mid]; l = mid + 1
        call    puzzle4             4 puzzle

.L10:   ret                         5

.L11:   leaq -1(%rax), %rcx         6 r = mid -1
        call puzzle4                6
        ret                         6

.L5:    movq $-1, %eax              7
        ret                         7
*/

// %rdi *a; %rsi v; %rdx l; %rcx r;
// %rax mid
// s, e
long puzzle4(long *a, long v, uint64_t l, uint64_t r){
    long mid = (r - l) / 2 + l;
    if(l > r) return -1;

    // sprawdzanie co się kryje pod midem
    if(v == a[mid]) return mid;
    if(a[mid] > v){
        r = mid - 1;
        return puzzle4(a, v, l, r);
    }
    else{
        l = mid + 1;
        return puzzle4(a, v, l, r);
    }
}