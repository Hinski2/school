# zad 4

---

* `przestrzeń adresowa` - zbiór adresów wirtualnych, pod którymi proces „widzi” swój kod, dane, stertę (heap), stos itd.
* `wywołąnia systemowe` - kontrolowane przejście z trybu użytkownika do trybu jądra, by popraciś OS o usługę niedostępną dla programu w trybie użytkownika. przyklad: open, read, write, fork

---
mamy:
* 16 resestrów ogólnego przeznaczenia 64 bitowe
* 16 rejestrów SSE (SIMD: xmm), 128 bity
* 8 rejestrów x87 dla liczb zmiennopozycyjnych, 80 bity
* 16 rejestrów AVX (SIMD: ymm), 265 bity

![img](/stack_frame.png)

* koniec stosu musi być wyrównany do 16, czyli `(%rsp + 8)` jest wielokrotnością 16

### w jaki sposób jądro musi przygowtać przygotować przestrzeń adresową procesu

1. trzeba załadować program do pamięci
2. tworzony jest stos użytkownika z argc, argv[], envp[], auxv (auxiliary vector)
3. wyrównanie stosu: `%rsp` musi być wyrównane do 16
4. przygotowanie rejestrów:
    * `%rbp` - nieokreślony ale user code powinien ustawić go na 0
    * `%rsp` - (wspaźnik stosu) zawsze wyrównany do 16 bajtów
    * `%rdx` - zawiera wskaźnik do funkcji którą program powinien wywołać przy atexit()
5. proces dostaje kopie plików 


### co musi znajdować sie na stosie w momencie wywołania procedury \<\<_start>>

![img](/initial_process_stack.png)
na stosie musi się znajdować:
* argc (liczba argumentóœ )
* argv (wskaźniki do argumentów)
* envp (wspaźniki do zmiennych srodowiskowych)
* auxuiliary vector - dodatkowe informacje 


* fpu - wszystkie wyjątki zamaskowane
* SIMD - maski wyjątków zamaskowane
* rFLAGS register - wszystskie flagi powinny być ustawione na neutralne


### Do czego służy auxiliary vector
auxiliary vector to tablica struktur, przekazyawna programowi przy starcie, interpretowana zgodnie z `a_type`. jest to tablica metadanych o procesie

``` c
typedef struct {
    int a_type;
    union {
        long a_val;
        void *a_ptr;
        void (*a_fnc)();
    } a_un;
} auxv_t;
```

![img](/aux_vec_types.png)

---

### w jaki sposób wywołać funcję jadra
można tylko przekazać wartości należące do klasy INTEGER albo MEMORY
funkcje jądra wywołujemy używajac syscall, numer syscall musi być przekazany rejestrem `%rax`.
podcas systemcall jądro niszczy rejestry `%rcx, %r11`

### w jakich rejestrach umieścić argumenty
funkcje jądra:       `%rdi, %rsi, %rdx, %r10, %r8, %r9`
funkcje użytkownika: `%rdi, %rsi, %rdx, %rcx, %r8, %r9`

w funkcjach jądra nie mozna używać stosu

### gdzie można spodziewać się wyników
rejestry `%rax` pozioda rezultat system-calla. 

### jak jądro sygnalizuje niepowodzenie wywołania systemowego
wartości [-4095, -1] wskazują na error równy -errno