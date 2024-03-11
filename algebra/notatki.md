# Algebra Notatki

---

## Spis tresci
1.  Ciała, przestrzenie liniowe, liniowa niezależność, eliminacja Gauba
    1.1 Ciała
    1.2 Przestrzenia liniowe
    1.3 Podprzestrzenie liniowe
    1.4 Kombinacje liniowe wektorów
    1.5 Liniowa niezależność wektorów
    1.6 Metody eliminacji Gauba

2. Baza przestrzeni liniowej, wymiar
    2.1 Baza przestrzeni liniowej
    2.2 Wyrażanie wektora w bazie
    2.3 Wymiar przestrzeni liniowej
    2.4 Zastosowanie eliminacji Gauba do liczenie wymiaru
    2.5 Warstwy

---

## 1 Ciała przestrzenie liniowe, liniowa niezależność, eliminacja Gauba

### 1.1 Ciała
Ciała są strukturami matematycznymi, które uogólniają koncepcję liczb, wprowadzając operacje dodawania i mnożenia z określonymi własnościami:
* Każdy element (poza 0 dla mnożenia) ma element odwrotny względem dodawania i mnożenia.
* Operacje dodawania i mnożenia są przemienne.
* Istnieją elementy neutralne dla dodawania (0) i mnożenia (1).
* W $\mathbb{Z}_p$, operacje dodawania i mnożenia definiowane są modulo p.

kluczowe jest zrozumienie, że ciała stanowią fundament dla teorii przestrzeni liniowych, rozszerzając koncepcję liczb rzeczywistych na bardziej ogólne systemy liczbowe. Szczególnie istotne jest to, że ciała zapewniają strukturę, w której operacje dodawania i mnożenia są dobrze zdefiniowane i zachowują intuicyjne właściwości znane z liczb rzeczywistych. Daje to solidną podstawę do badania wektorów, macierzy i przekształceń liniowych w matematyce wyższej i jej zastosowaniach.

### 1.2 Przestrzenie liniowe
Przestrzeń liniowa jest uogólnieniem $\mathbb{R}^n$, gdzie jej elementy nazywane są wektorami. Definicja przestrzeni liniowej nad ciałem $F$ obejmuje:

- Dodawanie wektorów: $+ : V \times V \rightarrow V$
- Przemienność dodawania: $\forall \vec{u}, \vec{v} \in V, \vec{v} + \vec{u} = \vec{u} + \vec{v}$
- Łączność dodawania: $\forall \vec{u}, \vec{v}, \vec{w} \in V, (\vec{u} + \vec{v}) + \vec{w} = \vec{u} + (\vec{v} + \vec{w})$
- Istnienie wektora zerowego $\vec{0}$: $\exists \vec{0} \in V, \forall \vec{v} \in V, \vec{0} + \vec{v} = \vec{v}$
- Istnienie elementu przeciwnego dla każdego wektora $\vec{v}$: $\forall \vec{v} \in V, \exists -\vec{v} \in V, (-\vec{v}) + \vec{v} = \vec{0}$
- Mnożenie wektorów przez skalary: $· : F \times V \rightarrow V$
- Rozdzielność mnożenia względem dodawania skalarów: $\forall \alpha, \beta \in F, \forall \vec{v} \in V, (\alpha + \beta) \cdot \vec{v} = \alpha \cdot \vec{v} + \beta \cdot \vec{v}$
- Rozdzielność mnożenia względem dodawania wektorów: $\forall \alpha \in F, \forall \vec{v}, \vec{u} \in V, \alpha \cdot (\vec{v} + \vec{u}) = \alpha \cdot \vec{v} + \alpha \cdot \vec{u}$
- Łączność mnożenia skalarów: $\forall \alpha, \beta \in F, \forall \vec{v} \in V, \alpha \cdot (\beta \cdot \vec{v}) = (\alpha \beta) \cdot \vec{v}$
- Zachowanie wektora przy mnożeniu przez jedynkę: $\forall \vec{v} \in V, 1 \cdot \vec{v} = \vec{v}$

Elementy $V$ nazywamy wektorami, a elementy $F$ - skalarami.

#### Przykłady przestrzeni liniowych:
1. $\mathbb{R}^n, \mathbb{C}^n, \{0\}, \mathbb{Q}^n, \mathbb{Z}_p^n$ nad odpowiednimi ciałami: $\mathbb{R}, \mathbb{C}, \text{dowolnym}, \mathbb{Q}, \mathbb{Z}_p$.
2. Zbiory funkcji: $\mathbb{R}^\mathbb{R}, \mathbb{R}^\mathbb{Q}, \mathbb{Q}^\mathbb{R}, \mathbb{Z}_p^\mathbb{R}, \mathbb{R}^\mathbb{N}$.
3. $\mathbb{R}, \mathbb{C}$ nad $\mathbb{Q}$.
4. Zbiory ciągów nieskończonych o wartościach w $\mathbb{R}, \mathbb{Z}_p$.
5. Zbiory ciągów skończonych o wartościach w $\mathbb{R}, \mathbb{Z}_p$.
6. Zbiory wielomianów o współczynnikach z $F$ nad $F$.

