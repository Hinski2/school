# rozdział 1

---

### ciała
`def` - podstawowa struktura algebraicza w której zdefiniowane są dwie operacje:
* dodawanie
* mnożenie

przykłady: 
* $\R$
* $\mathbb{Q}$

### przestrzenei liniowe 
`def` - zbiór wektorów, w kórym zdefiniowane są operacje dodawania wektorów i mnożenia wektorów przez skalary. Można o tym myśleć jak o ogólenieniu $\R^n$

własności: (dla przestrzenie liniowej `V` nad ciałem `F`)
* dodawanie wektórów: jeśli `u` i `v` są wektorami w przestrzeni liniowej `V`, to suma `u + v` także należy do `V`
* mnożenie przez skalar: jeśli `c` jest skalarem z ciałą `F`, a `v` wektorem z `V`, to `cv` również naleźy do `V`
* zawieranie wektora zerowego  

przykłady:
* $\R^n$
* $\Z_p^n$
* $\R^\R$

### podprzestrzeń liniowa
Dla przestrzeni liniowej `V` jej podzbiór` W ⊆ V` jest podprzestrzenią liniową, gdy jest przestrzenią liniową nad tym samym ciałem i działania są określone tak, jak w `V`. Zapisujemy to jako `W ≤ V`.

### kombinacja liniowa
Kombinacja liniowa wektorów to wyrażenie utworzone przez sumę wektorów, gdzie każdy z wektorów jest przemnożony przez pewien skalar

\[
\mathbf{w} = c_1 \mathbf{v}_1 + c_2 \mathbf{v}_2 + \cdots + c_n \mathbf{v}_n
\]

### otoczka liniowa
mając wektory ze zbioru U, Otoczka liniowa to zbiór wszystkich wektorów które możemy uzyskać przez kombinacje liniową wektorów z U. Jeśli chcemy przedstawić to graficznie np dla przestrzenie liniowej $\R^2$ to możemy otrzymać: punkt, linie albo wszystkie punkty w $\R^2$

Dla przestrzeni liniowej V nad ciałem F. Dla dowolnego zbioru wektorów (skończonego lub nie) U ⊆ V otoczka linowa, oznaczaja jako LIN(U), to zbiór wszystkich możliwych kombinacji liniowych wektorów ze zbioru U 

$$
\text{LIN}(U) = \left\{ \sum_{i=1}^{k} \alpha_i \mathbf{v}_i \mid k \in \mathbb{N}, \alpha_1, \dots, \alpha_k \in F, \mathbf{v}_1, \dots, \mathbf{v}_k \in U \right\}.
$$

Dla dowolnego zbioru wektorów \( U \subseteq V \) w przestrzeni liniowej \( V \), otoczka liniowa \( \text{LIN}(U) \) jest podprzestrzenią liniową \( V \). Jest to najmniejsza przestrzeń liniowa zawierająca \( U \).

