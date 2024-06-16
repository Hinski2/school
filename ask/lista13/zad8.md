# zad8

---

#### do wytłumaczenia:
* **virtualna przestrzeń adresowa** - Przestrzeń adresowa przydzielona procesowi, która pozwala programom korzystać z większej ilości pamięci, niż jest fizycznie dostępna, przez mapowanie logicznych adresów na fizyczne.
* **zbiór rezydentalny** -  Ilość pamięci fizycznej (RAM), którą proces aktualnie zajmuje, czyli część jego danych i kodu, która znajduje się w RAM
* **stronicowanie na żądanie (ang. demand paging)** - Technika zarządzania pamięcią, w której strony pamięci są ładowane do RAM tylko wtedy, gdy są potrzebne
* **współdzielenie pamięci** -  Mechanizm, który umożliwia kilku procesom dostęp do tej samej przestrzeni pamięci

#### liczenie rozmiaru pamięci wirtualnej używanej przez wszystkie procesy
**PID (Process ID)** – unikalny identyfikator procesu.
**RSS (Resident Set Size)** – ilość pamięci fizycznej (RAM) używanej przez proces (w kilobajtach).
**VSZ (Virtual Memory Size)** – rozmiar pamięci wirtualnej używanej przez proces (w kilobajtach).

``ps -e -o pid,rss,vsz > plik.txt`` potem włączas ``sumator.py``

#### bierzące użycie i całkowity rozmiar pamięci fizycznej
komenda ``free``
```
               total        used        free      shared  buff/cache   available
Mem:         8022440     1469128     3779004        3200     2774308     6273100
Swap:        2097152           0     2097152
```

Całkowity rozmiar pamięci (total): 8022440
Bieżące użycie pamięci (used): 1469128

Stronicowanie na żądanie ładuje do pamięci tylko te strony, które są aktualnie potrzebne przez program. 
Współdzielenie pamięci umożliwia różnym procesom dostęp do tych samych fragmentów pamięci, np. bibliotek.