#### Fakty o przestrzeniach liniowych:
1. $\forall \vec{v} \in V, 0 \cdot \vec{v} = \vec{0}$ - Mnożenie dowolnego wektora przez skalar równy zero daje wektor zerowy, pokazując, że zero działa jako element neutralny mnożenia przez skalar.
2. $\forall \alpha \in F, \alpha \cdot \vec{0} = \vec{0}$ - Mnożenie wektora zerowego przez dowolny skalar zawsze daje wektor zerowy, co świadczy o braku wpływu skalara na wektor zerowy.
3. $\forall \vec{v} \in V, \alpha \in F, \alpha \cdot \vec{v} = \vec{0} \Leftrightarrow \vec{v} = \vec{0} \lor \alpha = 0$ - Jeśli iloczyn skalara i wektora daje wektor zerowy, to albo wektor jest wektorem zerowym, albo skalar jest równy zero, co wskazuje na jednoznaczność warunku na wektor i skalar prowadzący do wektora zerowego.
4. $\forall \vec{v} \in V, (-1) \cdot \vec{v} = -\vec{v}$ - Mnożenie wektora przez skalar równy -1 daje wektor przeciwny, pokazując jak skalowanie wpływa na kierunek wektora.
5. Wektor przeciwny jest dokładnie jeden dla każdego wektora - Dla każdego wektora istnieje tylko jeden unikalny wektor, który po dodaniu do niego daje wektor zerowy, zapewniając unikalność elementu przeciwnego.
6. Wektor zerowy jest dokładnie jeden w przestrzeni liniowej - Istnieje tylko jeden wektor, który działa jako element neutralny dodawania, co gwarantuje spójność struktury przestrzeni liniowej.

### 1.3 Podprzestrzenie liniowe

#### Definicja 1.5 (Podprzestrzeń liniowa)
Dla przestrzeni liniowej $V$, jej podzbiór $W \subseteq V$ jest podprzestrzenią liniową, gdy jest przestrzenią liniową nad tym samym ciałem i działania są określone tak, jak w $V$. Zapisujemy to jako $W \leq V$.

#### Przykłady podprzestrzeni liniowych:
1. Cała przestrzeń $V$ jest swoją podprzestrzenią.
2. Zbiór {$\vec{0}$} jest podprzestrzenią.
3. W $\mathbb{R}^n$ zbiór wektorów mających 0 na ustalonych współrzędnych.
4. W $\mathbb{R}^n$ zbiór wektorów o sumie współrzędnych równej 0.
5. Dla zbioru wszystkich wielomianów o współczynnikach z $F$, zbiór wielomianów o stopniu najwyżej $k$.
6. Dla zbioru wszystkich wielomianów o współczynnikach z $F$, zbiór wielomianów przyjmujących wartość 0 w ustalonym zbiorze punktów.
7. W $\mathbb{R}^n$ zbiór wektorów spełniających równania $x_1 + 2x_2 = 0$ i $x_3 - x_2 = 0$.

#### Lemat 1.7:
Podzbiór $U \subseteq V$ jest podprzestrzenią liniową przestrzeni $V$ wtedy i tylko wtedy, gdy dla dowolnych wektorów $u, v \in U$ oraz dla każdego skalaru $\alpha \in \mathbb{F}$ (gdzie $\mathbb{F}$ jest ciałem, nad którym zdefiniowana jest przestrzeń $V$), wynik dodawania wektorów $u + v$ oraz mnożenia wektora $u$ przez skalar $\alpha$ również należy do $U$. Oznacza to, że podprzestrzeń $U$ musi być zamknięta na operacje dodawania wektorów i mnożenia wektorów przez skalary, które są zdefiniowane w przestrzeni $V$. Innymi słowy, niezależnie od tego, jakie wektory z $U$ weźmiemy i jakiego skalaru użyjemy, operacje te nie mogą wyprowadzić nas poza zbiór $U$, co zapewnia, że $U$ zachowuje strukturę liniową z $V$.

#### Operacje na podprzestrzeniach liniowych:
- **Suma:** $W + W' = \{\vec{w} + \vec{w'}: \vec{w} \in W, \vec{w'} \in W'\}$
- **Przecięcie:** $\bigcap_{i\in I} W_i$ dla dowolnego zbioru podprzestrzeni liniowych $\{W_i\}_{i\in I}$.
- **Iloczyn kartezjański:** $\prod_{i\in I} V_i$ dla dowolnego zbioru przestrzeni liniowych $\{V_i\}_{i\in I}$ nad tym samym ciałem.


#### Lemat 1.9: Dla podprzestrzeni $W, W' \leq V$:

Suma $W + W'$ jest zbiorem ${w + w' | w \in W, w' \in W'}$. Reprezentuje najmniejszą przestrzeń liniową, która zawiera zarówno $W$, jak i $W'$, zapewniając zamkniętość na dodawanie wektorów pochodzących z obu podprzestrzeni.

Przecięcie $\bigcap_{i\in I} W_i$ składa się z wektorów wspólnych dla wszystkich podprzestrzeni $W_i$. Jest to największa przestrzeń liniowa, która mieści się całkowicie w każdej z rozpatrywanych podprzestrzeni, co oznacza, że zachowuje wszystkie operacje liniowe dopuszczalne w każdej z $W_i$.

Iloczyn kartezjański $\prod_{i\in I} V_i$ definiuje się jako zbiór krotek $(v_1, v_2, \ldots, v_n)$, gdzie każdy element $v_i$ pochodzi z przestrzeni $V_i$. Działania w tej przestrzeni wykonuje się niezależnie w każdej współrzędnej, co pozwala na konstruowanie wektorów w nowej, większej przestrzeni liniowej z wektorów należących do poszczególnych przestrzeni $V_i$.

### 1.4 Kombinacje liniowe wektorów
#### Definicja 1.10 (Kombinacja liniowa)
Dla wektorów $\vec{v}_1, \vec{v}_2, \ldots, \vec{v}k$ ich kombinacja liniowa to wektor postaci $\sum{i=1}^{k} \alpha_i \vec{v}_i$, gdzie $\alpha_1, \ldots, \alpha_k$ to skalary z ciała $F$. Kombinacja liniowa jest z definicji skończona.

