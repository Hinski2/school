# zad1

``` c
Adres   Wartość |    Rejestr     Wartość
0x100   0xFF    |    %rax        0x100
0x108   0xAB    |    %rcx        1
0x110   0x13    |    %rdx        3
0x118   0x11    |

```

``` c
1. %rax             -> 0x100
2. 0x110            -> 0xFF
3. $0x108           -> 0x108
4. (%rax)           -> 0xFF
5. 8(%rax)          -> 0xAB
6. 21(%rax,%rdx)    -> 0x11
7. 0xFC(,%rcx,4)    -> 0xFF
8. (%rax,%rdx,8)    -> 0x11
9. 265(%rcx,%rdx,2) -> 0x13
```