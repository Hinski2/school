# zad6

---

* `tłumacznie adresów` - proces zamiany dresu wirtualnetgo na asres fizyczny, wykonywany przez jednostkę MMU (Memory Management Unit)
* `adres fizyczny` - rzeczywisty adres komurki w pamięci RAM, jest unikalny
* `adres wirtualny` - adres widziany przez program w swojej przestrzeni adresowej. adresy te nie sa unikalne w skali całego os, wiele procesów może mieć adres np 0x2000
* `pamięć TLB` - (Translation Lookaside Buffer) Mała, szybka pamięć podręczna w procesorze, ktora zapamietuje ostatnie tranlacje adresów, mozemy o niej myśleć jak o cache ale dla adresów

--- 

W x86-64 adresy wirtualne maja 48 bitów, a adresy fizyczne 52 bity.
każdy proces ma swój własny page table.
page tabli wygląda jak drzewo, niepełne. mamy lvl i rozrastają się one ale jeśli tablica (która jest tutaj node) jest pusta to wtedy nie jest tworzona 

![image](/procesor_package.png)
![image](/page_table_entry.png)
---

### Jak wygląda mechanizm tłumaczenia adresów bazujacy na wielepoziomowej tablicy stron procesorow z rodziny x86-64.

virtual addres dzieli sie na 5 pól
transalcja to przejście przez 4 poziomy tablic stron
wyniki translacji są cach'owane w TLB


| PML4 | PDPT | PD | PT | OFFSET |
| --- | --- | --- | --- | --- |
| 47..39 | 38..30 | 29..21 | 20..12 | 11..0|
| 9b | 9b | 9b | 9b | 12b |

PML4 - Page Map lvl (lvl 4 najwyższy)
PDPT - Page Directory Pointer Table (lvl 3)
PD - Page Directory (lvl 2)
PT - Page Table (lvl 1 najniższy )
Offeset - przesuniecie wewnętrz strony (strona ma 4KB)

przykład: 

    VA = 0x00007F123456789
    lvl4 = 7
    lvl3 = 481
    lvl2 = 166
    lvl1 = 354
    offset = 193

1. wybieramy lvl4[7] -> wskazuje na lvl3
    - musimy sprawdzić czy mamy odpowiednie uprawnienia dostępu(P, R/W, U/S, NX), jeśli nie to rzucamy page fault
2. wybieramy lvl3[481]:
    - jeśli bit PS  -> wskazuje na strone 1GB, translacja się kończy
    - jeśli !bit PS -> wskazuje na lvl2
3. wybieramy lvl2[166]:
    - jeśli bit PS  -> wskazuje na strone 2MB, translacja się kończy
    - jeśli !bit Ps -> wskazuje na lvl1
4. wybieramy lvl1[354] -> wskazuje na adres ramki 4KB w pamięci fizycznej
5. do adresu ramki dodajemy offset -> dostajemy finalny fizyczny adres

(wskazuje na strone = daje nam fizyczny adres początkowy ramki pamięci o określonym rozmiarze)
(jak robimy np lvl3[481] to dostajemy page table entry który ma w sobie adred tablicy na lvl2)

---

### Algorytm obliczania adresu fizycznego na podstawie adresu wirtualnego z uwzględnieniem uprawnień dostępu. 

w page table entry mamy flagi: 
* P (present) - czy wpis jest w pamięci
* R/W (ReadOnly / ReadWrite) - czy wszystkie dostępne strony są tylko ReadOnly czy też ReadWrite
* U/S (User/ Supervisor) - 0 = dostęp w trybie jądra, 1 w trybie urzytkownika
* NX (No execute) - kod nie moze być wykonywany
---

### rola TLB w procesie tlumacznenia adresów

TLB - Mała, szybka pamięć podręczna w procesorze, ktora zapamietuje ostatnie tranlacje adresów, mozemy o niej myśleć jak o cache ale dla adresów. dzięki niej:
* nie musimy za każdym razem przechodzić całej 4 poziomewej struktury tablic stron

gdy procesro potrzebuje przetlumaczyć adres wirtulany to najpierw sprawdza w TLB, czy mamy gotowe mapowanie VA -> PA
-  jeśli tak (hit) -> or razu uzywa fizycznego adresu
-  jeśli nie (miss) -> przechodzimy cały proces 4 poziomowego tlumaczenia i wynik wypisuje do TLB na przyszlość 