**Przykłady kombinacji liniowych:**
W $\mathbb{R}^2$ prosta przechodząca przez $(0, 0)$ i $(1, 1)$ jest kombinacją wektora $[1, 1]$.
Prosta przez punkty $(1, 1)$ i $(2, 3)$ ma postać $\alpha[1, 1] + (1 - \alpha)[2, 3]$ dla $\alpha \in \mathbb{R}$.
Odcinek między $(1, 1)$ a $(2, 3)$ to $\alpha[1, 1] + (1 - \alpha)[2, 3]$ dla $\alpha \in [0, 1]$.
Równoległobok z wierzchołkami $\vec{v}_1, \vec{v}_2, \vec{v}_3, \vec{v}_4$, gdzie $\vec{v}_1 + \vec{v}_4 = \vec{v}_2 + \vec{v}_3$, to zbiór punktów $\vec{v}_1 +\alpha(\vec{v}_2 -\vec{v}_1) +\beta(\vec{v}_3 -\vec{v}_1)$ dla $\alpha, \beta \in [0, 1]$.

#### Definicja 1.12 (Otoczka liniowa)
Otoczka liniowa $LIN(U)$ dla zbioru wektorów $U$ w przestrzeni liniowej $V$ jest zbiorem tworzonym przez wszystkie kombinacje liniowe elementów z $U$. Oznacza to, że biorąc dowolne wektory z $U$ i łącząc je z dowolnymi skalarami z ciała $F$, można utworzyć każdy element otoczki liniowej

#### Fakt 1.14
$LIN(U)$ jest najmniejszą przestrzenią liniową, która zawiera $U$, co implikuje, że jakiekolwiek inne przestrzenie liniowe zawierające $U$ muszą również zawierać $LIN(U)$.

#### Lemat 1.16
Lemat podkreśla idempotentność operacji otoczki liniowej: $LIN(U) = LIN(LIN(U))$. Oznacza to, że $LIN(U)$ jest zamknięta na kombinacje liniowe swoich elementów. Dodatkowo, jeśli $U \subseteq LIN(U_0)$ i $U_0 \subseteq LIN(U)$, wówczas $LIN(U_0) = LIN(U)$, co ilustruje wzajemną zamkniętość otoczek liniowych tych zbiorów.

#### Lemat 1.17
Lemat mówi o niezmienniczości otoczki liniowej względem skalowania wektorów: $$LIN(\vec{v}_1, \ldots, \vec{v}_k) = LIN(\alpha_1\vec{v}_1, \ldots, \alpha_k\vec{v}_k)$$ gdzie $\alpha_i \neq 0$ dla wszystkich $i$. To pokazuje, że mnożenie wektorów przez niezerowe skalary nie wpływa na przestrzeń przez nie rozpiętą.

#### Lemat 1.18
Lemat mówi, że jeśli mamy zbiór wektorów ${\vec{v}_1, \vec{v}_2, \ldots, \vec{v}k}$ w przestrzeni liniowej $V$ nad ciałem $F$, oraz ciąg skalarny ${\alpha_1, \alpha_2, \ldots, \alpha_k}$, gdzie $\alpha_1 \neq 0$, to otoczka liniowa $$\text{LIN}\left(\sum_{i=1}^k \alpha_i \vec{v}_i, \vec{v}_2, \ldots, \vec{v}_k\right) = \text{LIN}(\{\vec{v}_1, \vec{v}_2, \ldots, \vec{v}_k\})$$
To podkreśla, że wprowadzenie kombinacji liniowej wektora nie zmienia przestrzeni rozpinanej przez ten zbiór.

### 1.5 Liniowa niezależność wektorów

#### Definicja 1.19
Układ wektorów $U$ jest **liniowo niezależny**, gdy dla dowolnego $k \geq 1$, dowolnych różnych wektorów $\vec{v}_1, \ldots, \vec{v}_k \in U$ oraz ciągu współczynników $\alpha_1, \ldots, \alpha_k \in F$, równość:

$$
\sum_{i=1}^{k} \alpha_i \cdot \vec{v}_i = \vec{0}
$$

implikuje, że wszystkie współczynniki są zerowe:

$$
\alpha_1 = \alpha_2 = \cdots = \alpha_k = 0.
$$

**Uwaga:** $U$ traktujemy jako multizbiór, co oznacza, że jeśli zawiera pewien element $m$ razy, można go $m$ razy użyć. W takim przypadku, $U$ jest liniowo zależny, ponieważ $\vec{v} + (-1) \cdot \vec{v} = \vec{0}$.

#### Lemat 1.20
Niech $B \subseteq V$ będzie układem wektorów. Następujące warunki są równoważne:

1. Układ $B$ jest liniowo niezależny.
2. Wektor $\vec{0}$ ma dokładnie jedno przedstawienie w postaci kombinacji liniowej wektorów ze zbioru $B$.
3. Pewien wektor z $LIN(B)$ ma dokładnie jedno przedstawienie w postaci kombinacji liniowej wektorów ze zbioru $B$.
4. Każdy wektor z $LIN(B)$ ma najwyżej jedno przedstawienie w postaci kombinacji liniowej wektorów z $B$.

#### Fakt 1.21
Niech $V$ będzie przestrzenią liniową. Układ wektorów $U \subseteq V$ jest liniowo zależny wtedy i tylko wtedy, gdy jeden z nich można przedstawić jako liniową kombinację pozostałych. Równoważnie, układ wektorów $U \subseteq V$ jest liniowo zależny wtedy i tylko wtedy, gdy istnieje $\vec{u} \in U$ taki, że $\vec{u} \in LIN(U \setminus \{\vec{u}\})$.

#### Fakt 1.22
Niech $V$ będzie przestrzenią liniową. Układ wektorów $U \subseteq V$ jest liniowo zależny wtedy i tylko wtedy, gdy istnieje $\vec{u} \in U$ taki, że $LIN(U) = LIN(U \setminus \{\vec{u}\})$. Jeśli $U$ nie zawiera $\vec{0}$, istnieją przynajmniej dwa takie wektory.

