# zad3

---

* `sekcja` - fragment programu w pliku wykonywalnym, każda sekcja ma określone dane i przeznaczenie np
    * .text -> kod programu 
    * .data -> dane zainicjalizowane
    * .bss -> dane niezainicjalizowane
    * .rodoata -> dane tylo do odczytu

* `segment` - grupa sekcji o podobnych właściwościach załadowana do pamięci RAM
* `nagłówki programu` - początek pliku wykonywalnego, zawieracjący metadane potrzebne do wykonania programu np.
    * typ pliku
    * adres startowy programu (pod jakim adresem jest main)
    * rozmiary i adresy segmenów
    * tablice sekcji i tablice segmentów 

---

### składowe pliku wykonywalengo

* nagłówek pliku - zawiera metadane programu
* section headers - opisuje sekcje w pliku
* program headers - opisuje segmenty, czyli co i jak trzeba załadować do pamięci
* sekcje - jako faktyczna zawartosć programu
* symbol table - lista wszystkich funkcji i zmiennych globalnych w programie
* tablica relokacji - inforamcje ktore adresy w kodzie lub dzanych przeba poprawić 

---

### czym rózni się sekcja od segmentu

sekcja zaweira inforamcje potrzebne przy relokacji i linkowaniu
segment zawiera informacje które są potrzebne podczas działania programu

---

### co opisują nagłówki programu

* typ pliku
* adres startowy programu (pod jakim adresem jest main)
* rozmiary i adresy segmenów
* tablice sekcji i tablice segmentów 


---

### skąd os wie pod jakim adresem ma umieścić segmenty programu i gdzie położona jest pierwsza instrukcja programu

skąd wie gdzie jset polozona pierwsza instrukcja porgramu: jest napisane w ELF Header: `Entry point address:               0x1110`, 

skąd os wie pod jakim adresem ma umieścić segmenty programu: `Start of section headers:          21152 (bytes into file)`


---



``` python
readelf 1_ls -a

ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x1110
  Start of program headers:          64 (bytes into file)
  Start of section headers:          21152 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         14
  Size of section headers:           64 (bytes)
  Number of section headers:         37
  Section header string table index: 36

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .note.gnu.pr[...] NOTE             0000000000000350  00000350
       0000000000000040  0000000000000000   A       0     0     8
  [ 2] .note.gnu.bu[...] NOTE             0000000000000390  00000390
       0000000000000024  0000000000000000   A       0     0     4
  [ 3] .interp           PROGBITS         00000000000003b4  000003b4
       000000000000001c  0000000000000000   A       0     0     1
  [ 4] .gnu.hash         GNU_HASH         00000000000003d0  000003d0
       0000000000000028  0000000000000000   A       5     0     8
  [ 5] .dynsym           DYNSYM           00000000000003f8  000003f8
       0000000000000210  0000000000000018   A       6     1     8
  [ 6] .dynstr           STRTAB           0000000000000608  00000608
       000000000000010d  0000000000000000   A       0     0     1
  [ 7] .gnu.version      VERSYM           0000000000000716  00000716
       000000000000002c  0000000000000002   A       5     0     2
  [ 8] .gnu.version_r    VERNEED          0000000000000748  00000748
       0000000000000040  0000000000000000   A       6     1     8
  [ 9] .rela.dyn         RELA             0000000000000788  00000788
       00000000000000f0  0000000000000018   A       5     0     8
  [10] .rela.plt         RELA             0000000000000878  00000878
       0000000000000150  0000000000000018  AI       5    23     8
  [11] .init             PROGBITS         0000000000001000  00001000
       000000000000001b  0000000000000000  AX       0     0     4
  [12] .plt              PROGBITS         0000000000001020  00001020
       00000000000000f0  0000000000000010  AX       0     0     16
  [13] .text             PROGBITS         0000000000001110  00001110
       000000000000072e  0000000000000000  AX       0     0     16
  [14] .fini             PROGBITS         0000000000001840  00001840
       000000000000000d  0000000000000000  AX       0     0     4
  [15] .rodata           PROGBITS         0000000000002000  00002000
       0000000000000030  0000000000000000   A       0     0     4
  [16] .eh_frame_hdr     PROGBITS         0000000000002030  00002030
       0000000000000064  0000000000000000   A       0     0     4
  [17] .eh_frame         PROGBITS         0000000000002098  00002098
       000000000000016c  0000000000000000   A       0     0     8
  [18] .note.ABI-tag     NOTE             0000000000002204  00002204
       0000000000000020  0000000000000000   A       0     0     4
  [19] .init_array       INIT_ARRAY       0000000000003dd0  00002dd0
       0000000000000008  0000000000000008  WA       0     0     8
  [20] .fini_array       FINI_ARRAY       0000000000003dd8  00002dd8
       0000000000000008  0000000000000008  WA       0     0     8
  [21] .dynamic          DYNAMIC          0000000000003de0  00002de0
       00000000000001e0  0000000000000010  WA       6     0     8
  [22] .got              PROGBITS         0000000000003fc0  00002fc0
       0000000000000028  0000000000000008  WA       0     0     8
  [23] .got.plt          PROGBITS         0000000000003fe8  00002fe8
       0000000000000088  0000000000000008  WA       0     0     8
  [24] .data             PROGBITS         0000000000004070  00003070
       0000000000000010  0000000000000000  WA       0     0     8
  [25] .bss              NOBITS           0000000000004080  00003080
       0000000000000030  0000000000000000  WA       0     0     32
  [26] .comment          PROGBITS         0000000000000000  00003080
       000000000000001b  0000000000000001  MS       0     0     1
  [27] .debug_aranges    PROGBITS         0000000000000000  0000309b
       0000000000000060  0000000000000000           0     0     1
  [28] .debug_info       PROGBITS         0000000000000000  000030fb
       0000000000000bee  0000000000000000           0     0     1
  [29] .debug_abbrev     PROGBITS         0000000000000000  00003ce9
       00000000000003d6  0000000000000000           0     0     1
  [30] .debug_line       PROGBITS         0000000000000000  000040bf
       0000000000000258  0000000000000000           0     0     1
  [31] .debug_str        PROGBITS         0000000000000000  00004317
       00000000000003f6  0000000000000001  MS       0     0     1
  [32] .debug_line_str   PROGBITS         0000000000000000  0000470d
       0000000000000118  0000000000000001  MS       0     0     1
  [33] .debug_loclists   PROGBITS         0000000000000000  00004825
       00000000000001fb  0000000000000000           0     0     1
  [34] .symtab           SYMTAB           0000000000000000  00004a20
       0000000000000480  0000000000000018          35     8     8
  [35] .strtab           STRTAB           0000000000000000  00004ea0
       0000000000000283  0000000000000000           0     0     1
  [36] .shstrtab         STRTAB           0000000000000000  00005123
       0000000000000176  0000000000000000           0     0     1
```