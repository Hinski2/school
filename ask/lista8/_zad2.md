# zad2

---

#### co przechowuje .shstrtab:
Section Header String Table (.shstrtab): Zawiera nazwy sekcji używane w pliku ELF. Każdy nagłówek sekcji wskazuje na swoją nazwę poprzez indeks w tej tabeli. Narzędzia, które czytają i analizują pliki ELF, takie jak readelf czy objdump, korzystają z tej tabeli, aby wyświetlić nazwy sekcji podczas raportowania struktury pliku ELF.

#### co przechowuje .strtab:
String Table (.strtab): Przechowuje ciągi znaków, przeważnie są to nazwy symboli używane w tabeli symboli. Narzędzia takie jak linkery i debuggery wykorzystują tę tabelę do odnalezienia nazw symboli, które są potrzebne do powiązań (relokacji) oraz do celów debugowania.

Obie te sekcje ułatwiają zarządzanie i identyfikację różnych części pliku ELF, pozwalają na łatwe odniesienie się do nazw symboli i sekcji poprzez indeksy, co jest znacznie bardziej efektywne niż przechowywanie pełnych nazw w każdym miejscu, gdzie mogą być one potrzebne.

#### Elf64_Sym
Rekord symbolu Elf64_Sym w formacie ELF dla systemów 64-bitowych zawiera kluczowe informacje o symbolach przechowywanych w tabeli symboli. Oto skrócone znaczenie każdego z pól w tym rekordzie:

* st_name: Indeks do tabeli stringów symboli, określający nazwę symbolu.
* st_value: Wartość symbolu, często adres w pamięci, gdzie symbol jest zlokalizowany.
* st_size: Rozmiar symbolu, na przykład liczba bajtów dla obiektów danych.
* st_info: Zawiera informacje o typie symbolu (funkcja, zmienna itp.) i jego powiązaniu (lokalny, globalny, słaby itp.).
* st_other: Określa widoczność symbolu (domyślna, ukryta itp.) i zawiera inne flagi.
* st_shndx: Indeks do tabeli nagłówków sekcji, wskazujący sekcję związaną z symbolem.

Każde pole jest istotne dla systemu linkera i ładowacza oraz narzędzi do debugowania, aby zrozumieć, jak odwołać się do symboli, zarządzać nimi i w jaki sposób powinny być traktowane w trakcie wykonania programu.


#### Tablica Symboli (Symbol Table)

- **Przechowywanie Symboli:** Zawiera nazwy funkcji, zmiennych globalnych i identyfikatorów.
- **Informacje o Symbolach:** Zawiera typ, zakres, adres i rozmiar każdego symbolu.
- **Relokacje:** Używana do modyfikacji adresów symboli podczas linkowania.
- **Rozwiązanie Symboli:** Linker rozwiązuje odwołania do symboli między różnymi plikami.
- **Debugowanie:** Umożliwia debuggerom mapowanie adresów na nazwy symboli.
- **Dynamiczne Linkowanie:** Pomaga dynamicznemu ładowaczowi w lokalizacji symboli w czasie wykonywania programu.

#### po co nam ELF64_Shrd
* Organizacja Pliku: Definiują strukturę pliku, umożliwiając efektywne mapowanie zawartości na pamięć.
* Zarządzanie Pamięcią: Pozwalają na właściwe umieszczanie sekcji w pamięci podczas ładowania pliku.
* Linkowanie: Dostarczają informacji potrzebnych do poprawnego linkowania symboli i sekcji.
* Ładowanie Dynamiczne: Wspierają identyfikację i lokalizację sekcji w czasie wykonywania dla bibliotek dzielonych.
* Wsparcie dla Narzędzi Deweloperskich: Umożliwiają debuggery i inne narzędzia do inspekcji i modyfikacji programów.
* Optymalizacja Wydajności: Zapewniają właściwe wyrównanie sekcji, co wpływa na szybkość dostępu do pamięci.
* Nagłówki sekcji są więc niezbędne dla efektywnego wykorzystania zasobów systemowych i sprawnego działania aplikacji.

#### Elf64_Shdr - Nagłówek Sekcji

- **`sh_name`:** Indeks do nazwy sekcji w tabeli stringów.
- **`sh_type`:** Określa zawartość i semantykę sekcji.
- **`sh_flags`:** Flagi reprezentujące różne atrybuty.
- **`sh_addr`:** Adres, gdzie pierwszy bajt sekcji powinien się znajdować w pamięci.
- **`sh_offset`:** Przesunięcie bajtowe od początku pliku do pierwszego bajtu sekcji.
- **`sh_size`:** Rozmiar sekcji w bajtach.
- **`sh_link`:** Indeks tabeli nagłówków sekcji, użycie zależy od typu sekcji.
- **`sh_info`:** Dodatkowe informacje, interpretacja zależy od typu sekcji.
- **`sh_addralign`:** Ograniczenia dotyczące wyrównania adresowego sekcji.
- **`sh_entsize`:** Rozmiar w bajtach każdego wpisu dla sekcji z wpisami o stałym rozmiarze.


```c
//swap.c
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

Wynik komendy ``readelf -t -s swap.o``
```nasm
There are 15 section headers, starting at offset 0x750:

