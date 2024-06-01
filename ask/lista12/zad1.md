# zad1

---

**aliasing pamięci** to sytuacja, w której dwa lub więcej wskaźników odwołuje się do tego samego obszaru pamięci

**restrict** - mówi kompilatorowi, że wskaźnik jest jedynym wskaźnikiem który wskazuje na dany obiekt 

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
void swap(long *xp, long *yp) {
    *xp = *xp + *yp; /* x+y */
    *yp = *xp - *yp; /* x+y-y = x */
    *xp = *xp - *yp; /* x+y-x = y */
}
```

</td>
<td>

```c
void swap2(long *xp, long *yp) {
    long x = *xp, y = *yp;
    x = x + y, y = x - y, x = x - y;
    *xp = x, *yp = y;
}

```


</td>
</tr>
</table>

</div>

gdyby to xp i xp wskazywały na to samo miejsce w pamięci to po swap *xp i *yp były by prówne 0

### przed zmianą

``` nasm
swap:
        movq    (%rsi), %rax
        addq    (%rdi), %rax
        movq    %rax, (%rdi)
        subq    (%rsi), %rax
        movq    %rax, (%rsi)
        subq    %rax, (%rdi)
        ret
swap2:
        movq    (%rdi), %rax
        movq    (%rsi), %rdx
        movq    %rdx, (%rdi)
        movq    %rax, (%rsi)
        ret
```


### po zmianie

``` c
void swap(long *restrict xp, long *restrict yp) {
    *xp = *xp + *yp; /* x+y */
    *yp = *xp - *yp; /* x+y-y = x */
    *xp = *xp - *yp; /* x+y-x = y */
}

swap:
        movq    (%rsi), %rax
        movq    (%rdi), %rdx
        movq    %rax, (%rdi)
        movq    %rdx, (%rsi)
        ret
```