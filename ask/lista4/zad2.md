# zad2

``` c
Adres   Wartość |    Rejestr     Wartość
0x100   0xFF    |    %rax        0x100
0x108   0xAB    |    %rcx        1
0x110   0x13    |    %rdx        3
0x118   0x11    |
```

``` c
1. addq %rcx,(%rax)         -> 0x100 zapisywane do 0x100
2. subq 16(%rax),%rdx       -> -0x10 zapisywane do %rdx
3. shrq $4,%rax             -> 0x10 zapisywane do %rax
4. incq 16(%rax)            -> 0x14 zapisywane do 0x110
5. decq %rcx                -> 0x0 zapisywane do %rcx
6. imulq 8(%rax)            -> 0xAB00 zapisywane do %rax
7. leaq 7(%rcx,%rcx,8),%rdx -> 0x10 zapisywane do %rdx
8. leaq 0xA(,%rdx,4),%rdx   -> 0x16 zaisywane do %rdx
```