Section Headers:
  [Nr] Name
       Type              Address          Offset            Link
       Size              EntSize          Info              Align
       Flags
  [ 0] 
       NULL             0000000000000000  0000000000000000  0
       0000000000000000 0000000000000000  0                 0
       [0000000000000000]: 
  [ 1] .text
       PROGBITS         0000000000000000  0000000000000040  0
       000000000000006b 0000000000000000  0                 1
       [0000000000000006]: ALLOC, EXEC
  [ 2] .rela.text
       RELA             0000000000000000  00000000000005f0  12
       00000000000000c0 0000000000000018  1                 8
       [0000000000000040]: INFO LINK
  [ 3] .data
       PROGBITS         0000000000000000  00000000000000ab  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000003]: WRITE, ALLOC
  [ 4] .bss
       NOBITS           0000000000000000  00000000000000b0  0
       0000000000000010 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 5] .rodata.str1.1
       PROGBITS         0000000000000000  00000000000000b0  0
       000000000000000a 0000000000000001  0                 1
       [0000000000000032]: ALLOC, MERGE, STRINGS
  [ 6] .data.rel
       PROGBITS         0000000000000000  00000000000000c0  0
       0000000000000008 0000000000000000  0                 8
       [0000000000000003]: WRITE, ALLOC
  [ 7] .rela.data.rel
       RELA             0000000000000000  00000000000006b0  12
       0000000000000018 0000000000000018  6                 8
       [0000000000000040]: INFO LINK
  [ 8] .rodata.cst8
       PROGBITS         0000000000000000  00000000000000c8  0
       0000000000000008 0000000000000008  0                 8
       [0000000000000012]: ALLOC, MERGE
  [ 9] .comment
       PROGBITS         0000000000000000  00000000000000d0  0
       000000000000002c 0000000000000001  0                 1
       [0000000000000030]: MERGE, STRINGS
  [10] .note.GNU-stack
       PROGBITS         0000000000000000  00000000000000fc  0
       0000000000000000 0000000000000000  0                 1
       [0000000000000000]: 
  [11] .note.gnu.property
       NOTE             0000000000000000  0000000000000100  0
       0000000000000020 0000000000000000  0                 8
       [0000000000000002]: ALLOC
  [12] .symtab
       SYMTAB           0000000000000000  0000000000000120  13
       00000000000003d8 0000000000000018  37                8
       [0000000000000000]: 
  [13] .strtab
       STRTAB           0000000000000000  00000000000004f8  0
       00000000000000f6 0000000000000000  0                 1
       [0000000000000000]: 
  [14] .shstrtab
       STRTAB           0000000000000000  00000000000006c8  0
       0000000000000088 0000000000000000  0                 1
       [0000000000000000]: 

Symbol table '.symtab' contains 41 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 .bss
     2: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    1 .Ltext0
     3: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    5 .LC1
     4: 0000000000000000    57 FUNC    LOCAL  DEFAULT    1 incr
     5: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    1 .LFB0
     6: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU1
     7: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU2
     8: 0000000000000002     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU3
     9: 0000000000000000     4 OBJECT  LOCAL  DEFAULT    4 count.0
    10: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU4
    11: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU5
    12: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    8 .LC0
    13: 0000000000000008     8 OBJECT  LOCAL  DEFAULT    4 sum
    14: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU6
    15: 0000000000000034     0 NOTYPE  LOCAL  DEFAULT    1 .LVL0
    16: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU7
    17: 0000000000000039     0 NOTYPE  LOCAL  DEFAULT    1 .LFE0
    18: 0000000000000039     0 NOTYPE  LOCAL  DEFAULT    1 .LVL1
    19: 0000000000000039     0 NOTYPE  LOCAL  DEFAULT    1 .LFB1
    20: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU9
    21: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU10
    22: 000000000000004a     0 NOTYPE  LOCAL  DEFAULT    1 .LVL2
    23: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU11
    24: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU12
    25: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU13
    26: 0000000000000054     0 NOTYPE  LOCAL  DEFAULT    1 .LVL3
    27: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU14
    28: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU15
    29: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU16
    30: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU17
    31: 0000000000000001     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU18
    32: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU19
    33: 000000000000006a     0 NOTYPE  LOCAL  DEFAULT    1 .LVL4
    34: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  ABS .LVU20
    35: 000000000000006b     0 NOTYPE  LOCAL  DEFAULT    1 .LFE1
    36: 000000000000006b     0 NOTYPE  LOCAL  DEFAULT    1 .Letext0
    37: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf
    38: 0000000000000039    50 FUNC    GLOBAL DEFAULT    1 swap
    39: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    6 bufp0
    40: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND buf
```

Polecenie readelf z opcjami -t -s na pliku swap.o dostarcza informacji o tabelach symboli oraz o nagłówkach sekcji pliku obiektowego. 

#### Lokalizacja Nagłówków Sekcji i Zawartości Sekcji
Informacja o lokalizacji nagłówków sekcji oraz zawartości poszczególnych sekcji w pliku relokowalnym jest zawarta w nagłówkach sekcji, a szczególnie w polach Offset i Address. Offset wskazuje, gdzie w pliku zaczyna się sekcja, a Address wskazuje, gdzie powinna znaleźć się sekcja w pamięci podczas wykonania.

#### Pozycja Symbolu względem Początku Sekcji
Pozycję danego symbolu względem początku sekcji można określić na podstawie wartości w polu Value, które wskazuje adres symbolu względem początku sekcji, do której jest przypisany. Wartość Value jest zazwyczaj offsetem od początku sekcji, gdzie sekcja jest określona przez Ndx.