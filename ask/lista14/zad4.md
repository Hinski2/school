***DEFINICJE***
### Pełna Asocjacyjność TLB

**TLB (Translation Lookaside Buffer)** to pamięć podręczna, która przechowuje mapowanie wirtualnych adresów na fizyczne. Gdy mówimy, że TLB jest "w pełni asocjacyjne", oznacza to, że każdy wpis w TLB może przechowywać dowolne mapowanie, a wyszukiwanie odbywa się poprzez porównanie całego tagu (numeru strony wirtualnej) z każdym wpisem w TLB.

**Pełna asocjacyjność**:
- Każdy wpis w TLB może zawierać dowolne mapowanie.
- Wyszukiwanie odbywa się przez porównanie całego tagu z każdym wpisem w TLB, co może być kosztowne, ale pozwala na większą elastyczność.
- Umożliwia to bardziej efektywne wykorzystanie pamięci TLB w porównaniu z innymi metodami, np. bezpośrednim mapowaniem czy asocjacyjnością grupową.

### Ofiara

W kontekście pamięci podręcznej (w tym TLB), **ofiara** to wpis, który jest zastępowany nowym wpisem, gdy pamięć podręczna jest pełna i trzeba zwolnić miejsce. W pełni asocjacyjnym TLB, decyzja o wyborze ofiary jest podejmowana na podstawie algorytmu zastępowania, takiego jak **LRU (Least Recently Used)**, który wybiera najmniej używany wpis jako ofiarę do zastąpienia.

### Wtoczenie (Swap-in)

**Wtoczenie** (ang. swap-in) odnosi się do procesu przenoszenia strony z pamięci zewnętrznej (dysku) do pamięci głównej. Dzieje się to, gdy proces potrzebuje dostępu do strony, która aktualnie znajduje się na dysku. Proces ten obejmuje:
- Znalezienie wolnej ramki w pamięci głównej lub wybranie ramki do zastąpienia (ofiara).
- Skopiowanie strony z dysku do pamięci głównej.
- Aktualizacja odpowiednich struktur danych, takich jak tablica stron, aby odzwierciedlić nowe mapowanie.

### Błąd Strony

**Błąd strony** (ang. page fault) występuje, gdy proces próbuje uzyskać dostęp do strony, która nie znajduje się w pamięci głównej. Może to być spowodowane:
- Strona znajduje się na dysku (strona została wcześniej wyparta z pamięci głównej).
- Strona nigdy nie była załadowana do pamięci (np. podczas inicjalizacji procesu).

Gdy wystąpi błąd strony, system operacyjny musi:
1. Przerwać wykonanie bieżącego procesu.
2. Zlokalizować brakującą stronę na dysku.
3. Wtoczyć stronę z dysku do pamięci głównej.
4. Aktualizować tablicę stron i inne struktury danych, aby odzwierciedlić nowe mapowanie.
5. Wznowić wykonanie procesu.

### Przykład Analizy

Oto jak przebiega analiza dostępów do pamięci z wcześniejszego przykładu w kontekście tych pojęć:

1. **Adres 0x123d (VPN: 0x1, Offset: 0x23d)**
   - **TLB Miss**: VPN 0x1 nie jest obecny w TLB.
   - **Page Table Miss**: VPN 0x1 nie jest w pamięci głównej (jest na dysku).
   - **Page Fault**: System musi wtoczyć stronę z dysku.
   - **Swap-in**: Strona jest ładowana do nowej ramki w pamięci głównej, tablica stron i TLB są aktualizowane.

2. **Adres 0x08b3 (VPN: 0x2, Offset: 0x8b3)**
   - **TLB Miss**: VPN 0x2 nie jest obecny w TLB.
   - **Page Table Miss**: VPN 0x2 nie jest w pamięci głównej (jest na dysku).
   - **Page Fault**: System musi wtoczyć stronę z dysku.
   - **Swap-in**: Strona jest ładowana do nowej ramki w pamięci głównej, tablica stron i TLB są aktualizowane.

