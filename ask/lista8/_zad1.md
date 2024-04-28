# zad 1

---

**Plik relokowalny:** nazywany również plikiem obiektowym, jest to plik zawierający kod źródłowy skompilowany do postaci maszynowej oraz informacje dotyczące symboli i relokacji. Jest to pośredni etap w procesie kompilacji, który może być łączony (konsolidowany) z innymi plikami relokowalnymi w celu utworzenia końcowego wykonywalnego pliku lub biblioteki.

**Sekcje** w kontekście plików wykonywalnych, bibliotek współdzielonych oraz plików obiektowych są to logiczne części tych plików, które organizują kod maszynowy, dane oraz inne zasoby programu. Sekcje pomagają w strukturyzacji oraz zarządzaniu różnymi elementami programu podczas procesu kompilacji, linkowania oraz wykonania.

Oto kilka typowych sekcji spotykanych w plikach wykonywalnych, bibliotekach współdzielonych oraz plikach obiektowych:

1. .text**: Jest to sekcja, w której przechowywany jest kod maszynowy programu, czyli instrukcje wykonywalne. Ten fragment kodu jest uruchamiany, gdy program jest wykonywany.
2. .data: Sekcja zawierająca globalne zmienne inicjalizowane. Dane w tej sekcji są przechowywane w pamięci i są dostępne zarówno do odczytu, jak i zapisu podczas działania programu.
3. .bss: Ta sekcja zawiera globalne zmienne niezainicjalizowane. Zmienne w tej sekcji zajmują miejsce w pamięci, ale nie są one inicjalizowane wartościami początkowymi. Wartości tych zmiennych są ustawiane na zero podczas uruchamiania programu.
4. .rodata: Sekcja ta zawiera stałe, które są tylko do odczytu podczas działania programu. Przechowuje na przykład stałe znakowe, które nie mogą być modyfikowane.
5. .debug: Sekcja zawierająca informacje debugujące, takie jak mapowanie kodu źródłowego na kod maszynowy, informacje o symbolach, informacje o typach danych itp. Jest to przydatne podczas debugowania programów.
6. .comment: Sekcja ta zawiera komentarze umieszczone w kodzie źródłowym, które mogą być wyświetlane podczas analizy pliku wykonywalnego.

**Zasięg widoczności** określa, gdzie w programie dany symbol jest dostępny:

1.Globalny zasięg: Dostępny dla całego programu.
2.Lokalny zasięg: Dostępny tylko w określonym bloku kodu.
3.Zasięg pliku: Ograniczony do jednego pliku źródłowego.
4.Zasięg zewnętrzny: Dostępny dla innych plików lub modułów.
5.Zasięg wewnętrzny: Ograniczony do jednego modułu lub pliku.



Plik swap.c

```c
extern int printf(const char *, ...);
extern long buf[];

long *bufp0 = &buf[0];
static double sum = 0.0;

static void incr() {
  static int count = 0;
  count++;
  sum += 3.14;
  printf("sum = %f\n", sum);
}

void swap(int i) {
  incr();
  long temp = *bufp0;
  *bufp0 = buf[i];
  buf[i] = temp;
}
```
trzeba wskazań symnole i podać ich zasięg widzialności (local, global, extern):
| symbol | zasięg widzialości | sekcja |
|---|---| --- |
| printf | extern | u
| buff | extern | u
| bufp0 | global | data
| count | local | bss
| sum | local | bss
| incr() | local | text
| swap() | global | text


Plik relokowalny stworzony przy pomocy ``nm swap.o``
```nasm
0000000000000000 r .LC0
0000000000000000 r .LC1
                 U _GLOBAL_OFFSET_TABLE_
                 U buf
0000000000000000 D bufp0
0000000000000000 b count.0
0000000000000000 t incr
                 U printf
0000000000000008 b sum
0000000000000039 T swap
```