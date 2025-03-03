# notatka 1

---

## problemy, algorytmy programy

### fibonacii modlulo 

1. rekurencyjnie
``` c++
int fibrek(int n){
    if(n <= 1) return 1;
    return (fibrek(n - 1) + fibrek(n - 2)) % mod;
}
```

2. iteracyjnie
``` c++ 
int fibiter(int n){
    int a = 1, b = 1, c = 1;
    for(int i = 3; i <= n; i++){
        a = b;
        b = c;
        c = a + b;
    }

    return c;
}
```

3. macierze
korzystamy z tego że: 
$$
\begin{bmatrix} 0 & 1 \\ 1 & 1 \end{bmatrix} 
\cdot 
\begin{bmatrix} f_i \\ f_{i+1} \end{bmatrix} 
=
\begin{bmatrix} f_{i+1} \\ f_{i+2} \end{bmatrix}
$$
Stąd
$$
\begin{bmatrix} 0 & 1 \\ 1 & 1 \end{bmatrix}^{n-1} 
\cdot 
\begin{bmatrix} f_0 \\ f_1 \end{bmatrix} 
=
\begin{bmatrix} f_{n-1} \\ f_n \end{bmatrix}
$$

## efektywność programów
interesuje nas:
* **złożoność czasowa** - liczba jednostek czasu potrzebnych na wykowanie programu
* **złożoność pamięciowa** - liczba jednostek pamięci potrzebnych do wykonania algorytmu

będziemy przyjmowali że nasz model komputera to maszyna RAM, cechuje sie ona:
* **kryterum jenorodne** - koszt każdej operacji maszyny RAM jest jendostkowy 
* **kryterium logarytmicznie** - koszt opecaji maszyny RAM jest jówny sumie długości operandów (będziemy to stosowali do szacowania złożoności obliczeń na wielkich liczbach)
**uwaga**: stosując kryterium logarytmiczne należy uwzględnić koszt obliczania adresu w trakcie wykonywania rozkazów stosujących adresowanie pośrednie 


#### przykład sortowanie:

**Insertion Sort**: Dla każdego elementu przesuwa go do właściwego miejsca w posortowanej części tablicy.
``` c++
void insertSort(vector<int> &T){
    int n = T.size();
    for(int i = 1; i < n; i++){
        int j = i - 1, x = T[i];
        while(j >= 0 and T[j] > x){
            T[j + 1] = T[j];
            j--;
        }

        T[j + 1] = x;
    }
}
```

**Selection Sort**: W każdej iteracji znajduje najmniejszy element i zamienia go na początek nieposortowanej części.

```c++
void selectSort(vector<int> &T){
    int n = T.size();
    for(int i = 0; i < n - 1; i++){
        int minIndex = i;
        for(int j = i + 1; j < n; j++){
            if(T[j] < T[minIndex])
                minIndex = j;
        }

        swap(T[i], T[minIndex]);
    }
}
```

#### złożoności:
* **złożoność pesymistyczna**: maksymalny koszt obliczeń dla danych rozmiaru n
* **zlożoność oczekiwana**: średni koszt obliczeń dla danych rozmiaru n

**złożoność problemu**: złożoność najlpszego algorytmu rozwiazującego dany problem 

## notacje:
Oznaczenia:
* $\R^*$ - zbiór nieujemnych liczb rzeczywistych
* $\R^+$ - zbiór dodatnich liczb rzeczywistych
analogicznie dla $\N$

Niech f: $\N \implies \R^*$ będzie dowolna funkcja:
* $O(f(n)) = \{ t: \N \implies \R^* | \exists_{c \in R^+}  \exists_{n_0 \in \N} \forall_{n \geq n_0}  t(n) \leq cf(n)\}$

* $\Omega(f(n)) = \{ t: \N \implies \R^* | \exists_{c \in R^+}  \exists_{n_0 \in \N} \forall_{n \geq n_0}  t(n) \geq cf(n)\}$

* $\Theta(f(n)) = O(f(n)) \cap \Omega(f(n))$

intyicja:
* $O(f(n))$ (duże O) - górne ogranicznie, oznacza że funkcja $t(n)$ rośnie co najwyżej tak szybko jak $f(n)$ 
* $\Omega(f(n))$ - dolne ogranicznie, oznacza że funkcja $t(n)$ rośnie co najmniej tak szybko jak $f(n)$
* $\Theta(f(n))$ - ścisłe ogranicznie, oznacza, że $t(n)$ rośnie dokładnie w tym samym tempie co $f(n)$
