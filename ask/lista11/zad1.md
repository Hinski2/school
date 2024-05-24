# zad 1

---

#### Adresowanie bajtowe
Adresowanie bajtowe oznacza, że każdy adres pamięci wskazuje na pojedynczy bajt danych. W kontekście pamięci cache oznacza to, że musimy zarządzać adresami na poziomie bajtów, a nie większych jednostek danych.

#### Mapowanie bezpośrednie
liczba lini w secie wynosie 1
w tej metodzie każdy blok pamięci głównej jest mapowany do jednej, określonej linii w pamięci cache. Jest to najszybsza i najprostsza technika, ale ma wysoką liczbę missów z powodu konfliktów (conflict misses).
(w lini trzymamy offset pod którym znajduje się bajt o który nam chodzi)  

---

**Addres of word:**
[22 bits tag][5 bits idx][5 bits block offset]

**index** - używane do określenia, do którego zestawu (set) w cache blok danych zostanie przypisany.
**tag** - identyfikuje unikalnie blok danych w pamięci głównej
**offset** - mówi że dane zaczynają się pod tym offsetem

#### Jaki jest rozmiar bloku w 32-bitowych słowach?
* jedno słowo 32 bity -> 4 bajty
* offset wskazuje na bajt w bloku, więc blok ma 2^5 = 32 bajty.
* blok ma 32 / 4 = 8 słowa

#### Ile wierszy ma nasza pamięć podręczna
* liczba wierszy (set) jest określona przez index czyli 2 ^ 5 = 32 wiersze (sety)

#### Jaki jest stosunek liczby bitów składujących metadane do liczby wszystkich bitów?

* linia składa się z 
    * **tag** 22 bity
    * **valid bit** 1 bit
    * **blok pamięci** u nas 32 bajty -> 256 bity

    metadane -> 23 bity, dane 256 bity 

* dla całej pamięki która ma 32 wiersze:
    * metadane: 736 bitów
    * dane: 8192 bitów

metadane / dane = 0.08984375


