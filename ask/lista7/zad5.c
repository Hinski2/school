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


//rdi to e
void proc(union elem *e){
    long *rdx = e -> e2.next;
    rdx -= *(e + 2);
    e -> e1.y = rdx;
}




int main(){
    printf("%ld\n", sizeof(union elem));
}


/*
załużmy że mamy a i b
proc:
    movq 8(%rdi),   %rax       rax = rdi + 8    -> &(a -> next)
    movq (%rax),    %rdx       rdx = *rax       -> a -> next
    movq (%rdx),    %rdx       rdx = **rax      -> b
    subq 8(%rax),   %rdx       rdx -= rdi + 16  
    movq %rdx,      (%rdi)      
ret
*/