3. **Adres 0x365c (VPN: 0x3, Offset: 0x65c)**
   - **TLB Hit**: VPN 0x3 jest obecny w TLB.
   - Brak potrzeby działania, ponieważ strona jest już w pamięci głównej.

4. **Adres 0x871b (VPN: 0x8, Offset: 0x71b)**
   - **TLB Miss**: VPN 0x8 nie jest obecny w TLB.
   - **Page Table Miss**: VPN 0x8 nie jest w pamięci głównej (jest na dysku).
   - **Page Fault**: System musi wtoczyć stronę z dysku.
   - **Swap-in**: Strona jest ładowana do nowej ramki w pamięci głównej, tablica stron i TLB są aktualizowane.

5. **Adres 0xbee6 (VPN: 0xb, Offset: 0xee6)**
   - **TLB Hit**: VPN 0xB jest obecny w TLB.
   - Brak potrzeby działania, ponieważ strona jest już w pamięci głównej.

6. **Adres 0x3140 (VPN: 0x3, Offset: 0x140)**
   - **TLB Hit**: VPN 0x3 jest obecny w TLB.
   - Brak potrzeby działania, ponieważ strona jest już w pamięci głównej.

7. **Adres 0xc049 (VPN: 0xc, Offset: 0x049)**
   - **TLB Miss**: VPN 0xC nie jest obecny w TLB.
   - **Page Table Miss**: VPN 0xC nie jest w pamięci głównej (jest na dysku).
   - **Page Fault**: System musi wtoczyć stronę z dysku.
   - **Swap-in**: Strona jest ładowana do nowej ramki w pamięci głównej, tablica stron i TLB są aktualizowane.

W ten sposób każdy dostęp do pamięci jest analizowany pod kątem obecności w TLB, tablicy stron i konieczności wtoczenia strony z dysku.

### Ustalanie ostatecznego stanu TLB i tablicy stron po dostępie do pamięci

Przyjmijmy następujące założenia:
- Strony mają rozmiar 4 KiB, czyli offset wynosi 12 bitów.
- TLB jest w pełni asocjacyjny z zastępowaniem LRU.
- Początkowy stan TLB i tablicy stron jest podany.

Zacznijmy od rozbicia adresów na VPN i offset:

### Adresy:
1. **Adres: 0x123d**
   - VPN: 0x1
   - Offset: 0x23d

2. **Adres: 0x08b3**
   - VPN: 0x2
   - Offset: 0x8b3

3. **Adres: 0x365c**
   - VPN: 0x3
   - Offset: 0x65c

4. **Adres: 0x871b**
   - VPN: 0x8
   - Offset: 0x71b

5. **Adres: 0xbee6**
   - VPN: 0xb
   - Offset: 0xee6

6. **Adres: 0x3140**
   - VPN: 0x3
   - Offset: 0x140

7. **Adres: 0xc049**
   - VPN: 0xc
   - Offset: 0x049

### Stan początkowy TLB:
- Wartości Tagów to numery VPN.
- PPN to numery fizycznych stron.

### Stan początkowy tablicy stron:
- VPN są numerami stron wirtualnych.
- PPN są numerami stron fizycznych.
- Strony na dysku są oznaczone jako "dysk".

### Dostępy do pamięci:

#### 1. Adres: 0x123d (VPN: 0x1, Offset: 0x23d)

- Szukamy VPN 0x1 w TLB: Brak (miss)
- Szukamy VPN 0x1 w tablicy stron: Valid=0, PPN=dysk (miss)
- Swap-in strony z dysku do następnej dostępnej ramki:
  - Nowy PPN: 0x0D (najwyższy obecny to 0x0C, więc bierzemy następny)
  - Aktualizacja tablicy stron:
    - VPN 0x1: Valid=1, PPN=0x0D
