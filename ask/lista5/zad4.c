#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/*
    funkcja sprawdza ile znaków z s znajduje się w tablicy d
*/

/*
puzzle2:
        movq %rdi, %rax         1       przypisauje do rax s

.L3:    movb (%rax), %r9b       2       przypisuje pierwszy znak z s do r9b
        leaq 1(%rax), %r8       2       przypisauje s do r8 z pominieciem jednego znaku
        movq %rsi, %rdx         2       przypisuje do rdx d

.L2:    movb (%rdx), %cl        3       przypisauje do cl pierwszy znak z d
        incq %rdx               3       przesówam początek d o jeden, gubiąc pierwszy znak
        testb %cl, %cl          3       sprawdzam czy nie wyszedłem poza tablice d
        je .L4                  3       jeśli wyszedłem poza tablice d

        cmpb %cl, %r9b          4       sprawdzam czy początek s i d są takie same
        jne .L2                 4       są różne to ide do L2 czyli sprawdzam następny znak z d

        movq %r8, %rax          5       znaki są takie same więc zapisuje ans
        jmp .L3                 5       sprawdzam czy mogę dalej przesunąć s i sprawdzicwięcej znaków

.L4:    subq %rdi, %rax         6       zwracam liczbę znaków z s ktre znalazłem w d
        ret
*/

long puzzle2(char *s, char *d){
    char *oryginalna_s = s;
    char *oryginalna_d = d;

    while(*s){
        d = oryginalna_d;
        while(*d){
            // znaki takie same
            if(*s == *d){
                s++;
                break;
            }
            // inne znaki
            d++;
        }

        //jeśli przeszedłem całą tablice d i nic nie znalazłem
        if(!*d) break;
    }

    return s - oryginalna_s;
}