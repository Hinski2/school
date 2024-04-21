const long CNT = 7;
const long a = 4;

typedef struct { //sizeof = 40
    long idx;
    long x[a];         
} a_struct;

typedef struct {
    int first;          //offset 0, size 4
    a_struct a[CNT];    //offset 8, size 280 -> 
    int last;           //offset 288, size 4
} b_struct;


// rdi = i, rsi = pb
void test (long i, b_struct *bp) {
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}

/*
rcx/ecx = n
test:
    movl    0x120(%rsi),    %ecx        ecx = bp -> last
    addl    (%rsi),         %ecx        ecx = bp -> lasat + bp -> first
    leaq    (%rdi,%rdi,4),  %rax        rax = 5 * i
    leaq    (%rsi,%rax,8),  %rax        rax = pb + 8 * 5 * i    //ap
    movq    0x8(%rax),      %rdx        rdx = 8 + pb[40i]       // ap -> x
    movslq  %ecx,           %rcx        rcx = bp -> last + bp -> first   
    movq    %rcx, 0x10(%rax,%rdx,8)     16 + pb + 8 * 5 * i + 64 + 8 * bp[40i]
    16 + ap + 8 * 
retq

*/
