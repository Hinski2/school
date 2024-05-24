# zad 2

#### definicje 
**pamięć sekwencyjno-skojarzeniowa** rodzaj pamięci cache, w której każdy adres pamięci jest mapowany na konkretny zestaw (set) linii cache. W przeciwieństwie do pamięci direct-mapped, gdzie każdemu blokowi pamięci odpowiada dokładnie jedna linia cache, w set-associative cache każdy blok może być przechowywany w dowolnej z kilku linii w przypisanym zestawie.

( czyli to taki direct mapping, ale liczba lini w secie jest rózna od 1)

**Szerokość szyny adresowej** określa, ile unikalnych adresów pamięci można zaadresować.

**Set** w pamięci cache to grupa linii cache, do której może być przypisany blok danych z pamięci głównej

**Blok** w pamięci cache to jednostka danych przenoszona między pamięcią główną a pamięcią cache, zawierająca zazwyczaj kilka bajtów

#### dane:
* **typ pamięci**: sekcyjno-skojarzeniową o dwuelementowych zbiorach
* blok: ma 4 bajty

--- 

* blok ma 4 bajty -> offset to 2 ^ 2
* set ma 4 linie -> idx = 2 ^ 2
* adres może mieć 12 bitów
więc adres to -> [8 tag, 2 idx, 2 offset] 

| Indeks | Znacznik | Valid | B0 | B1 | B2 | B3 |
|--------|----------|-------|----|----|----|----|
| 0      | 00       | 1     | 40 | 41 | 42 | 43 |
|        | 83       | 1     | FE | 97 | CC | D0 |
| 1      | 00       | 1     | 44 | 45 | 46 | 47 |
|        | 83       | 0     | -- | -- | -- | -- |
| 2      | 00       | 1     | 48 | 49 | 4A | 4B |
|        | 40       | 0     | -- | -- | -- | -- |
| 3      | FF       | 1     | 9A | C0 | 03 | FF |
|        | 00       | 0     | -- | -- | -- | -- |

832 -> 10000011 00 10 -> 0x83 0x0 0x3 to jest 43
835 -> 10000011 01 01 -> 0x83 0x1 0x1 to nie jest valid
FFD -> 11111111 11 01 -> 0xFF 0x3 0x1 C0

4A jest pod 00000000 10 10 -> 0xA