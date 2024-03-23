.global _start
.global add_128

add_128:
        addq    %rsi,    %rsi    # dodanie błodszych bitów do rsi
        adcq    %rdi,    %rdx    # dodanie starszych bitów do rdx z ewentualnym curring

        # rdx już jest na miejscu teraz tylko rax
        movq    %rsi,    %rax    # przeniesienie rsi do rax
        ret

_start:
    # tutaj można by było napisać wywołanie funkcji add_128

    # zakończenie programu
    mov     $60,    %rax  # sys_exit
    mov     $0,     %rdi   # Kod wyjścia, np. 0
    syscall        # Wykonanie wywołania systemowego