#### Lemat 1.23 (Porównaj Lemat 1.18)
Niech $U = (\vec{v}_1, \ldots, \vec{v}_k)$ będzie układem wektorów. Rozpatrzmy układy:
- $U' = (\vec{v}_1, \ldots, \vec{v}_{i-1}, \alpha\vec{v}_i, \vec{v}_{i+1}, \ldots, \vec{v}_k)$ dla $\alpha \neq 0$, $1 \leq i \leq k$
- $U'' = (\vec{v}_1, \ldots, \vec{v}_{i-1}, \vec{v}_i + \alpha\vec{v}_j, \vec{v}_{i+1}, \ldots, \vec{v}_k)$ dla $i \neq j$

Wtedy $U$ jest liniowo zależny wtedy i tylko wtedy, gdy $U'$ jest liniowo zależny, wtedy i tylko wtedy, gdy $U''$ jest liniowo zależny.

### 1.6 Metoda eliminacji Gaussa

Metoda eliminacji Gaussa to usystematyzowany sposób na znajdowanie dla danego skończonego zbioru wektorów \(U \subseteq F^n\) jego maksymalnego podzbioru niezależnego. Chcemy uogólnić następujące obserwacje:

- Jeśli każdy wektor ma współrzędną, na której tylko on jest niezerowy, zbiór jest liniowo niezależny.
- Układ wektorów zawierający \(\vec{0}\) nie jest niezależny.
- Możemy "upraszczać" wektory używając Lematu 1.23, co pokazuje, że oryginalny układ wektorów był liniowo zależny, natomiast bez pierwszego danego wektora jest liniowo niezależny.

#### Definicja 1.25 (Postać schodkowa)

Układ wektorów \(V_1, \ldots, V_m \in F^n\) jest w postaci schodkowej, jeżeli istnieje ciąg pozycji \(0 = i_0 < i_1 < i_2 < \cdots < i_m\) taki, że dla każdego \(j = 1, \ldots, m\):

- Wektor \(V_j\) ma na pozycji \(i_j\) element niezerowy.
- Wektor \(V_j\) ma na pozycjach mniejszych niż \(i_j\) same zera.

#### Lemat 1.26

Jeśli układ wektorów w \(F^n\) jest w postaci schodkowej, to jest niezależny.

**Dowód:** Rozważamy wektory \(V_1, \ldots, V_k\) i ich pozycje z definicji postaci schodkowej \(i_1, \ldots, i_m\). Dla kombinacji liniowej równającej się zeru z najmniejszym niezerowym współczynnikiem \(\alpha_j\), otrzymujemy sprzeczność, gdyż suma daje niezerową wartość na pozycji \(i_j\).

#### Metoda eliminacji Gaussa - Proces

