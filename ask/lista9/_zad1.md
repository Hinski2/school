# zad1

---

```c
// data.s
	.file	"data.c"
	.text
	.globl	array
	.bss
	.align 32
	.type	array, @object
	.size	array, 800
array:
	.zero	800
	.globl	bar
	.align 8
	.type	bar, @object
	.size	bar, 8
bar:
	.zero	8
	.globl	some
	.section	.data.rel,"aw"
	.align 32
	.type	some, @object
	.size	some, 38
some:
	.quad	weird
	.long	-3
	.zero	4
	.quad	abc
	.quad	foo
	.string	"efghi"
	.section	.rodata
	.type	abc, @object
	.size	abc, 4
abc:
	.string	"abc"
	.globl	foo
	.data
	.align 2
	.type	foo, @object
	.size	foo, 2
foo:
	.value	314
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits

```

```c
//data.c
short foo = 314;

extern int weird(float);

static const char abc[] = "abc";

struct {
  int (*c)(float);
  int b;
  const char *a;
  short *d; 
  char e[];
} some = {
  .c = weird,
  .a = abc,
  .b = -3,
  .d = &foo,
  .e = "efghi",
};

struct {
  float re;
  float im;
} bar;

long array[100];
```

### czym jest sterownik kompilatora?
Sterownik kompilatora, często nazywany także „driverem kompilatora”, to program odpowiedzialny za zarządzanie całym procesem kompilacji kodu źródłowego na określonej platformie. W przypadku narzędzi takich jak gcc w systemie UNIX/Linux, sterownik kompilatora pełni kilka kluczowych funkcji:

* **Orkiestracja Procesu Kompilacji**: Sterownik kompilatora interpretuje argumenty i opcje przekazywane z linii poleceń, decyduje, które programy pomocnicze uruchomić (np. preprocesor, kompilator właściwy, linkier), i w jakiej kolejności. Zarządza również przepływem danych między tymi narzędziami.
* **Obsługa Opcji Kompilacji**: Sterownik analizuje opcje i flagi kompilacji, takie jak optymalizacje, ustawienia debugowania, określenie plików do załączenia, definiowanie makr, a także specyfikacje lokalizacji bibliotek i innych zasobów.
* **Wywoływanie Narzędzi**: Po przetworzeniu opcji sterownik kompilatora wywołuje odpowiednie narzędzia składowe. W przypadku GCC może to być cc1 (kompilator właściwy dla C), as (asembler) i ld (linkier). Każde z tych narzędzi wykonuje konkretną część procesu kompilacji.
* **Raportowanie Błędów i Ostrzeżeń**: Sterownik kompilatora również zbiera i prezentuje komunikaty o błędach i ostrzeżeniach generowane przez narzędzia składowe, ułatwiając użytkownikowi zrozumienie i rozwiązanie problemów związanych z kompilacją.

### czym są dyrektywy asemblera
Dyrektywy asemblera to specjalne instrukcje używane w kodzie asemblera, które sterują procesem kompilacji, ale nie generują bezpośrednio kodu maszynowego. Służą do organizacji programu, zarządzania pamięcią, przypisywania konkretnych zadań do kompilatora lub asemblera oraz do ustawień, które wpływają na sposób, w jaki kod jest generowany i zarządzany. Dyrektywy te są często specyficzne dla danej platformy lub asemblera i nie wykonują żadnych operacji w czasie działania programu. Oto kilka głównych rodzajów dyrektyw asemblera:

1. **Definicja Danych**: Dyrektywy takie jak `.data`, `.bss` czy `.rodata` pozwalają zdefiniować różne sekcje pamięci, w których przechowywane są zmienne, stałe i inne dane.

2. **Alokacja i Inicjalizacja**: Przykładowo, dyrektywy takie jak `.byte`, `.word`, `.long`, `.quad`, `.zero` służą do alokacji pamięci dla zmiennych i opcjonalnie ich inicjalizacji.

3. **Makrodefinicje**: Dyrektywy takie jak `.macro` i `.endm` pozwalają na definiowanie makr, które są blokami kodu wielokrotnego użytku.

4. **Kontrola Przepływu**: Dyrektywy takie jak `.if`, `.endif`, `.else` itp. umożliwiają sterowanie przepływem kompilacji w zależności od określonych warunków.

5. **Symbole i Etykietowanie**: Dyrektywy takie jak `.global` i `.local` definiują zasięg symboli (nazw funkcji, zmiennych itp.).

6. **Organizacja Pamięci i Wyrównanie**: Dyrektywy takie jak `.align` służą do wyrównywania sekcji kodu lub danych do określonych granic w pamięci.

7. **Komentarze i Informacje**: Dyrektywy takie jak `.comment` umożliwiają dołączanie metainformacji do kodu.


### jakie sterowniki kompilatora zostały użyte:
`` gcc -ggdb -Og -Wall -g0 -fno-common -S -o data.s data.c ``

#### co one znaczą:
- `-ggdb`: Opcja ta dodaje rozszerzone informacje debugowania, które są optymalizowane dla GDB (GNU Debugger). Jest to użyteczne dla głębszego debugowania na poziomie źródła.

- `-Og`: Optymalizacja przeznaczona specjalnie do debugowania. Zapewnia rozsądną wydajność wykonania programu przy zachowaniu wysokiej jakości informacji debugowania, co ułatwia analizę programu.

