# zad5

---

`eliminacji wspólnych podwyrażeń` -  wykrywanie i eliminacja powtarzajacych się obliczeń 

```c
long neigh(long a[], long n, long i, long j) {
    long ul = a[(i-1)*n + (j-1)];
    long ur = a[(i-1)*n + (j+1)];
    long dl = a[(i+1)*n - (j-1)];
    long dr = a[(i+1)*n - (j+1)];

    return ul + ur + dl + dr;
}
```

```nasm
argumenty:
    a[] - rdi
    n - rsi
    i - rdx
    j - rcx

neigh:
        decq    %rdx                    ; rdx = i - 1
        leaq    -1(%rcx), %r8           ; r8 = j - 1
        incq    %rcx                    ; rcx = j + 1
        imulq   %rsi, %rdx              ; rdx = (i - 1) * n
        addq    %rsi, %rsi              ; rsi = 2n
        addq    %rdx, %rsi              ; rsi = 2n + (i - 1) * n = (i + 1) * n
        leaq    (%rdx,%r8), %r9         ; r9 = (i - 1) * n + j - 1
        addq    %rcx, %rdx              ; rdx = (i - 1) * n + j + 1 
        movq    (%rdi,%rdx,8), %rax     ; rax = a[(i - 1) * n + (j + 1)]
        movq    %rsi, %rdx              ; rdx = (i + 1) * n
        subq    %rcx, %rsi              ; rsi = (i + 1) * n - j - 1
        addq    (%rdi,%r9,8), %rax      ; rax += a[(i - 1) * n + (j - 1)]
        subq    %r8, %rdx               ; rdx = (i + 1) * n - j + 1
        addq    (%rdi,%rdx,8), %rax     ; rax += a[(i + 1) * n - (j - 1)]
        addq    (%rdi,%rsi,8), %rax     ; rax += a[(i + 1) * n - (j + 1)]
        ret

    2; r8 = j - 1
    3; rcx = j + 1
    4; rdx = (i - 1) * n
    5; rsi = (i + 1) * n   

    decq    %rdx                    ; rdx = i - 1
    leaq    -1(%rcx), %r8           ; r8 = j - 1
    incq    %rcx                    ; rcx = j + 1
    imulq   %rsi, %rdx              ; rdx = (i - 1) * n
    leaq    (%rdx,%rsi,2), %rsi     ; rsi = (i + 1) * n
    movq    %rsi, %r9               ; r9 = (i + 1) * n
    addq    %r8, %r9                ; r9 = (i + 1) * n + (j - 1)
    movq    (%rdi, %r9, 8), %rax    ; rax = [ul]
    addq    $2, %r9                 ; r9 = (i + 1) * n + (j + 1)
    addq    (%rdi, %r9, 8), %rax    ; rax = [ul] + [ur]
    subq    %rcx, %rdx              ; rdx = (i - 1) * n - (j + 1)
    addq    (%rdi, %rdx, 8), rax    ; rax = [ul] + [ur] + [dr]
    addq    $2, %rdx                ; rdx = (i - 1) * n - (j - 1)
    addq    (%rdi, %rdx, 8), rax    ; gg
    ret
```
