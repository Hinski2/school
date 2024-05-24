# zad7

---

* **bramkowanie kolumny t_CAS** Czas potrzebny od momentu wysłania sygnału który pozwala na dostęp do odpowiedniej kolumny w pamięci, do momentu, gdy dane z tej kolumny są gotowe do odczytu.
* **wybor wiersza t_RCD** Czas potrzebny od momentu aktywacji wiersza pamięci do momentu, gdy można wydać sygnał CAS, czyli przejść od wyboru wiersza do wyboru kolumny.
* **wstępne ładowania wiersza t_RP** Czas potrzebny do dezaktywacji obecnego wiersza i przygotowania matrycy pamięci do dostępu do kolejnego wiersza, zanim będzie możliwe wydanie nowego sygnału RAS.
* **bramkowania wiersza t_RAS** Minimalny czas, przez który wiersz musi być aktywny przed jego dezaktywacją, umożliwiający poprawne przeczytanie lub zapisanie danych.

**Rozmiar bloku pamięci**: 64 bajty
**Przesył danych na cykl**: 64 bity

Jak to liczyć:
1. najpierw sprawdzamy ile operacji robimy na nanosekunde
2. pesynistyczny czas to t_CAS + t_RCD + T_RP + T_RAS

dla trybu sekwencyjengo
1. pierwszy dostęp w tRCD + tCAS
2. kolejne w tCAS
3. Po zakończeniu operacji na wierszu, zamknij wiersz, co zajmuje tRP + tRas (bo to minimalny czas przez który wiersz ma być aktywny) 

[tRCD + n * t_CAS + t_RAS+ tRP]

---

```
DDR4-1600
tCLK = 800 MHz
tCAS = 10
tRCD = 10
tRP = 10
tRAS = 25

t_CLK (częstotliwość zegara):
    1 / 800MHz = 1.25ns

Czas dostępu (pesymistyczny):
    t_CAS + t_RCD + T_RP + T_RAS = 
    10 + 10 + 10 + 25 =
    55 t_CLK -> 68.75ns 

pesymistyczny przypadek:
    8 * 55 t_CLK -> 550ns

w trybie sekwencyjnym
    [tRCD + n * t_CAS + t_RAS+ tRP]
    10 + 8 * 10 + 25 + 10 = 125 t_CLK -> 156.25ns
   
```
---

```
DDR4-2133
tCLK = 1066.67 MHz
tCAS = 15
tRCD = 15
tRP = 15
tRAS = 36

t_CLK (częstotliwość zegara):
    1 / 1066.67MHz = 0.94ns

Czas dostępu (pesymistyczny):
    t_CAS + t_RCD + T_RP + T_RAS = 
    15 + 15 + 15 + 36 =
    81 t_CLK -> 76.14ns 

pesymistyczny przypadek:
    8 * 76.14 t_CLK -> 609.12ns

w trybie sekwencyjnym
    [tRCD + n * t_CAS + t_RAS+ tRP]
    15 + 8 * 15 + 36 + 15 = 186 t_CLK -> 174.84ns
```