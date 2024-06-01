# zad3

---

`niezmienniki pętli` - zmienne (lub właściwości) które są takie sają przed i po wykonaniu się pętli
`zmienne indukcyjne` - zmienne, które są używane w pętlach do liczenia iteracji
`Strength reduction` - technika optymalizacji , która polega na zastąpieniu kosztownych operacji arytmetycznych mniej kosztownymi operacjami.

```c
void foobar(long a[], size_t n, long y, long z) {
    for (int i = 0; i < n; i++) {
        long x = y - z;
        long j = 7 * i;
        a[i] = j + x * x;
    }
}
```

```nasm
argumenty :
    a[] - rdi
    n - rsi
    y - rdx
    z - rcx

foobar:
        subq    %rcx, %rdx  ;  y -= z
        xorl    %eax, %eax  ; nasza zmienna inkukcyjna (i)
        imulq   %rdx, %rdx  ; (y - z) * (y - z) -> wyciągamy x * x przed pętle
.L2:
        cmpq    %rax, %rsi  
        je      .L5 
        movq    %rdx, (%rdi,%rax,8) ; dajemy x * x + i * 7 do a[i] czyli na początku x * x + 0 potem x * x + 7 ...
        incq    %rax                ; i++
        addq    $7, %rdx            
        jmp     .L2
.L5:
        ret

; zamiast liczyć j * 7 za każdym razem trzymamy j w rdx i w każdym obrocie pętli zwiększamy rdx o 7 
; więc niezmiennikiem pętli będzie to że rdx trzyma x * x + (liczba obrotów pętli) * 7 
; innym niezmiennikiem pętli jest x * x 
```

przed pętle wyrzuciliśmy x * x, żeby go nie liczyć w każdym obrobie pętli bo x * x jest niezmiennikiem pętli 

osłabieniu uległo j = i * 7, w asemblerze nie używamy j, zamiast tego w każdym obrocie pętli do rdx dodajemy 7 więc mamy rdx = x * x + (liczba obrotów pętli) * 7