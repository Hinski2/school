#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

union elem {
    struct {//16 bajtów
        long *p;            // 8 bajtów
        long y;             // 8 bajtów
    } e1;

    struct {//16 bajtów
        long x;             // 8 bajtów
        union elem *next;   // 8 bajtów
    } e2;
};

/*
    elem:
    0:  p   x
    1:  p   x
    2:  p   x
    3:  p   x
    4:  p   x
    5:  p   x
    6:  p   x
    7:  p   x

    8:  y   next
    9:  y   next
    10: y   next
    11: y   next
    12: y   next
    13: y   next
    14: y   next
    15: y   next
*/



// void proc(union elem *ep) {
//     long *rax = (long *)(ep->e2.next);      // Odpowiada linii 12 w asemblerze.
//     long rdx = *(long *)(*rax);                   // Linie 13 i 14 w asemblerze.
//     rdx -= *(rax + 1);                            // Linia 15 w asemblerze.
//     *(long *) ep = rdx;                      // Linia 16 w asemblerze.
// }


// oblicza *p - y dla nex_elem i wpisuje do elem -> e2.x
void proc(union elem *elem_ptr) {
    union elem *next_elem = elem_ptr->e2.next; //następna wartość

    long rdx = *(long*) next_elem->e1.p;       //wartość na którą wskazuje next elem, może y

    rdx -= next_elem->e1.y;                    //wartość wskaźnika 

    elem_ptr->e2.x = rdx;
}

int main(){
    long someValue = 10;
    long otherValue = 5;

    // Tworzenie pierwszego elementu unii
    union elem first_elem;
    first_elem.e1.p = &someValue;  // przypisanie wskaźnika
    first_elem.e1.y = 15;          // przypisanie wartości bezpośredniej

    // Tworzenie drugiego elementu unii
    union elem second_elem;
    second_elem.e1.p = &otherValue;  // przypisanie wskaźnika
    second_elem.e1.y = 20;           // przypisanie wartości bezpośredniej

    // Powiązanie obu elementów
    first_elem.e2.next = &second_elem;

    //wypisanie
    puts("before\n");
    printf("first_elem.e1.y: %ld\n", first_elem.e1.y);              // Wartość y w e1
    printf("first_elem.e2.x: %ld\n", first_elem.e2.x);              // Wartość x w e2
    printf("second_elem.e1.y: %ld\n", second_elem.e1.y);              // Wartość x w e2
    printf("second_elem.e2.x: %ld\n", second_elem.e2.x);              // Wartość x w e2

    // Wywołanie procedury
    proc(&first_elem);


    //wypisanie
    puts("after\n");
    printf("first_elem.e1.y: %ld\n", first_elem.e1.y);              // Wartość y w e1
    printf("first_elem.e2.x: %ld\n", first_elem.e2.x);              // Wartość x w e2
    printf("second_elem.e1.y: %ld\n", second_elem.e1.y);              // Wartość x w e2
    printf("second_elem.e2.x: %ld\n", second_elem.e2.x);              // Wartość x w e2

}

/*
ep
proc:
    movq 8(%rdi),   %rax       rax = ep -> 
    movq (%rax),    %rdx       
    movq (%rdx),    %rdx        
    subq 8(%rax),   %rdx       
    movq %rdx,      (%rdi)     
ret
*/