Niech \( V \) będzie przestrzenią liniową, \( U, U' \subseteq V \) układami wektorów. Wtedy:

$$
\text{LIN}(U) = \text{LIN}(\text{LIN}(U)).
$$

Jeśli \( U \subseteq \text{LIN}(U') \) i \( U' \subseteq \text{LIN}(U) \), to

$$
\text{LIN}(U') = \text{LIN}(U).
$$


Niech \( V \) będzie przestrzenią liniową nad ciałem \( F \), zaś \( \mathbf{v}_1, \dots, \mathbf{v}_k \in V \) wektorami z \( V \). Jeśli skalary \( \alpha_1, \dots, \alpha_k \in F \) są niezerowe, to:

$$
\text{LIN}(\mathbf{v}_1, \dots, \mathbf{v}_k) = \text{LIN}(\alpha_1 \mathbf{v}_1, \dots, \alpha_k \mathbf{v}_k).
$$


### liniowa nezależność wektorów

układ wektorów jest liniowo niezależny jeśli nie istnieje taki wektor u z układu który można przedstawić za pomocą reszty wektorów

Układ wektorów U ⊆ V jest liniowo zależny wtedy i tylko wtedy, gdy istnieje u ∈ U taki że u ∈ LIN(U \ {~u}).

### metoda eliminacji GauBa 
wiemy ze: 
* jeśli każdy wektor ma współrzędną, na której tylko on jest niezerowy, to zbiór jest liniowo niezależny
* układ wektorów zawierający ~0 nie jest niezależny
* używając Lematu 1.23 możemy „upraszczać wektory”

Po zakończeniu eliminacji otrzymujemy układ złożony z wektorów liniowo niezależnych oraz samych wektorów zerowych. Wektory niezależne rozpinają oryginalną przestrzeń.

---

# rozdział 2

---

### Baza przestrzeni liniowej
`def` - B jest bazą przestrzeni liniowej V gdy LIN(B) = V oraz B jest liniowo niezależny. Alternatywnie, mówimy, że B jest minimalnym zbiorem rozpinającym V.

fakty:
* Eliminacja Gaußa zastosowana do układu wektorów U zwraca bazę LIN(U) (oraz wektory zerowe).
* każdy wektor ma jednoznaczne przestawienie w bazie

`przedstawienie wektora w bazie` - Niech \( V \) będzie przestrzenią wektorową nad ciałem \( F \) i niech \( \{ \mathbf{b}_1, \mathbf{b}_2, \dots, \mathbf{b}_n \} \) będzie bazą przestrzeni \( V \). Wektor \( \mathbf{v} \in V \) można przedstawić jako kombinację liniową wektorów bazowych:

$$
\mathbf{v} = c_1 \mathbf{b}_1 + c_2 \mathbf{b}_2 + \cdots + c_n \mathbf{b}_n,
$$

gdzie \( c_1, c_2, \dots, c_n \in F \) są skalarami.

### izomorfizm przestrzeni liniowych 
Mówimy, że dwie przestrzenie V, W nad ciałem F są izomorficzne, jeśli:
1. istnieją bijekcje ϕ : V → W oraz ψ : W → V
2. funkcje ϕ i ψ zachowują dodawanie wektorów:
    dla dowolnych wektorów a i b z V: ϕ(a + b) = ϕ(a) + ϕ(b)
    dla dowolnych wektorów a i b z W: ψ(a + b) = ψ(a) + ψ(b)
3. funkcje ϕ i ψ zachowują mnożenie wektorów:
    dla dowolnego wektora v z V i skalara c z ciała F: ϕ(c * v) = c * ϕ(v)
    dla dowolnego wektora w z W i skalara c z ciała F: ψ(c * v) = c * ψ(v)

Niech V nad $\mathbb{F}$ ma bazę n-elementową. Wtedy V jest izomorficzna z $\mathbb{F}^n$.
Dowolne dwie przestrzenie liniowe nad F mające bazy n-elementowe są izomorficzne.

#### Lemat Steinitza o wymianie
Niech \( V \) będzie przestrzenią liniową, \( A \subseteq V \) liniowo niezależnym układem wektorów, zaś \( B \) układem rozpinającym \( V \). Wtedy albo \( A \) jest bazą, albo istnieje \( \mathbf{v} \in B \) taki, że \( A \cup \{\mathbf{v}\} \) jest liniowo niezależny.

wnioski: Każdy zbiór niezależny skończenie wymiarowej przestrzeni liniowej V można rozszerzyć do bazy.

### Wymiar przestrzeni liniowej
Dla przestrzeni skończenie wymiarowej V jej wymiar to moc jej bazy. Oznaczamy go jako dim(V).

Dla przestrzenie skończonych $ V_1, V_2 \leq V$ zachodzi: 
\[ \dim(V_1 + V_2) = \dim(V_1) + \dim(V_2) - \dim(V_1 \cap V_2) \]

Jeśli $B_1, B_2$ są bazami dla $V_1, V_2 \leq V$ to:
$$
    V_1 + V_2 = LIN(B_1 \cup B_2)
$$

### Warstwy 
Warstwa to po prostu przesunięta podprzestrzeń liniowa. Jest to zbiór punktów powstały przez dodanie ustalonego wektora do każdego punktu podprzestrzeni liniowej. Warstwy są podobne do podprzestrzeni, ale nie spełniają wszystkich jej własności (na przykład nie przechodzą przez początek układu współrzędnych).

Dla podprzestrzeni $W \leq V$ zachodzi:
$$
W + W = W \\
W + W = \{ w_1 + w_2: w_1, w_2 \in W \}
$$

---

# Rozdział 3

---

### przekształcenie liniowe
Niech \( V \) i \( W \) będą przestrzeniami liniowymi nad ciałem \( F \). Funkcja \( F : V \rightarrow W \) jest przekształceniem liniowym, jeśli dla wszystkich \( \mathbf{v}, \mathbf{w} \in V \) oraz \( \alpha \in F \) spełnia:

- \( F(\alpha \mathbf{v}) = \alpha F(\mathbf{v}) \)
- \( F(\mathbf{v} + \mathbf{w}) = F(\mathbf{v}) + F(\mathbf{w}) \)

Przekształcenie liniowe nazywa się również **homomorfizmem** między przestrzeniami \( V \) i \( W \).

Złożenie przekształceń liniowych jest przekształceniem liniowym.

### Jądro i obraz przekształcenia liniowego
dla przestrzeni liniowych \( V, W \) i przekształcenia liniowego \( F : V \rightarrow W \):

`Jądro przekształcenia liniowego` składa się z wszystkich wektorów, które po przekształceniu przez 𝐹 dają wektor zerowy. Jest to zbiór tych wektorów, które "zanikają" po przekształceniu.
$$
ker(F) = \{ \vec{v} : F( \vec{v}) = \vec{0} \}
$$

`Obraz przekształcenia liiowego` to zbiór wszystkich możliwych wyników, jakie można uzyskać stosując przekształcenie 𝐹 do wektorów w 𝑉 . Oznacza to, że obraz zawiera wszystkie wektory w 𝑊 , które są "osiągalne" przez 𝐹.

$$
Im(F) = \{ \vec{u} : \exist \vec{v} \, \, F(\vec{v}) = \vec{u} \}
$$

Jądro i obraz są przestrzeniami liniowymi

Niech $F : V \rightarrow W$ będzie przekształceniem liniowym, gdzie $V, W$ to skończenie wymiarowe przestrzenie liniowe:
$$
dim(V) = dim(Im(F)) + dim(ker(F))
$$

### rząd przekształcenia liniowego 
Rząd przekształcenia liniowego $F$ to $rk(F) = dim(Im(F))$

Rząd przekształcenia liniowego jest liczbą wymiarów przestrzeni, do której przekształcane są wektory z przestrzeni 𝑉 przez przekształcenie 𝐹 . Innymi słowy, mówi o liczbie niezależnych wektorów, które można uzyskać po przekształceniu.

Jeśli $F: V \rightarrow W$ jest przekształceniem liiowym i $F(\vec{v_1}), \dots, F(\vec{v_n}) \in W$ są liniowo niezaleźne, to rónież $\vec{v_1}, \dots, \vec{v_n}$ są liniowo niezaleźne 

---

# Rozdział 4

---

### macierze 
macierz identycznościowa:
$$
\begin{bmatrix}
1 & 0 & \dots & 0 \\
0 & 1 & \dots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \dots & 1
\end{bmatrix}
$$

macierz górnotrójkątna:
$$
\begin{bmatrix}
a_{11} & a_{12} & \dots & a_{1m} \\
0 & a_{2 1}& \dots & a_{2m} \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \dots & a_{nm}
\end{bmatrix}
$$

##### zestawienie macierzy: 
dwie macierze M, M' rozmiaru m x n oraz m x n' (nad tym samym ciałem) można zapiać:

\[ 
\left[ M \mid M' \right] 
\]

dwie macierze M, M' rozmiaru m x n oraz m' x n można zapisac:

\[
\left[\frac{M}{M'}\right]
\]

Mnożenie macierzy jest łączne, bo jest to funkcja, a składanie funkcji (w ogólności: relacji) jest łączne.

##### własności macierzy:
$$
Id \, A = A \\
A(B + C) = AB + AC \\
(B + C) A = BA + CA \\
\alpha(AB) = (\alpha A ) B  = A(\alpha B) \\
A [B | C] = [AB|AC] \\
\left[\frac{B}{C}\right] A = \left[\frac{BA}{CA} \right]
$$

##### transpozycja macierzy:
$$
\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6
\end{bmatrix}^T = 
\begin{bmatrix}
1 & 4 \\
2 & 5 \\
3 & 6
\end{bmatrix}
$$

$$
(M + N) ^ T = M^ T + N ^ T \\
(MN)^ T = N^T M^T \\
(M^T)^T = M
$$

### operacje elementarne
operacje elementarne (kolumnowe) to:
* zmiana kolumn
* dodanie do jednej z kolumn wielokrotności innej
* przemnożenie kolumny przez niezerowy skalar

(analogicznie definiujemy operacje elementarne wierszowe)

Operacje elementarne można przedstawić w postaci macierzy
Macierze odpowiadajace operacją elementarnym nazywamy **macierzami elementarnymi**

Dla macierzy M rozmiaru n x m możemy zadać przekształcenie liniowe $F_M : F^m \rightarrow F^n$:
$$
F_M(\vec{V}) = M \vec{V}
$$

Takie przekształcenie będziemy nazywać przekształceniem indukowanym przez macierz M.

##### rząd macierzy
rząd macierzy to maksymalna liczba liniowo niezależnych wierszy lub kolumn w tej macierzy.
Dla macierzy M i indukowanym przez nią przekształceniem liniowym $F_M$ zachodzi:
$$
rk(M) = rk(F_M)
$$

Rząd kolumnowy i wierszowy ustalonej macierzy M są sobie równe, w szczególności $rk(M) = rk(M^T)$

Operacje elementarne kolumnowe (wierszowe) na macierzach nie zmieniają rzędu wierszowego i kolumnowego macierzy

##### macierz odwrotna 
macierz odwrotna zapisujemy jako $M^{-1}$
$$
M \cdot M^{-1} = M^{-1} \cdot M = Id
$$

macierz jest odwracalna $\iff$ przekształcenie $F_M$ jest odwracalne 

macierz M wymiaru $n \times n$ jest odwracalna $\iff rk(M) = n$  

jeśli $M, N$ są odwracalne wtedy:
$$
(M^T) ^{-1} = (M^{-1})^T \\
(M^{-1})^{-1} = M
(MN)^{-1} = N^{-1}M^{-1}
$$

---

# Rozdział 5

---

\[
\begin{array}{ccc}
V & \xrightarrow{F} & W \\
\updownarrow (\cdot)_{\mathcal{B}_V} & & \updownarrow (\cdot)_{\mathcal{B}_W} \\
\mathbb{F}^n & \xrightarrow{M} & \mathbb{F}^m
\end{array}
\]

Diagram przemienny wizualizuje relacje między przekształceniami liniowymi a ich reprezentacjami macierzowymi względem wybranych baz.

1. **V i W** to przestrzenie liniowe, nad którymi działa przekształcenie liniowe \( F \).
2. **\( B_V \) i \( B_W \)** to bazy tych przestrzeni, odpowiednio \( V \) i \( W \).
3. **\( F \)** jest przekształceniem liniowym, które działa z przestrzeni \( V \) na \( W \).
4. Macierz \( M \) to macierz przekształcenia liniowego \( F \) względem baz \( B_V \) i \( B_W \).

Diagram przemienny oznacza, że niezależnie od tego, jaką drogę wybierzesz (czy najpierw zastosujesz przekształcenie \( F \), a potem wyrazisz wynik w bazie \( B_W \), czy najpierw wyrazisz wektor \( V \) w bazie \( B_V \), a następnie pomnożysz go przez macierz \( M \)), wynik będzie ten sam.

Diagram mówi nam że są dwa sposoby na przejście z lewego górnego rodu go prawego dolengo rogu:
$$
M_{B_V B_W}(F)(\vec{v})_{B_V} = (F \vec{v}) _ {B_W}
$$

### Macierz przekształcenia w bazie
**Macierz przekształcenia w bazie** to macierz, która reprezentuje przekształcenie liniowe \( F: V \rightarrow W \) w kontekście wybranych baz \( B_V \) w przestrzeni \( V \) oraz \( B_W \) w przestrzeni \( W \). 

Jeśli \( B_V = \{ \mathbf{v}_1, \mathbf{v}_2, \dots, \mathbf{v}_n \} \) jest bazą przestrzeni \( V \), a \( B_W = \{ \mathbf{w}_1, \mathbf{w}_2, \dots, \mathbf{w}_m \} \) jest bazą przestrzeni \( W \), to macierz przekształcenia \( M_{B_V B_W}(F) \) jest zbudowana z wektorów współrzędnych \( F(\mathbf{v}_i) \) wyrażonych w bazie \( B_W \). 

Każda kolumna tej macierzy odpowiada współrzędnym wektora \( F(\mathbf{v}_i) \) w bazie \( B_W \), a macierz ma wymiary \( m \times n \), gdzie \( m \) to liczba wektorów w bazie \( B_W \), a \( n \) to liczba wektorów w bazie \( B_V \).

po ludzku: jest to macierz która przyjmuje wektor v w bazie $B_V$ i zamienia go na wektor w w bazie $B_W$

### Macierz zmiany bazy
mówi nam jak przejść w macierzy w bazie B na macierz w bazie B'
$$
M_{BB'}(\vec{v})_{B} = (\vec{v})_{B'}
$$

Niech $B_V, B'_V$ będą bazami V, Wtedy:
$$
M_{BB'}\cdot M_{B'B} = Id
$$

tzn są to macierze odwrotne

--- 

# Rozdział 6

---

### wyznacznik 
wyznacznik to uogólnienie objętości (ale z znakiem) 
wyznacznik zapisujemy przez: det(M)

tutorial: https://youtu.be/wszYqnIIUr0?si=6gjb0FsZadnShJ3M

własności:
$$
det(\vec{V_1}, \vec{V_2}, \dots, \vec{V_{i - 1}}, \vec{0}, \vec{V_{i + 1}}, \dots, \vec{V_n}) = 0 \\
Jeśli  \ \ \vec{V_i} = \vec{V_j} \ \ to \ \ det(\vec{V_1}, \vec{V_2}, \dots, \vec{V_n}) = 0 \\
zminana \ kolejności \ dwóch \ wektorów \ zmienia \ znak \ (objętosć \ ze \ znakiem )
$$

dla macierzy trójkątnej determinant to iloczyn elementów na przekątnej

jeśli układ wektorów jest liniowo zależny to det jest równy zero:
$$
det(A) \neq 0 \iff rk(A) = n 
$$

### minor 
Minorem macierzy M nazywamy każdą macierz uzyskaną poprzez usunięcie M pewnego zbioru wierszy i kolum. Zwyczjowo $A_{i, j}$ to macierz powstałą z A poprzez usunięcie i-tego wiersza oraz j-tej kolumny

### dopełnienie algebraiczne
Dopełnienie algebraiczne elementu $a_{i, j}$ to $(-1)^{i + j} det(A_{i, j})$

### rozwinięcie laplace'a
dla macierzy kwadratowej $A = (a_{i j})_{i, j = 1, \dots, n}$ mamy:
$$
det(A) = \sum_{i = 1}^n (-1)^{i + j} \cdot a_{i,j} \cdot det(A_{i, j})
$$

po ludzku to ta normalna metoda która żawsze używasz z wykreślaniem (tutorial od 1min)

##### twierdzenie cauchy'ego
$$
det(AB) = det(A) \cdot det(B)
$$

##### ważne własności
$$
det(A) = det(A^T) \\
det(A) = det(A^{-1}) \\
det(A^n) = (det(A))^n \\
det(\alpha \cdot A) = \alpha ^ n \cdot det(A)
$$

jak działa ta ostatnia własnośc:
    $c * dim(A) = dim(B)$ gdzie B to taka sama macierz jak A, ale jej jeden wierz jest przenmnożony przez c

### wyznacznik a macierz odwrotna
Jeśli M jest odwracalna, to
$$
det(M^{-1}) = \frac{1}{det(M)}
$$

niech $F : V \rightarrow V$ będzie przekształceniem liniowym, zaś M, M' będą macierzami dla tego przekstałcenia wyrażonymi w różnych bazach. Wtedy: (wyznacznik macierzy nie zależy od bazy)
$$
dim(M) = dim(M')
$$

---

# Rozdział 7

---

wzory cramera: jeśli A to macierz kwadratowa i odwracalna, to jedyne rozwiązanie jest postaci: (gdzie $A_{x_i}$ to macierz wpostała przez zastąpienie i-tej kolumny A przez $\vec{B}$, czyli wektory wynikowy)
$$
x_i = \frac{det(A_{x_i})}{det(A)}
$$


#### układ jednorodne
układ postaci $\vec{B} = \vec{0}$ nazywany układem jednorodnym, taki układ ma na pewno jedno rozwiązanie

$$
A \vec{X} = \vec{0}
$$

#### układ niejednorody
Układ równań liniowych nazywamy niejednorodnym, jeśli przynajmniej jedno z równań w tym układzie ma po prawej stronie równości wartość różną od zera. 

$$
A \vec{X} = \vec{B} \ ma \ rozwiązanie \iff \vec{B} \in Im(A)
$$
jeśli równanie $A \vec{X} = \vec{B}$ ma rozwiązanie to zbiór wszystkich jego rozwiązań jest warstwą względem ker A 

po ludzku:
* jeśli B znajduje sięw obrazie A, to istanieje taki wektor X, że AX = B . innymi słowy, istnieje rozwiązanie tego równania
* Warstwa względem ker(A) oznacza, że każde rowziązanie X równania AX = B można przedstawić jako sumę pewnego konkretnego rozwiązania $X_0$ oraz dowolengo wektora z jądara ker(A). Formalnie: X = $X_0$ + K, gdzie K $\in$ ker(A). W praktyce jeśli mamy $X_0$ jedne konkretne rowsiązanie równania AX = B, to każde inne rozwiązanie X można uzyskać przez dodanie do $X_0$ dowolnego wektora K z ker(A)

##### Tw Kronecker-Capelli
układ  $A \vec{X} = \vec{B} \ ma \ rozwiązanie \iff rk(A | \vec{B}) = rk(A)$

---