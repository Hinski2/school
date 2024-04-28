# zad 5

---

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
//str-a.c
#include <stdio.h>

char *somestr(void);

int main(void) {
  char *s = somestr();
  s[5] = '\0';
  puts(s);
  return 0;
}
```

</td>
<td>

```c
// str-b.c
char *somestr(void) {
  return "Hello, world!";
}
```

</td>
</tr>
</table>

</div>

otzymujemy SIGSEGV w linijce ``s[5] = '\0'`` kod w asm to ``movb $0x0, 0x5(%rax)``, dzieje sie to przez to że tablica charów w str-b.c jest tylko do odczytu, wystarczy zmienić str-b.c by wszystko działało:
```c
// str-b.c
char *somestr(void) {
    static char c[] = "Hello, world!";
    return c;
}
```

Słowo kluczowe static zapewnia, że tablica mutable_string jest inicjalizowana tylko raz i przetrwa przez cały czas życia programu, podobnie jak globalna zmienna, ale z lokalnym zasięgiem.

po wpisaniu nm ./str otrzymamy:
``00000000004c50f0 d c.0``
więc teraz string jest w sekcji data
