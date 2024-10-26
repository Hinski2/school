# wyklad 3
### Arytmetyka zmiennoprzecinkowa i podstawowe pojęcia teorii blędów 

---

#### przykład 1:
##### Perfidny wielomian wilkinsona
$$
    w(x) := (x - 1)(x - 2)(x - 3)...(x - 20) = 1x^{20} - 210x^{19} ... \\
    w_\epsilon := w(x) - \epsilon * x^{19}
$$
```
dane: 
    współczynnik wielomianu w postaci potegowaj
wynik:
    miejsca zerowe
```
wkrey $w(x)$ i $w_\epsilon(x)$ przykład ten podkzuje że mnimalna zmiana danych może mocno zmienicwykres, w tym przypadku dostajemy dodatkowe miejsca zerowe urojone 

**wknoski**: mała wsględna zmiana danych powoduje **DUŻĄ** względna zmienę wyniku

---

#### przykład 2:
##### Macierz hilberta
```
dane: 
    macierz hilberta i numeryczna macierz hilberta
wynik:
    wynik wyznacznika
```

$$
H_n := [ \frac{1}{1 + j - 1}]_{n \times n} \\
\tilde{H_n} := [ fl( \frac{1}{1 + j - 1})]_{n \times n} \\
$$

$\tilde{H_n}$ to numeyczny odpowiednik macierzy Hilberta
wyznaczniki $H_n$ i $\tilde{H_n}$ są zupełnie inne 
**wknoski**: mała wsględna zmiana danych powoduje **DUŻĄ** względna zmienę wyniku

---

#### Przykłąd 3

rozażmy następujący układ równań liniowych
```
dane:
    macierz hilberta, wektor niewiadomych i wektor jedynke
wynik: 
    rozwiązanie równania liniowego
```
$$
 H_n \cdot [x_1, x_2, x_3, \dots x_n] = b_n \\
 gdzie \ b_n := H_n \cdot [1, 1, 1, \dots, 1]
$$

więc wynikiem jest wektor zawierający same jedynki -> $[1, 1, 1, \dots, 1]$
rozważmy następny ukłąd równań 
$$
\tilde{H_n} \cdot [x_1, x_2, x_3, \dots x_n] = fl(b_n) \\
$$

ale tutaj wynik, czyli $b_n$ jest z dupy, zupełnie inny od $[1, 1, 1, \dots, 1]$
**wknoski**: mała wsględna zmiana danych powoduje **DUŻĄ** względna zmienę wyniku

---

#### def:
**Zadanie źle uwarunkowane**: zadanie nazywamy źle uwarunkowanym jeśi mała względna zmiana danych powoduje dużą względną zmianę wyników. Wielkości mówiące o tym w jaki sposób względna zmiana danych wpływa na względną wartość wyniku nazywamy wspaźnikami uwarunkowania 

**uwaga:**
* rozwiazując zadanie źle uwarunkowane przy pomocy komputera i arytmetyki zmiennopozycyjnej (fl) nalerzy zachować szczególną ostrożność 

* uwarunkowanie to cecha zadanie i nic tego nie zmieni

* w jaki sposób badać uwarunkowanie zadania? Jest to turdne :)

---

### badanie uwarunkowania zaania

#### przykłąd 1
zbadajmy uwarunkowanie zdaia obliczania wartości ustalonej funcji w danym punkcjie 

$f$ - ustalona funkcja
$f(x)$ - wynik dokładny
$|h|$ - moduł z tej liczby jest maly
$\left| \frac{f(x) - f(x + h)}{h} \right|$ $\approx$ pochodna $f'(x)$

**def: względna zmiana wyniku**

