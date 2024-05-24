# zad3

---

#### Do wyjaśnienia:
* **Magistrala** - To fizyczny sposób połączenia różnych komponentów komputera, umożliwiający im komunikację i wymianę danych. Magistrala przekazuje dane między procesorem, pamięcią operacyjną, urządzeniami peryferyjnymi i innymi elementami systemu.
* **Przepustowość** - Mówi o maksymalnej ilości danych, które mogą być przesyłane przez magistralę lub inne medium transmisyjne w jednostce czasu. W kontekście magistrali, jest to liczba transferów danych, która może być wykonana na sekundę, a w przypadku magistrali 32-bitowej z zadania wynosi 10 milionów transferów na sekundę.
* **Cykle magistrali** - Cykle zegara systemowego, podczas których magistrala jest wykorzystywana do przesyłania danych. Każdy cykl magistrali pozwala na wykonanie jednej operacji, takiej jak odczyt lub zapis danych z/do pamięci.
* **Podkradanie cykli** - Technika wykorzystywana przez kontrolery Direct Memory Access (DMA), która pozwala tym urządzeniom na korzystanie z cykli magistrali, które normalnie byłyby niewykorzystane przez procesor. Podczas "podkradania" cykli, DMA tymczasowo przejmuje kontrolę nad magistralą w celu przeprowadzenia transferu danych, minimalizując wpływ na wydajność procesora. 

### dane:
* magistrala 32 bitowa
* przepustowość 10 milionów transferów na sekundę.
* Wszystkie instrukcje są 32-bitowe, a ich wykonanie zajmuje dwa cykle magistrali (W pierwszym cyklu następuje pobranie instrukcji z pamięci i jej zdekodowanie, a w drugim jej wykonanie)
* Dla instrukcji wykonujących dostęp do pamięci w drugim cyklu nastąpi odwołanie do pamięci.
* Dla pozostałych instrukcji w drugim cyklu procesor nie odwołuje się do magistrali.
* Procesor wykonuje ciąg instrukcji, z których 40% robi dostęp do danych w pamięci.
* Moduł DMA może transferować dane z dysku z prędkością 5MB/s.

---

#### Ile instrukcji przetworzy w ciągu sekundy procesor, gdy transfer jest nieaktywny:
Gdy transfer danych z dysku jest nieaktywny, procesor może wykorzystywać wszystkie cykle magistrali do przetwarzania instrukcji. Każda instrukcja zajmuje dwa cykle magistrali.

**Przepustowość magistrali**: 10 milionów transferów na sekundę.
**Cykle magistrali na instrukcję**: 2.
**iops**: ilość operacji które procesor wykonuje przez sekunde

procesor przetworzy 60% * iops + 40% * 10'000'000 / 2

---

#### Ile instrukcji przetworzy w ciągu sekundy procesor, gdy transfer jest aktywny:
```
Jeśli DMA jest aktywne to w tym cyklu procesor nie może robić
dostępów do pamięci, czyli DMA kradnie cykle procesorowi
potencjalnie go spowalniając. 
To jest właśnie ! podkradanie cykli !
```
na potrzeba obliczeń zakładam że (jeden ze sposobów interpretacji zadania), dla 40% instrukcji które robią dostęp do pamięci połowa z nich jest przeplatana z instrukcjami DMA

dane:
* **Przepustowość magistrali**: 10 milionów transferów na sekundę.
* **Cykle magistrali na instrukcję**: 2.
* Moduł **DMA transferuje dane z dysku z prędkością** 5 MB/s.
* **iops**: ilość operacji które procesor wykonuje przez sekunde

procesor wykona 60% * iops + 20% * 10'000'000 / 2 + 20% * 5'000'000 

---

####  co złego mogłoby się stać, gdyby kontroler dysku dostawał wyłącznie cykle magistrali nieużywane przez procesor

```po ludzku co by się stało jeśli nie istniało by podkradanie cykli ```

Jeśli kontroler dysku dostaje wyłącznie cykle magistrali nieużywane przez procesor, oznacza to, że może on przeprowadzać operacje tylko wtedy, gdy procesor nie korzysta z magistrali. Innymi słowy, kontroler ma dostęp do magistrali tylko w momentach, gdy nie jest ona zajęta przez procesor, co może skutkować nieregularnym i opóźnionym dostępem do danych.

Co złego mogłoby się stać w takiej sytuacji:
1. Wolniejszy transfer danych - dostęp do magistrali ograniczony do momentów bezczynności procesora.
2. Dłuższe czasy oczekiwania - opóźnienia w operacjach wejścia/wyjścia.
3. Zmniejszona wydajność systemu - efektywność systemu obniżona przez ograniczony dostęp do magistrali.
4. Opóźnienia w aplikacjach - szczególnie wrażliwe w systemach wymagających szybkiego dostępu do danych.