1. Rozpoczynamy z całym zbiorem wektorów \(U\), pustym zbiorem \(U'\) i \(j = 0\).
2. W każdym kroku utrzymujemy \(U'\) w postaci schodkowej, z indeksami niezerowych pozycji nie większymi niż \(j\), a wektory w \(U\) mają na pozycjach nie większych niż \(j\) same zera.
3. Wybieramy pozycję \(j'\) oraz wektor \(V \in U\) tak, że:
   - \(j' > j\) i \(j'\) jest najmniejszą taką pozycją, gdzie któryś z wektorów z \(U\) ma niezerową współrzędną.
   - \(V\) ma niezerową współrzędną na \(j'\).
4. Dodajemy \(V\) do \(U'\) i wybieramy \(j'\) jako nowe \(j\).
5. Dla każdego \(V' \in U \setminus \{V\}\), zastępujemy \(V'\) przez \(V' - \frac{\alpha'}{\alpha} V\), gdzie \(\alpha\) i \(\alpha'\) to współrzędne na \(j\).

#### Lemat 1.27

Na końcu procesu otrzymujemy układ złożony z wektorów liniowo niezależnych oraz samych wektorów zerowych. Wektory niezależne rozpinają oryginalną przestrzeń.

#### Fakt 1.28

Oryginalny zbiór był niezależny wtedy i tylko wtedy, gdy nie otrzymaliśmy żadnego wektora \(\vec{0}\). Jeśli w czasie eliminacji Gaussa używaliśmy do eliminowania jedynie wektorów \(V_1, \ldots, V_n\), które na końcu są niezerowe, odpowiadające im wektory początkowe rozpinają tę samą przestrzeń co wszystkie wektory początkowe.

### Kluczowe Koncepcje:

- **Ciała**: Struktury algebraiczne z dwiema operacjami (dodawanie, mnożenie) spełniające pewne aksjomaty (np. przemienność, istnienie elementu odwrotnego).
- **Przestrzenie liniowe**: Zbiory wektorów nad ciałem, gdzie zdefiniowane są operacje dodawania wektorów i mnożenia przez skalar, spełniające określone aksjomaty.
- **Liniowa Niezależność**: Koncepcja określająca, że zbiór wektorów jest liniowo niezależny, jeśli żaden z nich nie może być wyrażony jako kombinacja liniowa pozostałych.
- **Eliminacja Gaussa**: Metoda rozwiązania układów równań liniowych poprzez sprowadzenie macierzy do schodkowej formy rzędowej, co ułatwia znalezienie rozwiązań.

---

## 2 Baza przestrzeni liniowej, wymiar

### 2.1 Baza przestrzeni liniowej

Chcemy określić minimalny (niezależny) układ wektorów generujący daną przestrzeń, co ma wiele pozytywnych właściwości.

#### Definicja 2.1 (Baza)

Baza \(B\) przestrzeni liniowej \(V\) jest określona, gdy \(LIN(B) = V\) oraz \(B\) jest liniowo niezależny. Innymi słowy, \(B\) jest minimalnym zbiorem rozpinającym \(V\).

#### Przykłady baz

- W przestrzeni \(F^n\), tzw. baza standardowa składa się z wektorów \(E_1 = (1, 0, \ldots, 0), E_2 = (0, 1, 0, \ldots, 0), \ldots, E_{n-1} = (0, \ldots, 0, 1, 0), E_n = (0, \ldots, 0, 1)\).
- W przestrzeni wielomianów stopnia \(\leq n\), bazę stanowią wielomiany \(\{x^i\}_{i=0}^n\).
- W przestrzeni ciągów o wyrazach w \(F\), które mają skończenie wiele niezerowych wyrazów, bazę tworzą \(\{e_i\}\), gdzie \(e_i\) ma 1 na i-tej pozycji i 0 wszędzie indziej. Ta baza jest nieskończona.

#### Twierdzenie 2.3

Metoda eliminacji Gaussa zastosowana do układu wektorów \(U\) zwraca bazę \(LIN(U)\) oraz ewentualne wektory zerowe. Wektory z wejścia odpowiadające uzyskanej bazie również stanowią bazę.

##### Uwaga

Gdy użyjemy metody eliminacji Gaussa i skupimy się tylko na wektorach, które tworzą bazę, to te wybrane wektory są niezależne i całkowicie opisują naszą przestrzeń - tworzą bazę. Ale, jeśli do tych wektorów dodamy jeszcze inne, to możemy zmienić charakter zbioru - niektóre z nowych wektorów mogą sprawić, że całość stanie się zależna.

##### Co to znaczy dla nas i jak to wykorzystać?

To oznacza, że mając dowolny zbiór wektorów, możemy użyć eliminacji Gaussa, aby znaleźć najprostszy, niezależny zbiór wektorów (bazę), który opisuje tę samą przestrzeń. Jest to przydatne, gdy chcemy uprościć problem lub znaleźć podstawowe elementy, z których każdy wektor w przestrzeni może być zbudowany.

Dzięki temu procesowi:

1. Możemy zidentyfikować nadmiarowe wektory, które nie wpływają na charakter przestrzeni.
2. Zyskujemy zbiór fundamentalnych wektorów, które są niezbędne do opisania całej przestrzeni.
3. Ułatwiamy sobie pracę z przestrzenią, gdyż pracujemy z mniejszą liczbą wektorów.

W praktyce, jeśli chcesz zrozumieć strukturę przestrzeni lub znaleźć jej bazę, eliminacja Gaussa jest narzędziem do identyfikacji kluczowych wektorów, eliminując jednocześnie te, które są zbędne.


#### Definicja 2.4 (Przestrzeń skończenie wymiarowa)

Przestrzeń jest skończenie wymiarowa, jeśli posiada skończony zbiór rozpinający

### 2.2 Wyrażanie wektora w bazie

#### Definicja 2.5 (Wyrażanie wektora w bazie)
Jeśli $B = \{\vec{v}_1, \ldots, \vec{v}_n\}$ jest bazą przestrzeni liniowej $V$ oraz $\vec{v} \in V$ jest wektorem, to wyrażeniem wektora $\vec{v}$ w bazie $B$ nazywamy reprezentację $\vec{v}$ jako sumę:
$$\vec{v} = \sum_{i=1}^{n} \alpha_i\vec{v}_i.$$
Każdy skalar $\alpha_i$ jest współczynnikiem przy wektorze bazowym $\vec{v}_i$ w tej reprezentacji.

#### Przykład 2.6
Dla bazy $B = \{(1, 1, 1), (0, 1, 1), (0, 0, 1)\}$ przestrzeni $\mathbb{R}^3$, wektory bazy standardowej $E_1, E_2, E_3$ mogą być wyrażone jako $E_1 = (1, 1, 1) - (0, 1, 1), E_2 = (0, 1, 1) - (0, 0, 1)$ i $E_3 = (0, 0, 1)$.

#### Twierdzenie 2.7
Każdy wektor ma jednoznaczne przedstawienie w bazie. Dowód tego twierdzenia opiera się na założeniu liniowej niezależności zbioru bazowego $B$ i wskazuje, że różne przedstawienia tego samego wektora w bazie prowadzą do sprzeczności.

#### Definicja 2.8 (Notacja: Wyrażanie wektora w bazie)
Jeśli $B = \{\vec{v}_1, \vec{v}_2, \ldots, \vec{v}_n\}$ jest bazą przestrzeni liniowej $V$ oraz $\vec{v} \in V$ jest wektorem, to jego reprezentację w bazie $B$ oznaczamy jako $(\vec{v})_B = (\alpha_1, \alpha_2, \ldots, \alpha_n)$, gdzie $\vec{v} = \sum_{i=1}^{n} \alpha_i\vec{v}_i$. Współczynniki $\alpha_i$ to współrzędne wektora $\vec{v}$ w bazie $B$.

#### Przykład 2.9
Kontynuując poprzedni przykład dla bazy $B$, mamy $(E_1)_B = (1, -1, 0), (E_2)_B = (0, 1, -1)$, i $(E_3)_B = (0, 0, 1)$. Użycie tej reprezentacji ułatwia, na przykład, pokazanie, że dla $\vec{V} = (7, 4, 2)$ mamy $(\vec{V})_B = (7, -3, -2)$, ponieważ $(\vec{V})_B = 7(E_1)_B + 4(E_2)_B + 2(E_3)_B$.

Zauważmy, że po wyrażeniu wektorów $\vec{v}_1, \ldots, \vec{v}_n$ w ustalonej bazie $B$, możemy traktować je podobnie jak wektory z $\mathbb{F}^n$. W pewnym sensie jest to „dokładne” odwzorowanie.

#### Definicja 2.10 (Izomorfizm przestrzeni liniowych)

Izomorfizm przestrzeni liniowych to takie odwzorowanie między dwiema przestrzeniami \(V\) i \(W\) nad tym samym ciałem \(F\), które jest bijekcją (odwzorowaniem wzajemnie jednoznacznym) i zachowuje operacje przestrzeni liniowej: dodawanie wektorów i mnożenie przez skalar. Formalnie, jeśli \(\phi: V \to W\) jest izomorfizmem, to dla wszystkich \(\vec{v}, \vec{v}_0 \in V\) i \(\alpha \in F\), zachodzi:
- \(\phi(\vec{v} + \vec{v}_0) = \phi(\vec{v}) + \phi(\vec{v}_0)\)
- \(\phi(\alpha \cdot \vec{v}) = \alpha \cdot \phi(\vec{v})\)

#### Przykłady izomorfizmu:

- Przestrzeń wielomianów stopnia nie większego niż \(k\) i \(F^{k+1}\) są izomorficzne.
- Przestrzeń wielomianów i przestrzeń ciągów o skończonej liczbie niezerowych elementów również są przykładami przestrzeni izomorficznych.

#### Lemat 2.12

Wyrażenie wektora w ustalonej bazie skończenie wymiarowej przestrzeni \(V\) nad ciałem \(F\) stanowi izomorfizm między \(V\) a \(F^{|B|}\), gdzie \(|B|\) to liczba elementów w bazie. Oznacza to, że każdy wektor w przestrzeni \(V\) może być jednoznacznie przedstawiony jako ciąg współrzędnych w \(F^{|B|}\), zachowując przy tym strukturę liniową.

#### Znaczenie izomorfizmu:

Izomorfizm pokazuje, że struktury dwóch przestrzeni liniowych są "równoważne" w sensie operacji liniowych. Pozwala to na przenoszenie problemów matematycznych i intuicji między różnymi kontekstami matematycznymi, co jest szczególnie użyteczne w przypadku analizy i rozumienia złożonych przestrzeni przez odwołanie do bardziej znanych lub łatwiejszych do zrozumienia przestrzeni.

### Fakt 2.13

Jeśli $\phi: V \to W$ jest izomorfizmem, to układ $\{\mathbf{v}_1, \ldots, \mathbf{v}_n\}$ jest liniowo niezależny wtedy i tylko wtedy, gdy układ $\{\phi(\mathbf{v}_1), \ldots, \phi(\mathbf{v}_n)\}$ jest liniowo niezależny.

#### Twierdzenie 2.14

Twierdzenie 2.14 mówi, że jeśli przestrzeń liniowa \(V\) nad ciałem \(F\) posiada bazę składającą się z \(n\) elementów, to \(V\) jest izomorficzna z \(F^n\). Innymi słowy, dowolne dwie przestrzenie liniowe nad tym samym ciałem \(F\), które mają bazy o tej samej liczbie elementów, są izomorficzne.

##### Co to oznacza?

Oznacza to, że struktura przestrzeni liniowej jest całkowicie określona przez liczbę elementów w jej bazie. Jeśli dwie przestrzenie mają bazy o tej samej liczbie elementów, można przeprowadzić operacje na wektorach w jednej przestrzeni, mając pewność, że te same operacje będą miały analogiczne skutki w drugiej przestrzeni. To podkreśla uniwersalność i elastyczność koncepcji przestrzeni liniowych oraz umożliwia uproszczenie wielu problemów matematycznych poprzez analizę w bardziej znanych lub wygodnych przestrzeniach.

#### Twierdzenie 2.15

Każda skończenie wymiarowa przestrzeń liniowa \(V\) posiada bazę, a każda baza tej przestrzeni ma taką samą liczbę elementów, co oznacza, że wszystkie bazy skończenie wymiarowej przestrzeni liniowej są równoliczne.

#### Lemat Steinitza o wymianie (Lemat 2.16)

Dla przestrzeni liniowej \(V\), jeśli mamy liniowo niezależny zbiór wektorów \(A\) oraz zbiór wektorów \(B\), który rozpina \(V\), to można zawsze rozszerzyć zbiór \(A\) o wektory z \(B\), aby nadal był liniowo niezależny, aż do uzyskania bazy \(V\).

#### Co to oznacza w praktyce?

- **Twierdzenie 2.15** zapewnia, że niezależnie od wybranej przestrzeni liniowej, zawsze można znaleźć zestaw wektorów, które jednoznacznie określają każdy wektor w tej przestrzeni, co jest podstawą do definiowania wymiaru przestrzeni.
- **Lemat Steinitza** pokazuje metodę na budowanie bazy z dowolnego liniowo niezależnego zbioru wektorów, co jest kluczowe przy dowodzeniu istnienia baz oraz w procesie znajdowania konkretnej bazy dla danej przestrzeni liniowej.

##### Wnioski z Lematu Steinitza

#### Lemat 2.17
Każdy liniowo niezależny zbiór wektorów w skończenie wymiarowej przestrzeni liniowej \(V\) można rozszerzyć do bazy przestrzeni. To oznacza, że zawsze istnieje sposób, aby z dowolnego zestawu wektorów, które nie są liniowo zależne, utworzyć pełną bazę przestrzeni.

#### Lemat 2.18
W każdej skończenie wymiarowej przestrzeni liniowej \(V\), z każdego zbioru wektorów \(A \subseteq V\) można wybrać bazę dla przestrzeni przez nie rozpinanej \(LIN(A)\). Wskazuje to na uniwersalność koncepcji bazy oraz na to, że dowolny zbiór wektorów ma w sobie "zakodowane" potencjalne bazy.

##### Przykłady Zastosowania

#### Eigenfaces
- **Problem:** Rozpoznawanie twarzy.
- **Metoda:** Reprezentacja obrazów twarzy jako wektory przestrzeni.
- **Klucz:** Wykorzystanie bazy wektorów własnych do klasyfikacji i identyfikacji twarzy.
- **Wynik:** Umożliwia efektywne rozpoznawanie twarzy i zwiększa skupienie zdjęć jednej osoby.

#### Wielomiany
- **Problem:** Obliczanie wartości wielomianu w punkcie oraz mnożenie wielomianów.
- **Metoda:** Reprezentacja wielomianów w bazie jednomianów lub poprzez wartości w \(k + 1\) punktach.
- **Wynik:** Ułatwia obliczenia i interpolację wielomianów.

#### Transformata Fouriera
- **Problem:** Analiza i modyfikacja dźwięku.
- **Metoda:** Przekształcenie reprezentacji dźwięku do bazy dźwięków bazowych (sinusy i cosinusy różnych częstotliwości).
- **Wynik:** Umożliwia lepszą analizę dźwięku, filtrację i modyfikację charakterystyk częstotliwościowych.

Te przykłady ilustrują, jak rozumienie baz i przekształceń izomorficznych umożliwia rozwiązanie złożonych problemów poprzez uproszczenie ich reprezentacji.

### 2.3 Wymiar przestrzeni liniowej

#### Definicja 2.22 (Wymiar przestrzeni liniowej)
Wymiar przestrzeni skończenie wymiarowej \(V\) jest równy mocy jej bazy, oznaczany jako \(\dim(V)\). To "n" w \(\mathbb{R}^n\) lub ogólnie w \(F^n\). Dla przestrzeni \(V = \{0\}\), przyjmujemy, że jej wymiar to 0, co jest konwencją spójną z innymi faktami: ta przestrzeń ma 0-elementową bazę.

#### Wniosek 2.23
Każde dwie przestrzenie liniowe \(n\)-wymiarowe nad \(F\) są izomorficzne i izomorficzne z \(F^n\).

#### Lemat 2.24 (Formuła na wymiar sumy przestrzeni)
Jeśli \(V_1, V_2 \leq V\) są przestrzeniami skończenie wymiarowymi, to:
\[ \dim(V_1 + V_2) = \dim(V_1) + \dim(V_2) − \dim(V_1 \cap V_2) \]
Pokazuje to, jak obliczyć wymiar przecięcia \(V_1 \cap V_2\), mając wymiary \(V_1\), \(V_2\) i znając wymiar ich sumy.

#### Fakt 2.25
Jeśli \(B_1\) i \(B_2\) są bazami dla \(V_1, V_2 \leq V\), to:
\[ V_1 + V_2 = \text{LIN}(B_1 \cup B_2) \]
Znając \(\dim(V_1)\) i \(\dim(V_2)\), jesteśmy w stanie obliczyć moc bazy \(V_1 + V_2\), a więc znamy wymiar \(V_1 + V_2\). Pozwala to na policzenie wymiaru \(V_1 \cap V_2\), co jest użyteczne w wielu kontekstach matematycznych, szczególnie przy analizie złożoności przestrzeni wygenerowanych przez różne zbiory wektorów.

### 2.4 Zastosowanie eliminacji Gaussa do liczenia wymiaru

- Eliminację Gaussa stosujemy do zbioru wektorów $A$, aby obliczyć $\text{dim}(\text{LIN}(A))$, co oznacza, że po eliminacji otrzymujemy zbiór wektorów liniowo niezależnych wraz z wektorami zerowymi, a przestrzeń generowana przez te wektory pozostaje niezmieniona. Zatem otrzymany zbiór wektorów liniowo niezależnych stanowi bazę, a jej liczność odpowiada liczbie wymiarów przestrzeni.

#### Fakt 2.26
- Jeżeli po zakończeniu eliminacji Gaussa otrzymamy zbiór składający się z $k$ niezerowych wektorów (oraz dowolnej liczby wektorów zerowych), to oryginalny zbiór zawierał dokładnie $k$ wektorów niezależnych.

#### Przykład 2.27
- Rozważmy przestrzenie liniowe $S$ i $T$, określone jako $S = \text{LIN}(\{(1, 6, 5, 5, 3), (1, 2, 3, 2, 2)\})$ oraz $T = \text{LIN}(\{(3, 4, 5, 3, 3), (2, 1, 3, 1, 2)\})$. Obliczamy $\text{dim}(S + T)$ oraz $\text{dim}(S \cap T)$ i podajemy bazę $S + T$. Z zależności:
$$\text{dim}(S + T) = \text{dim}(S) + \text{dim}(T) - \text{dim}(S \cap T)$$
- Wymiar $\text{LIN}(S + T)$ wynosi 3, co oznacza, że wymiar $\text{LIN}(S) \cap \text{LIN}(T)$ wynosi 1. Baza $S + T$ składa się z wektorów $(1, 2, 3, 2, 2), (0, 1, -1, 0, -1), (0, 0, -6, -3, -5)$.

### 2.4.1 Wybór bazy

Wybór odpowiedniej bazy jest kluczowy dla zrozumienia problemów i znalezienia prostych rozwiązań. Na przykład, w przypadku rekurencji liniowych, jak rekurencja na liczby Fibonacciego (\(f_n = f_{n-1} + f_{n-2}, f_1 = f_2 = 1\)), znalezienie odpowiedniej bazy może uprościć problem.

Rozważając rekurencję \(a_n = a_{n-1} + 2a_{n-2}\) z warunkami początkowymi \(a_0 = \alpha, a_1 = \beta\), możemy traktować zbiór ciągów spełniających to równanie jako przestrzeń liniową. Wyszukując bazę składającą się z ciągów, których elementy łatwo można obliczyć, natrafiamy na ciągi geometryczne jako potencjalne kandydaty.

Rozwiązując równanie charakterystyczne \(x^2 - x - 2 = 0\), znajdujemy, że baza tej przestrzeni może składać się z ciągów \(2^n\) i \((-1)^n\). Współczynniki tych ciągów należy odpowiednio dobrać, aby spełniały warunki początkowe. Takie podejście do wyboru bazy ułatwia rozwiązanie problemu, pokazując jak kluczowe jest znalezienie odpowiedniej bazy dla danej przestrzeni liniowej.

### 2.5 Warstwy

Warstwy w przestrzeni liniowej \(V\) z podprzestrzenią \(W\) są zbiorami wynikającymi z przesunięcia \(W\) o wektor \(u\). Dla przestrzeni \(V\) i jej podprzestrzeni \(W\), zbiór \(U\) jest warstwą \(W\) w \(V\) jeśli przyjmuje postać \(U = \{u + w : w \in W\}\), gdzie \(u\) jest ustalonym wektorem.

- **Przykłady**:
  1. W przestrzeni \(R^n\) z podprzestrzenią, gdzie trzecia współrzędna to 0, warstwami są zbiory wektorów o ustalonej trzeciej współrzędnej.
  2. Dla wektorów spełniających \(2x_1 - x_3 = 0\), każda warstwa zawiera wektory, dla których \(2x_1 - x_3\) ma ustaloną wartość.
  3. W przestrzeni wielomianów z podprzestrzenią składającą się z wielomianów zerujących się w punktach 2 i 4, warstwy zawierają wielomiany o ustalonej wartości w tych punktach.

Dodawanie zbiorów wektorów jest łączne i przemienne, co oznacza, że dla podprzestrzeni \(W\), zachodzi \(W + W = W\).

**Lemat 2.32** równoważność warunków:
  1. Istnieje wektor \(u \in V\), taki że \(U = u + W\).
  2. Istnieje wektor \(u \in U\), taki że \(U = u + W\).
  3. Dla każdego wektora \(u \in U\), zachodzi \(U = u + W\).
    Lemat ułatwia identyfikację, kiedy zbiór wektorów może być traktowany jako przesunięcie (warstwa) podprzestrzeni liniowej, co jest pomocne w analizie rekurencji prawie liniowych poprzez transformację do postaci liniowej.

**Lemat 2.33**:
  Niech \(U\) i \(U'\) będą warstwami podprzestrzeni \(W\). Wtedy \(U = U'\) lub \(U \cap U' = \emptyset\).

  Lemat pokazuje, że dwie warstwy podprzestrzeni liniowej albo są identyczne, albo nie mają wspólnych elementów, co może być wykorzystane do klasyfikacji różnych rozwiązań rekurencji prawie liniowej w zależności od ich warunków początkowych.

**Lemat 2.34**:
  Przecięcie dwóch warstw jest puste lub jest warstwą (jakiejś podprzestrzeni).
  Lemat wskazuje, że przecięcie dwóch warstw jest albo puste, albo stanowi warstwę innej podprzestrzeni, co może być użyte do analizy relacji między różnymi rozwiązaniami rekurencji prawie liniowej.

**Wypukłość warstw (Lemat 2.35)**:
  Warstwa jest wypukła, co oznacza, że jeśli dwa punkty należą do warstwy, to cała prosta przez nie przechodząca również należy do tej warstwy. Warunki równoważne bycia warstwą to:
  1. \(U\) jest warstwą.
  2. Dla wszystkich \(\alpha \in F\), \(v, u \in U\), zachodzi \(\alpha v + (1 - \alpha)u \in U\).

  Lemat dotyczy wypukłości warstw, co ma zastosowanie w analizie, jak różne wartości początkowe wpływają na przestrzeń rozwiązań rekurencji prawie liniowej, ułatwiając znajdowanie ogólnych wzorców lub właściwości tych rozwiązań.

#### Rekurencja prawie liniowa

Rekurencja prawie liniowa to rodzaj rekurencji, która przypomina rekurencję liniową, ale zawiera dodatkowe, niezależne od poprzednich elementów ciągu, stałe lub funkcje. Typowa rekurencja liniowa definiowana jest przez równanie \(a_n = c_1a_{n-1} + c_2a_{n-2} + \ldots + c_ka_{n-k}\), gdzie \(c_1, \ldots, c_k\) są stałymi. W przypadku rekurencji prawie liniowej, równanie to uzupełniane jest o składnik, który nie zależy od wcześniejszych elementów ciągu, np. \(a_n = c_1a_{n-1} + c_2a_{n-2} - f(n)\), gdzie \(f(n)\) jest pewną stałą lub funkcją niezależną od \(a_n, a_{n-1}, \ldots\).

### Podsumowanie

Rozdział drugi skupia się na kluczowych pojęciach baz przestrzeni liniowych i ich wymiarów, co jest istotne dla zrozumienia struktury przestrzeni liniowej.

#### Najważniejsze koncepcje:
- **Baza przestrzeni liniowej** jest minimalnym zbiorem wektorów liniowo niezależnych, który rozpina daną przestrzeń.
- **Wymiar przestrzeni liniowej** jest określany przez liczbę elementów w bazie tej przestrzeni.
- **Izomorfizm przestrzeni liniowych** pokazuje, że struktury dwóch przestrzeni są "równoważne", co umożliwia przenoszenie intuicji i rozwiązań między różnymi przestrzeniami.
- **Warstwa** to zbiór elementów przestrzeni liniowej, które można przedstawić jako przesunięcie podprzestrzeni liniowej o wektor nie należący do tej podprzestrzeni. To pojęcie jest kluczowe dla analizy przekształceń liniowych i relacji między podprzestrzeniami.

#### Ważne lematy i twierdzenia:
- **Twierdzenie 2.3** mówi, że metoda eliminacji Gaussa pozwala znaleźć bazę danej przestrzeni liniowej.
- **Twierdzenie 2.14** wskazuje, że przestrzenie liniowe nad tym samym ciałem i mające bazy o tej samej liczbie elementów są izomorficzne.
- **Lemat Steinitza o wymianie** (Lemat 2.16) pokazuje, jak z dowolnego liniowo niezależnego zbioru wektorów można zbudować bazę przestrzeni liniowej.
- **Twierdzenie o warstwach** podkreśla, że wszystkie warstwy danej podprzestrzeni liniowej są równoliczne, co oznacza, że każda warstwa może być traktowana jako "przesunięcie" podprzestrzeni przez wektor nie należący do tej podprzestrzeni.
- **Lemat o złożoności warstw** wskazuje na to, jak warstwy mogą być użyte do analizy złożoności problemów w przestrzeniach liniowych, pozwalając na lepsze zrozumienie relacji między podprzestrzeniami i całej przestrzeni.


---





