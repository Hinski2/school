const int R = 7, S = 5, T = 13;
long A[R][S][T];

long store_elem(long i, long j, long k, long *dest){
    *dest = A[i][j][k];
    return sizeof(A);
}
/*

rdi = i
rsi = j
rdx = k
rcx = dest


S * T = 65
T = 13 ->
    -> S = 5
R * S * T = 455 -> R = 7


store_elem:
    leaq    (%rsi,%rsi,2),  %rax        rax = 3 * j
    leaq    (%rsi,%rax,4),  %rax        rax = 13 * j
    movq    %rdi,       %rsi            rsi = i
    salq    $6,         %rsi            rsi = 64 * i
    addq    %rsi,       %rdi            rdi = 65 * i
    addq    %rax,       %rdi            rdi = 13 * j + 65 * i
    addq    %rdi,       %rdx            rdx = k + 13 * j + 65 * i
    movq    A(,%rdx,8), %rax            rax = A + 8 * (k + 13 * j + 65 * i) = A + 8 * k + 104 * j + 520 * i 
    movq    %rax,       (%rcx)          rax = A[65 * i][13 * j][k]
    movq    $3640,      %rax
    ret

    wiemy że:
        sizeof(A) = 3640 ->
            -> R * S * T = 455
        
*/