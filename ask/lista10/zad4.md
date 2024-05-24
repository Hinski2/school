# zad 4

---

#### do wyjaśnienia:
**Pamięć podręczna** - To szybki rodzaj pamięci umiejscowiony blisko procesora, który przechowuje kopie danych z najczęściej używanych miejsc pamięci głównej. Dzięki temu procesor może szybciej uzyskać dostęp do tych danych, zamiast odwoływać się do wolniejszej pamięci RAM.

**Blok** - W kontekście pamięci, blok to podstawowa jednostka danych przechowywana lub przetwarzana w pamięci. W pamięciach podręcznych blok to najmniejsza ilość danych, która może być przesłana między pamięcią podręczną a pamięcią główną. **ma 64B**

**Hierarchia pamięci** - To układ zorganizowany różnych rodzajów pamięci w komputerze, ułożonych według szybkości i wielkości, od najmniejszej i najbardziej reaktywnej (jak rejestr lub pamięć podręczna CPU) do największej i najwolniejszej (jak dyski twarde czy inne formy pamięci masowej). Hierarchia ta pozwala na efektywne zarządzanie danymi i zwiększenie ogólnej wydajności systemu.

---

**A(k)** wyznacza czas, w cyklach procesora, w którym pamięć k-tego poziomu odpowiada na pytanie czy przechowuje dany blok pamięci.

**H(k)** wyznacza prawdopodobieństwo z jakim blok znajduje się na k-tym poziomie hierarchii pamięci, pod warunkiem, że nie znajduje się na wcześniejszych poziomach.

częstotliwość taktowania: 2.5 GHz -> jeden cykl to 0.4ns

A(L1) = 4
A(L2) = 12
A(L3) = 40
A(DRAM) = 200
 
H(L1) = 0.9 
H(L2) = 0.95
H(L3) = 0.98
H(DRAM) = 1.0

#### średni czas dostępu do pamięci
```
H(L1) * A(L1) +
(1 - H(L1)) * H(L2) * A(L2) +
(1 - H(L1)) * (1 - H(L2)) * H(L3) * A(L3) + 
(1 - H(L1)) * (1 - H(L2)) * (1 - H(L3)) * H(DRAM) * A(DRAM) =

0.9 * A(L1) +
0.095 * A(L2) +
0.0049 * A(L3) +
0.0001 * A(DRAM) = 

3.6 + 1.14 + 0.196 + 0.02 cykli -> 4.956 cykli -> 1.9824ns
```

#### pesymistyczny czas dostępu do pamięci
```
A(L1) + A(L2) + A(L3) + A(DRAM) = 
4 + 12 + 40 + 200 =
256cykli -> 102.4ns
```