- `-Wall`: Włącza wszystkie podstawowe ostrzeżenia kompilatora, co pomaga w identyfikacji potencjalnych problemów w kodzie źródłowym jeszcze przed etapem wykonania.

- `-g0`: Ta opcja całkowicie wyłącza generowanie informacji debugowania, co jest przydatne, gdy nie potrzebujemy debugować końcowych binariów lub gdy chcemy zminimalizować rozmiar wyjściowy.

- `-fno-common`: Kontroluje, czy nieinicjowane zmienne globalne są umieszczane w wspólnej sekcji pamięci. Ta opcja zmusza kompilator do umieszczania nieinicjowanych globalnych zmiennych w sekcjach `.bss`, co może pomóc w rozwiązaniu problemów związanych z kolizjami nazw w różnych modułach.

- `-S`: Instruuje kompilator, aby zatrzymał proces po wygenerowaniu kodu asemblera. Kod asemblera jest zapisywany do pliku, co umożliwia jego przeglądanie lub ręczną modyfikację.

- `-o`: Opcja ta pozwala na określenie nazwy pliku wyjściowego generowanego przez kompilator, co jest kluczowe dla organizacji wygenerowanych plików w systemie plików.

### jakie dyrektywy asemblera znajdują się w kodzie:
- **`.file "filename"`**: Określa nazwę pliku źródłowego dla informacji debugowania. Jest to użyteczne w procesie debugowania oraz w dokumentacji pliku asemblera.

- **`.text`**: Ustawia sekcję na `.text`, która jest przeznaczona na kod wykonywalny. Jest to standardowa sekcja dla instrukcji maszynowych.

- **`.globl symbol`**: Deklaruje symbol (zmienną lub funkcję) jako globalny, co oznacza, że może być on dostępny w innych plikach lub modułach.

- **`.bss`**: Przełącza do sekcji `.bss`, przeznaczonej na niezainicjowane dane, które są inicjowane zerami przy uruchomieniu programu.

- **`.align n`**: Wyrównuje następny adres do najbliższej wielokrotności `n` bajtów. Jest to ważne dla optymalizacji wydajności dostępu do danych.

- **`.type symbol, @object`** lub **`.type symbol, @function`**: Określa typ danego symbolu, czy to obiekt danych, czy funkcja, co wpływa na sposób ich traktowania przez linkera.

- **`.size symbol, size`**: Określa rozmiar symbolu w bajtach. Jest to użyteczne dla linkera do alokacji odpowiedniej ilości pamięci.

- **`.zero n`**: Rezerwuje `n` bajtów i inicjuje je na zero. Często używane w sekcji `.bss` do tworzenia buforów.

- **`.quad x`**: Umieszcza 64-bitową liczbę lub adres w kodzie. Jest to użyteczne na platformach 64-bitowych do operacji na dużych liczbach czy adresach.

- **`.long x`**: Umieszcza 32-bitową liczbę w kodzie. Jest to standardowy format dla liczb całkowitych w wielu architekturach.

- **`.string "text"`**: Umieszcza null-terminated string w kodzie. Używane do przechowywania tekstowych stałych.

- **`.section name, "flags"`**: Przełącza do konkretnej sekcji o danej nazwie i atrybutach, które mogą określać, czy sekcja jest wykonywalna (`x`), zapisywalna (`w`), czy czytelna (`a`).

- **`.value x`**: Umieszcza 16-bitową wartość w kodzie. Jest to używane głównie na platformach, gdzie jest to standardowy rozmiar dla 'małych' wartości.

- **`.ident "info"`**: Umieszcza identyfikator w pliku wyjściowym. Zwykle zawiera informacje o wersji kompilatora lub inne metadane.

##### Przełączają bieżącą sekcję
Dyrektywy te są używane do zmiany kontekstu bieżącej sekcji, na którą asembler będzie składał kolejne instrukcje lub dane:
- **`.text`**: Przełącza do sekcji kodu wykonywalnego.
- **`.bss`**: Przełącza do sekcji dla niezainicjowanych danych.
- **`.data`**: Przełącza do sekcji dla zainicjowanych danych.
- **`.section name, "flags"`**: Umożliwia przełączenie do innych, mniej standardowych sekcji, z możliwością ustalenia dodatkowych atrybutów.

##### Dopisują zawartość do odpowiednich sekcji
Te dyrektywy umieszczają różne rodzaje danych bezpośrednio w bieżącej sekcji:
- **`.byte`**, **`.word`**, **`.long`**, **`.quad`**: Dopisują liczby o różnych rozmiarach (od 8 do 64 bitów).
- **`.zero n`**: Rezerwuje `n` bajtów zainicjowanych na zero.
- **`.string "text"`**: Dopisuje null-terminated string.
- **`.value x`**: Dopisuje 16-bitową wartość.

##### Modyfikują informacje przechowywane w nagłówku sekcji lub tablicę symboli
Te dyrektywy wpływają na metadane używane przez linker i debugger:
- **`.globl symbol`**: Deklaruje symbol jako globalny, umożliwiając jego użycie w innych jednostkach translacji.
- **`.local symbol`**: Deklaruje symbol jako lokalny, ograniczając jego zasięg do bieżącego pliku.
- **`.type symbol, @object`** lub **`.type symbol, @function`**: Określa typ symbolu (czy to dane, czy funkcja).
- **`.size symbol, size`**: Określa rozmiar symbolu.
- **`.ident "info"`**: Dodaje informacje identyfikacyjne do sekcji komentarza.
