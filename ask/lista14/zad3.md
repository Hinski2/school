### Translacja Adresów:

Aby przeprowadzić translację adresów w systemie pamięci podręcznej, najpierw należy zrozumieć format adresu w tym systemie. Załóżmy, że adres ma następującą strukturę:

- Adres logiczny składa się z VPN (Virtual Page Number) oraz offsetu.
- Adres fizyczny składa się z PPN (Physical Page Number) oraz offsetu.
- Struktura adresu logicznego:
  - 4 bity VPN
  - 8 bitów offsetu

W celu uproszczenia, założymy, że VPN to 4 najwyższe bity adresu, a offset to pozostałe 8 bitów.

Adresy, które mają być translacji to: 0x027c, 0x03a9, 0x0040.

### Krok 1: Podziel adresy na VPN i offset

1. Adres 0x027c:
   - VPN: 0x2 (0010)
   - Offset: 0x7c

2. Adres 0x03a9:
   - VPN: 0x3 (0011)
   - Offset: 0xa9

3. Adres 0x0040:
   - VPN: 0x0 (0000)
   - Offset: 0x40

### Krok 2: Translacja VPN na PPN

#### Adres 0x027c:

- VPN: 0x2
- Szukamy w TLB:
  - Zbiór 0, Tag 0x2, PPN 0x17, V = 1 -> Trafienie
  - PPN = 0x17
- Adres fizyczny: PPN 0x17, offset 0x7c
- Fizyczny adres: 0x17 * 0x100 + 0x7c = 0x17 * 256 + 124 = 0x17 * 256 + 124 = 0x17ac

#### Adres 0x03a9:

- VPN: 0x3
- Szukamy w TLB:
  - Zbiór 1, Tag 0x3, PPN 0x2D, V = 1 -> Trafienie
  - PPN = 0x2D
- Adres fizyczny: PPN 0x2D, offset 0xa9
- Fizyczny adres: 0x2D * 0x100 + 0xa9 = 0x2D * 256 + 169 = 0x2D * 256 + 169 = 0x2da9

#### Adres 0x0040:

- VPN: 0x0
- Szukamy w TLB:
  - Zbiór 0, Tag 0x0, PPN 0x09, V = 1 -> Trafienie
  - PPN = 0x09
- Adres fizyczny: PPN 0x09, offset 0x40
- Fizyczny adres: 0x09 * 0x100 + 0x40 = 0x09 * 256 + 64 = 0x09 * 256 + 64 = 0x0940

### Krok 3: Translacja Adresów do Pamięci Podręcznej

Adresy fizyczne do translacji w pamięci podręcznej:

1. Adres fizyczny: 0x17ac
   - Indeks: 0xac % 16 = 0xc
   - Tag: 0x17
   - Sprawdzamy pamięć podręczną pod indeksem 0xc:
     - Tag: -
     - Nie trafienie w pamięci podręcznej

2. Adres fizyczny: 0x2da9
   - Indeks: 0xa9 % 16 = 0x9
   - Tag: 0x2D
   - Sprawdzamy pamięć podręczną pod indeksem 0x9:
     - Tag: -
     - Nie trafienie w pamięci podręcznej

3. Adres fizyczny: 0x0940
   - Indeks: 0x40 % 16 = 0x0
   - Tag: 0x09
   - Sprawdzamy pamięć podręczną pod indeksem 0x0:
     - Tag: 0x19 (nie trafienie)
     - Tag: 0x09
     - Trafienie w pamięci podręcznej
     - Dane: DE 01 C4 32

Podsumowanie translacji:

1. Adres 0x027c:
   - Adres fizyczny: 0x17ac
   - Nie trafienie w pamięci podręcznej

2. Adres 0x03a9:
   - Adres fizyczny: 0x2da9
   - Nie trafienie w pamięci podręcznej

3. Adres 0x0040:
   - Adres fizyczny: 0x0940
   - Trafienie w pamięci podręcznej
   - Dane: DE 01 C4 32