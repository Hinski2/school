# zad9

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
//bar.c
int bar = 42;
short dead[15];
```

</td>
<td>

```c
//foo.c
long foo = 19;
char code[17];
```

</td>
</tr>
</table>

</div>

#### ``objdump -t -h bar.o``
```nasm
bar.o:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000000  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000004  0000000000000000  0000000000000000  00000040  2**2
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          0000001e  0000000000000000  0000000000000000  00000050  2**4
                  ALLOC
  3 .comment      0000002c  0000000000000000  0000000000000000  00000050  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  0000000000000000  0000000000000000  0000007c  2**0
                  CONTENTS, READONLY
  5 .note.gnu.property 00000020  0000000000000000  0000000000000000  00000080  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
SYMBOL TABLE:
0000000000000000 g     O .bss   000000000000001e dead
0000000000000000 g     O .data  0000000000000004 bar
```

rozmiar .data = 4 bajty
rozmiar .bss = 30 bajtów

.data zawiera zmienną int bar -> 4 * 1
.bss zawiera short dead[15] -> 2 * 15

offset obu zmiennych to 0

#### ``objdump -t -h foo.o``

```nasm
foo.o:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .text         00000000  0000000000000000  0000000000000000  00000040  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000008  0000000000000000  0000000000000000  00000040  2**3
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          00000011  0000000000000000  0000000000000000  00000050  2**4
                  ALLOC
  3 .comment      0000002c  0000000000000000  0000000000000000  00000050  2**0
                  CONTENTS, READONLY
  4 .note.GNU-stack 00000000  0000000000000000  0000000000000000  0000007c  2**0
                  CONTENTS, READONLY
  5 .note.gnu.property 00000020  0000000000000000  0000000000000000  00000080  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
SYMBOL TABLE:
0000000000000000 g     O .bss   0000000000000011 code
0000000000000000 g     O .data  0000000000000008 foo
```

rozmiar .data = 8 bajty
rozmiar .bss = 17 bajtów

.data zawiera long foo -> 4 * 1
.bss zawiera char code[17] -> 1 * 17

offset obu zmiennych to 0

#### Proces Częściowej Konsolidacji (ld -r)
Częściowa konsolidacja (partial linking) za pomocą polecenia ld -r scala kilka plików obiektowych w jeden pośredni plik obiektowy. W przeciwieństwie do pełnego linkowania, które generuje plik wykonywalny lub bibliotekę dzieloną, proces ten pozwala na:

* Rozwiązanie wewnętrznych symboli i relokacji między plikami obiektowymi, ale pozostawia nierozwiązane symbole zewnętrzne.
* Umożliwienie późniejszego linkowania (finałowego) do stworzenia ostatecznego pliku wykonywalnego lub biblioteki.

#### merge-1.o vs merge-2.o

<div class="full-width-table">

<table>
<tr>
<td> marge-1.o </td>
<td> marge-2.c </td>
</tr>
<tr>
<td>

```c
.data           0x0000000000000000        0xc
 *(.data)
 .data          0x0000000000000000        0x8 foo.o
                0x0000000000000000                foo
 .data          0x0000000000000008        0x4 bar.o
                0x0000000000000008                bar

.data1
 *(.data1)

.bss            0x0000000000000000       0x3e
 *(.bss)
 .bss           0x0000000000000000       0x11 foo.o
                0x0000000000000000                code
 *fill*         0x0000000000000011        0xf 
 .bss           0x0000000000000020       0x1e bar.o
                0x0000000000000020                dead
```

</td>
<td>

```c
.data           0x0000000000000000       0x10
 *(.data)
 .data          0x0000000000000000        0x4 bar.o
                0x0000000000000000                bar
 *fill*         0x0000000000000004        0x4 
 .data          0x0000000000000008        0x8 foo.o
                0x0000000000000008                foo

.data1
 *(.data1)

.bss            0x0000000000000000       0x31
 *(.bss)
 .bss           0x0000000000000000       0x1e bar.o
                0x0000000000000000                dead
 *fill*         0x000000000000001e        0x2 
 .bss           0x0000000000000020       0x11 foo.o
                0x0000000000000020                code
```

</td>
</tr>
</table>

</div>



**Porównanie Pozycji Symboli i Rozmiarów Sekcji:**
- **Sekcja `.data`:**
  - `merge-1.o`: Rozmiar `0xc` (12 bajtów);
  8 (long) + 4 (int) 
  - `merge-2.o`: Rozmiar `0x10` (16 bajtów);
  4 (int) + 4 (padding) + 8 (long)
- **Sekcja `.bss`:**
  - `merge-1.o`: Rozmiar `0x3e` (62 bajty);
  17 (char []) + 15 (padding) + 30 (short [])
  - `merge-2.o`: Rozmiar `0x31` (49 bajtów);
  30 (short []) + 2 (padding) + 17 (char [])

**Wpływ Kolejności Linkowania:**
  Kolejność linkowania plików źródłowych bezpośrednio wpływa na końcową organizację pamięci, co widać w rozmiarach sekcji i pozycjach symboli.


#### Padding i Wyrównanie przez Linker bez Znajomości Typów C

Linker nie musi znać typów danych języka C, aby odpowiednio zarządzać paddingiem i wyrównaniem. Oto kluczowe źródła informacji, które umożliwiają odpowiednie zarządzanie:

**Metadane z Plików Obiektowych:**
   - Sekcje pliku obiektowego zawierają metadane (`sh_addralign`) określające wymagane wyrównanie.
   - Kompilator dostarcza te informacje w oparciu o typy danych i strukturę kodu.
