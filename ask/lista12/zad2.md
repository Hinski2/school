# zad2

---

``__attribute__((leaf))`` mówi kompilatorowi, że dana funkcja jest funkcją liściową, czyli nie wywołuje innych funkcji
``__attribute__((pure))`` mówi kompilatorowi, że funkcja jest czystą funkcją, czyli funkcją która nie ma efektów ubocznych oraz jej wynik zależy tylko od jej argumentów i globalnych zmiennych, kórych nie zmienia
``inlining``  to optymalizacja kompilatora polegająca na zastąpieniu wywołania funkcji jej ciałem w miejscu wywołania. 


#### kod w c:
<style>
.full-width-table table {
  width: 100%;
  max-width: fit-content;
  margin-left: auto;
  margin-right: auto;
}
</style>

<div class="full-width-table">

<table>
<tr>
<td>

```c
__attribute__((leaf))
    size_t my_strlen(const char *s);

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == v)
        return &s[i];
        return 0;
}
```

</td>
<td>

```c
__attribute__((pure))
    size_t my_strlen(const char *s);

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == v)
        return &s[i];
        return 0;
}
```



</td>
</tr>
</table>

#### kod w asm:

<table>
<tr>
<td>

``` nasm
my_index:
        pushq   %r12
        movl    %esi, %r12d
        pushq   %rbp
        xorl    %ebp, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
.L2:
        movq    %rbx, %rdi
        call    my_strlen
        cmpq    %rax, %rbp
        jnb     .L8
        cmpb    %r12b, (%rbx,%rbp)
        jne     .L3
        leaq    (%rbx,%rbp), %rax
        jmp     .L1
.L3:
        incq    %rbp
        jmp     .L2
.L8:
        xorl    %eax, %eax
.L1:
        popq    %rbx
        popq    %rbp
        popq    %r12
        ret
```

</td>
<td>

```nasm
my_index:
        pushq   %rbp
        movl    %esi, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
        pushq   %rcx
        call    my_strlen
        movq    %rax, %rdx
        movq    %rbx, %rax
        addq    %rbx, %rdx
.L2:
        cmpq    %rdx, %rax
        je      .L8
        leaq    1(%rax), %rcx
        cmpb    %bpl, (%rax)
        je      .L1
        movq    %rcx, %rax
        jmp     .L2
.L8:
        xorl    %eax, %eax
.L1:
        popq    %rdx
        popq    %rbx
        popq    %rbp
        ret
```


</td>
</tr>
</table>

```c
static size_t my_strlen(const char *s){
        size_t len = 0;
        while(s[len] != '\0')
            len++;

        return len;
    }

const char *my_index(const char *s, char v) {
    for (size_t i = 0; i < my_strlen(s); i++)
        if (s[i] == v)
        return &s[i];
        return 0;
}
```

```nasm
my_index:
        pushq   %rbp
        movl    %esi, %ebp
        pushq   %rbx
        movq    %rdi, %rbx
        pushq   %rcx
        call    strlen
        xorl    %edx, %edx
.L2:
        cmpq    %rax, %rdx
        jnb     .L8
        cmpb    %bpl, (%rbx,%rdx)
        jne     .L3
        leaq    (%rbx,%rdx), %rax
        jmp     .L1
.L3:
        incq    %rdx
        jmp     .L2
.L8:
        xorl    %eax, %eax
.L1:
        popq    %rdx
        popq    %rbx
        popq    %rbp
        ret
```

kompilator wstawił my_strlen do my_index. Dzięki temu że dodaliśmy static do my_strlen kompilator wie:
* Funkcja nie jest modyfikowana w innych plikach.
* Funkcja nie ma efektów ubocznych, które są niewidoczne w bieżącym pliku.