/*
long v1 = q->t;
long v2 = q->u;
p->y = v1 + v2;

set_val:
    movslq  8(%rsi),    %rax   -> wiemy że offset t = 8
    addq    32(%rsi),   %rax   -> wiemy że offset u = 32
    movq    %rax,       184(%rdi)
    ret


    wiemy że:
        offset s[A] = offset t + 4 = 12
        sizeof s[A] = 32 - 12 = 20 -> A = 10

        B jest z przedziału [5, 8]
        A jest z przedziału []

        A * B = 180 lub A * B = 184
        offset y = 184 

*/

const int A = 9, B = 5; // ans

// p
typedef struct {
    int x[A][B];
    long y;      //184
} str1;

// q
//allign to 8
typedef struct {
    char array[B];  //offset 0 -> więc B: [1, 8]
    int t;          //offset 8
    short s[A];     //
    long u;         //offset 32
} str2; 

void set_val(str1 *p, str2 *q) {
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1 + v2;
}