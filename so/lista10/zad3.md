# zad 3

---

- `race condition` - 

---

``` c  
const int n = 50;
shared int tally = 0;

void total() {
    for (int count = 1; count <= n; count++)
        tally = tally + 1;
}

void main() {
    parbegin (total(), total());
}
```

--- 

### k = 2 
`tally = tally + 1`:
- Load
- Add 
- Store

##### Max = 100
najpierw zawsze wątek_1 wykonuje te trzy instrukcje, potem wątek_2 wykonują je. nie dochodzi do przeplotu

#### Min = 50

gdy mamy przeplot 
| wątek 1 | wątek 2 | 
| --- | --- | 
| load | | 
| add | load (ładuje tally) | 
| store (zapisuje tally + 1) | add | 
| | store (nadpisuje tally + 1)| 

mamy po takim przeplocie zwiększenie tylko o 1 

### k 
##### Max = k * 50 
##### Min = k
