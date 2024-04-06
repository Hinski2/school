# zad 6

``` python
    # funkacja dodająca dwie liczby int128_t
    # argumenty
        # x = %rdi, %rsi
        # y = %rdx, %rcx
    #wynik
        # %rdx, %rax
        
    .global add_128

    add_128:
            addq    %rcx,    %rsi    # dodanie młodszych bitów do rsi
            adcq    %rdi,    %rdx    # dodanie starszych bitów do rdx z ewentualnym curring

            # rdx już jest na miejscu teraz tylko rax
            movq    %rsi,    %rax    # przeniesienie rsi do rax
            ret
```