- Aktualizacja TLB:
  - Najstarszy wpis do zastąpienia (LRU=3): TLB[3]
  - TLB[3] = {Valid=1, Tag=0x1, LRU=0, PPN=0x0D}

#### 2. Adres: 0x08b3 (VPN: 0x2, Offset: 0x8b3)

- Szukamy VPN 0x2 w TLB: Brak (miss)
- Szukamy VPN 0x2 w tablicy stron: Valid=0, PPN=dysk (miss)
- Swap-in strony z dysku do następnej dostępnej ramki:
  - Nowy PPN: 0x0E
  - Aktualizacja tablicy stron:
    - VPN 0x2: Valid=1, PPN=0x0E
- Aktualizacja TLB:
  - Najstarszy wpis do zastąpienia (LRU=2): TLB[2]
  - TLB[2] = {Valid=1, Tag=0x2, LRU=0, PPN=0x0E}

#### 3. Adres: 0x365c (VPN: 0x3, Offset: 0x65c)

- Szukamy VPN 0x3 w TLB: Trafienie (hit)
  - Aktualizacja LRU: TLB[2].LRU = 3

#### 4. Adres: 0x871b (VPN: 0x8, Offset: 0x71b)

- Szukamy VPN 0x8 w TLB: Brak (miss)
- Szukamy VPN 0x8 w tablicy stron: Valid=0, PPN=dysk (miss)
- Swap-in strony z dysku do następnej dostępnej ramki:
  - Nowy PPN: 0x0F
  - Aktualizacja tablicy stron:
    - VPN 0x8: Valid=1, PPN=0x0F
- Aktualizacja TLB:
  - Najstarszy wpis do zastąpienia (LRU=1): TLB[1]
  - TLB[1] = {Valid=1, Tag=0x8, LRU=0, PPN=0x0F}

#### 5. Adres: 0xbee6 (VPN: 0xb, Offset: 0xee6)

- Szukamy VPN 0xB w TLB: Trafienie (hit)
  - Aktualizacja LRU: TLB[0].LRU = 3

#### 6. Adres: 0x3140 (VPN: 0x3, Offset: 0x140)

- Szukamy VPN 0x3 w TLB: Trafienie (hit)
  - Aktualizacja LRU: TLB[2].LRU = 3

#### 7. Adres: 0xc049 (VPN: 0xc, Offset: 0x049)

- Szukamy VPN 0xC w TLB: Brak (miss)
- Szukamy VPN 0xC w tablicy stron: Valid=0, PPN=brak (miss)
- Swap-in strony z dysku do następnej dostępnej ramki:
  - Nowy PPN: 0x10
  - Aktualizacja tablicy stron:
    - VPN 0xC: Valid=1, PPN=0x10
- Aktualizacja TLB:
  - Najstarszy wpis do zastąpienia (LRU=3): TLB[3]
  - TLB[3] = {Valid=1, Tag=0xC, LRU=0, PPN=0x10}

### Ostateczny stan TLB:
| Valid | Tag | LRU | PPN |
|-------|-----|-----|-----|
| 1     | 0xB | 3   | 0x0C|
| 1     | 0x8 | 2   | 0x0F|
| 1     | 0x3 | 3   | 0x06|
| 1     | 0xC | 0   | 0x10|

### Ostateczny stan tablicy stron:
| VPN | Valid | PPN |
|-----|-------|-----|
| 00  | 1     | 05  |
| 01  | 1     | 0D  |
| 02  | 1     | 0E  |
| 03  | 1     | 06  |
| 04  | 1     | 09  |
| 05  | 1     | 0B  |
| 06  | 0     | dysk|
| 07  | 1     | 04  |
| 08  | 1     | 0F  |
| 09  | 0     | dysk|
| 0A  | 1     | 03  |
| 0B  | 1     | 0C  |
| 0C  | 1     | 10  |

Wszystkie wpisy, które były swap-in są teraz Valid i mają odpowiednie nowe numery ramek.