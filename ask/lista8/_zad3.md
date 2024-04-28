# zad3

---

<table>
<tr>
<td> mismatch-a.c </td> <td> mismatch-b.c </td>
</tr>
<tr>
<td>

```c
void p2(void);

int main() {
  p2();
  return 0;
}

```

</td>
<td>
    
```c
#include <stdio.h>

char main;

void p2() {
  printf("0x%x\n", main);
}

```
</td>
</tr>
</table>

### czemu to działa?:
Program ten drukuje pewien ciąg znaków i kończy działanie bez zgłoszenia błędu, ponieważ odwołuje się do zmiennej main z pliku "mismatch-b.c", która nie została zainicjowana, więc jej wartość jest nieokreślona.


### z kąd pochodzi wydrukowana wartość?:
Wartość wydrukowana przez funkcję p2 pochodzi z pamięci, gdzie jest przechowywana zmienna main. Ponieważ zmienna ta nie została zainicjowana, jej wartość będzie nieokreślona i może zawierać losowe dane, które są w pamięci w momencie wykonania programu.

### symbol silny vs słaby:
Symbol silny i słaby różnią się sposobem, w jaki są traktowane przez linker podczas procesu łączenia:

* Symbol silny: To symbol, który musi być zdefiniowany dokładnie raz w całym programie. Jeśli jest kilka definicji silnych tego samego symbolu, linker zgłosi błąd.
* Symbol słaby: To symbol, który nie musi być zdefiniowany. Jeśli jest wiele definicji słabego symbolu, to linker wybierze jedną z nich i zignoruje pozostałe.

### co gdybyśmy w funkcji p2 przypisali wartość pod zmienną main
```c
//dla takeigo kodu  otzymuje segmentaion fault
#include <stdio.h>

char main;

void p2() {
  main = 'd';
  printf("0x%x\n", main);
}
```

```
Segmentation fault
```

### co jeśli zainicjowalibyśmy zmienną main w pliku "mismatch-b.c"
```
gcc -static -static -o mismatch mismatch-a.o mismatch-b.o
/usr/bin/ld: mismatch-b.o:(.data+0x0): multiple definition of `main'; mismatch-a.o:(.text+0x0): first defined here
collect2: error: ld returned 1 exit status
make: *** [Makefile:35: mismatch] Error 
```

### Przekazywanie opcji -fno-common do kompilatora jest dobrym pomysłem z kilku powodów:

* Uniknięcie niejednoznaczności: Domyślnie w niektórych kompilatorach, takich jak GCC, jeśli zmienna jest zadeklarowana, ale nie zdefiniowana w jednym pliku źródłowym, to kompilator traktuje ją jako symbol "common" i inicjuje ją wartością zero. Jednak to zachowanie może prowadzić do niejednoznaczności, zwłaszcza gdy różne pliki źródłowe zawierają deklaracje zmiennych o tej samej nazwie, ale różnej inicjalizacji.
* Zapobieganie błędom podczas łączenia: Użycie -fno-common wymusza bardziej rygorystyczne podejście do zmiennych "common". Jeśli zmienna jest zadeklarowana w jednym pliku źródłowym i zdefiniowana w innym, a opcja -fno-common jest ustawiona, to linker zgłosi błąd, co pomaga wykryć potencjalne problemy w kodzie.
* Kontrola nad zachowaniem programu: Ustawienie -fno-common pozwala programiście na bardziej precyzyjne kontrolowanie zachowania programu, eliminując niejednoznaczności i nieoczekiwane wyniki związane z deklaracją i definicją zmiennych.
* Poprawa przenośności kodu: Użycie -fno-common może poprawić przenośność kodu między różnymi kompilatorami i platformami, ponieważ wymusza ono bardziej jednoznaczne zachowanie związane z deklaracją i definicją zmiennych "common".