$$
\left |\frac{f(x) -(x + h)}{f(x)} \right| \approx \left |\frac{f(x) - f(x + h)}{h} \right| \cdot \left |\frac{h}{f(x)} \right| = \left |\frac{x f'(x)}{f(x)} \right | \cdot \left|\frac{h}{x} \right|
$$

**względna zmiana danych** (dla tego zadania) - 
$$
\left| \frac{x - (x + h)}{x} \right| = \left| \frac{h}{x} \right|
$$

wielkość $\left| \frac{xf'(x)}{f(x)} \right|$ to **wskaźnik uwarunkowania** (w tym zadaniu)  zadania obliczania wartości funkji f w danym punkcie



#### Przykląd 2
obliczymy uwarunkowanie zadaniawyznaczania iloczynu skalarnego dwóch wektorów 

Przypomnienie:
$$
x := [x_1, x_2, ... x_n]^ T \\
y := [y_1, y_2, ... y_n]^ T \\
S(x, y) := \sum_{i = 1}^n x_i \dot y_i \\
\tilde{x} = [x_1(1 + \epsilon_1), x_2(1 + \epsilon_2), ..., x_n(1 + \epsilon_n)] \\
\tilde{y} = [y_1(1 + \gamma_1), y_2(1 + \gamma_2), ..., y_n(1 + \gamma_n)] \\
S(\tilde{x}, \tilde{y}) = \sum_{i = 1}^n x_i(1 + \epsilon_i) \dot y_i(1 + \gamma_i) \\
$$

błąd względny:
$$
\left| \frac{S(x, y) - S(\tilde{x}, \tilde{y})}{S(x, y)} \right| = \left| \frac{\sum_{i = 1}^n x_i y_i (1 + \epsilon_i + \gamma_i + \epsilon_i \gamma_i)}{\sum_{i = 1}^n x_i y_i} \right| = \left| \frac{\sum_{i = 1}^n x_i y_i (\epsilon_i + \gamma_i)}{\sum_{i = 1}^n x_i y_i} \right| \leq (max_{1 \leq i \leq n} |\epsilon_i| + |\gamma_i|) \cdot \frac{\sum_{i = 1}^n |x_i y_i|}{|\sum_{i = 1}^n x_i y_i|}
$$

wobec tego wielkość $\frac{\sum_{i = 1}^n |x_i y_i|}{|\sum_{i = 1}^n x_i y_i|}$ można uznać za wskaźnik uwarunkowania zadania obliczania uloczynu slarnego wektów a i b

wniosi:
1. Jeśli $x_i$ i $y_i$ sa tego samego znaku dla $i = 1, 2, ..., n$ to zadanie jest dobre uwaruknowane
2. Jeśli mianownik jest bardzo mały np. $10^{-100}$ to zadanie jest źle uwarunkowane
...


### Algorytmy numeryczne poprawne
**def: algorytmu numerycznego poprawnego** - algorytm nazywamy numerycznie poprawnym jeśli wynik jego działania w arytmetyce zmiennopozycyjnej (fl) *może zostać* zinterpretowany jako mało zabużony wynik dokładny dla mało zaburzonych danych 

#### Przykład
Chcey obliczyć wartość funkcji dwóch zmiennych $A(a, b)$. Niech $Alg_A(a, b)$ oznacza algorytm obliczania wartości $A(a, b)$. $f(Alg_A(a, b)) = A(a(1 + \alpha),\ b(1 + \beta))(1 + \gamma)$ oznacza że dosstaje prawie dokladny wynik dla mało zaburzonych danych, $|\alpha|, |\gamma|, |\beta| \leq K * 2 ^{-t}$ 

**Pro tip:** na egzaminie zgaduj że wynik jest numerycznie poprawny

**Wnioski:**
1. algorytm nuperycznie poprawny + zadanie dobrze uwaruknowane $\implies$ sukces :)
2. algorytm numerycznie poprawny + zadanie źle uwarunkowane $\implies$ prawie na pewno poraźka :(


----

Przykład
Niechdany będzie algorytm na sume n liczba:
```c++
s = x[1]
for(i = 2; i <= n; i++)
    s = s + x[i]
    return s
```
$$
fl(s) = ((((x_1 + x_2)(1 + \epsilon_2) + x_3)(1 + \epsilon_3) + x_4)(1 + \epsilon_4) + ... + \epsilon_n)(1 + \epsilon_n) =  \sum_{i = 1}^n x_i \Pi_{j = i}^n(1 + \epsilon_j) = \sum_{i = 1}^n x_i (1 + E_i) = \sum_{i = 1}^n \tilde{x}
$$

oznaczmy przez $1 + E_i = \Pi_{j = i}^n(1 + \epsilon_j)$
oznaczmy przez $\tilde{x} = xi(1 + E_i)$

z twierdznie a oumulaji błędów 
$|E_i| \leq (n - i + 1) * 2^{-t}$ dla i = 1
$|E_i| \leq (n - i) * 2^{-t}$ dla $i \in {2, 3.. n}$

pro tip: w zadaniu domowym uważaj na zabużanie zmiennych w inny sposób w różnych cześciach zadania (ma być tak samo)
    