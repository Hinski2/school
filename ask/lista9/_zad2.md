# zad2

---

<style>
.full-width-table table {
  width: 100%;
  max-width: fit-content;
  margin-left: auto;
  margin-right: auto;
}
</style>

#### kod w c

<div class="full-width-table">

<table>
<tr>
<td> start.c </td>
<td> odd.c </td>
<td> even.c</td>
</tr>
<tr>
<td>

```c
int is_even(long);

void _start(void) {
  asm volatile(
    "syscall"
    : /* no output */
    : "a" (0x3c), "D" (is_even(42)));
}
```

</td>
<td>

```c
int is_even(long n);

int is_odd(long n) {
  if (n == 0)
    return 0;
  else
    return is_even(n - 1);
}
```

</td>
<td>

```c
int is_odd(long n);

int is_even(long n) {
  if (n == 0)
    return 1;
  else
    return is_odd(n - 1);
}

```

</td>
</tr>
</table>

</div>

#### kod w asemblerze

<div class="full-width-table">

<table>
<tr>
<td> start.s </td>
<td> odd.s </td>
<td> even.s</td>
</tr>
<tr>
<td>

```c
.text
.globl _start
.type _start, @function

_start:
    pushq %rax
    movl $42, %edi
    call is_even
    movl %eax, %edi
    movl $60, %eax
    syscall
    popq %rdx
    ret

.size _start, .-_start
```

</td>
<td>

```c
.text
.globl is_odd
.type is_odd, @function

is_odd:
    testq %rdi, %rdi
    je .L2
    decq %rdi
    jmp is_even

.L2:
    xorl %eax, %eax
    ret

.size is_odd, .-is_odd
```

</td>
<td>

```c
.text
.globl is_even
.type is_even, @function

is_even:
    testq %rdi, %rdi
    je .L2
    decq %rdi
    jmp is_odd

.L2:
    movl $1, %eax
    ret

.size is_even, .-is_even
```

</td>
</tr>
</table>

</div>

### miejsca występowania definicji symboli i referencji do symboli:

```bash
$ nm even.o
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T is_even
                 U is_odd
$ nm odd.o
                 U _GLOBAL_OFFSET_TABLE_
                 U is_even
0000000000000000 T is_odd
$ nm start.o
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T _start
                 U is_even
```

**oznaczenie T** to sekcja .text
**oznaczenie U** to undefined

### czemu nie można wygenerować ostateczniej postaci call i jump
```
$ objdump -dr odd.o

odd.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <is_odd>:
   0:   48 85 ff                test   %rdi,%rdi
   3:   74 08                   je     d <is_odd+0xd>
   5:   48 ff cf                dec    %rdi
   8:   e9 00 00 00 00          jmp    d <is_odd+0xd>
                        9: R_X86_64_PLT32       is_even-0x4
   d:   31 c0                   xor    %eax,%eax
   f:   c3                      ret  


$ objdump -dr start.o

start.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_start>:
   0:   50                      push   %rax
   1:   bf 2a 00 00 00          mov    $0x2a,%edi
   6:   e8 00 00 00 00          call   b <_start+0xb>
                        7: R_X86_64_PLT32       is_even-0x4
   b:   89 c7                   mov    %eax,%edi
   d:   b8 3c 00 00 00          mov    $0x3c,%eax
  12:   0f 05                   syscall 
  14:   5a                      pop    %rdx
  15:   c3                      ret    
```

Instrukcje `call` i `jmp` w asemblerze nie mogą być ostatecznie sformułowane w plikach obiektowych z powodu:

1. **Nieznane miejsca docelowe:** Podczas kompilacji, asembler nie zna lokalizacji wszystkich symboli, szczególnie tych w innych modułach lub bibliotekach.

2. **Relokacje:** Asembler generuje rekordy relokacji dla `call` i `jmp`, wskazujące, że adresy muszą być zaktualizowane przez linkera, kiedy ostateczne lokalizacje symboli będą znane.

3. **Optymalizacje linkera:** Linker może optymalizować układ kodu, co uniemożliwia statyczne określenie adresów podczas kompilacji.

4. **Pozycyjnie niezależny kod (PIC):** Wymaga adresów, które są ustalane dynamicznie, aby kod mógł być wykonany z dowolnego miejsca w pamięci.

5. **Dynamiczne ładowanie:** Adresy funkcji w bibliotekach ładowanych dynamicznie nie są znane do czasu wykonania, uniemożliwiając statyczne rozwiązanie adresów przez asembler.

#### informacje które zostawia asembler dla konsolidatora

Assembler zostawia linijki typu:
```
  6:   e8 00 00 00 00          call   b <_start+0xb>
                        7: R_X86_64_PLT32       is_even-0x4
```

która mówi, że pod adres 7, czyli `e8 [00 00 00 00]` tu w nawiasy ma zostać przypisany rekor relokacji o takim typie `R_X86_64_PLT32` i adresie `is_even`

czyli asembler po zasemblowaniu tego nie wie jaki tutaj ma zostawić adres więc więc zostawia informacje dla konsolidatora mówiącą o tym że musi znależć adres `is_even` i uzupełnić odpowiednią luke

`b <_start+0xb>` to adres następnej instrukcji

**Mapa konsolidacji** (linker map) to dokument wygenerowany przez linker podczas procesu łączenia plików obiektowych w plik wykonywalny lub bibliotekę. Zawiera informacje o lokalizacji sekcji, symboli i adresach, 

### główne zadania konsolidatora
1. **Łączenie Segmentów**: Łączy różne segmenty kodu i danych z plików obiektowych w jedną całość.
2. **Rozwiązywanie Symboli**: Wyszukuje i aktualizuje odniesienia do funkcji i zmiennych tak, aby wskazywały na właściwe miejsca w finalnym pliku.
3. **Obsługa Relokacji**: Modyfikuje adresy w kodzie, tak aby odpowiadały ich faktycznym lokalizacjom po złączeniu różnych części kodu.
4. **Optymalizacja**: Przeprowadza optymalizacje kodu, takie jak eliminacja duplikatów czy złożenie funkcji.
5. **Generowanie Informacji Debugowania**: Włącza informacje niezbędne do debugowania w finalnym produkcie.

```
$ objdump -d start
start:     file format elf64-x86-64


Disassembly of section .text:

00000000004000e8 <.text>:
  4000e8:       48 85 ff                test   %rdi,%rdi
  4000eb:       74 08                   je     0x4000f5
  4000ed:       48 ff cf                dec    %rdi
  4000f0:       e9 06 00 00 00          jmp    0x4000fb
  4000f5:       b8 01 00 00 00          mov    $0x1,%eax
  4000fa:       c3                      ret    
  4000fb:       48 85 ff                test   %rdi,%rdi
  4000fe:       74 08                   je     0x400108
  400100:       48 ff cf                dec    %rdi
  400103:       e9 e0 ff ff ff          jmp    0x4000e8
  400108:       31 c0                   xor    %eax,%eax
  40010a:       c3                      ret    
  40010b:       50                      push   %rax
  40010c:       bf 2a 00 00 00          mov    $0x2a,%edi
  400111:       e8 d2 ff ff ff          call   0x4000e8
  400116:       89 c7                   mov    %eax,%edi
  400118:       b8 3c 00 00 00          mov    $0x3c,%eax
  40011d:       0f 05                   syscall 
  40011f:       5a                      pop    %rdx
  400120:       c3                      ret  
```