# Rozdział 14

---

### Automorfizmy 
Dla danego obiektu kombinatorycznego $S$ jego grupa przekształceń (symetrii, automorfizmów) $G = Aut(S)$ powinna spełniać naspępujęce warunki:
* przekształcenie identycznościowe $e$ jest w $G$ 
* jeśli $\varphi_1, \varphi_2 \in G$ to te przekształcenia można uzyzłożyć uzyskując $\varphi = \varphi_1 \circ \varphi_2 \in G$ 
* dla każdego $\varphi \in G$ istnieje $\varphi^{-1}$ taki że $\varphi^{-1} \varphi = \varphi \varphi^{-1} = e$

### Grupa
Zbiór $(G, \cdot), \ gdzie \ \cdot : G \times G \rightarrow G$ jest działaniem dwuargumentowym jest grupą dxy:
* **łączność** działanie $\cdot$ jest łącznie
* **element neutralny** istnieje element neutralny $e$ taki że dla każdego $g \in G$ mamy $ge = eg = g$
* **element odwrotny** dla każdego $g \in G$ istnieje $g^{-1}$ spełniający $g^{-1}g = gg^{-1} = e$

jeśli $\cdot$ jest przenienne to mówimy o grupie przemiennej (abelowej) 

własności:
* element odwrotny w grupie $G$ jest jedyny
* element prawostronnie odwrotny jest też lewostronnie odwrotny
* identyczność jest jedna 
* równanie ax = b oraz xa = b mają dokładnie jedno rozwiązanie 

##### Półgrupy
W ogólności rozważa sie też monoidy (półgrupy) w których nie zakłądamy istnienia elementu odwrotnego 

### Tabelka diałań (mnożenia) 
Tabelka działań dla grupy $G$ podaje wprost wszystkie możliwe $|G|^2$ wyników mnorzenia

przykład: (tabela działań dla grupy klaina: {1, 3, 5, 7} z mnożeniem mod 8)
| $\cdot _ {mod \ 8}$ | 1 | 3 | 5 | 7 |
|---|---|---|---|---|
| **1** | 1 | 3 | 5 | 7 |
| **3** | 3 | 1 | 7 | 5 |
| **5** | 5 | 7 | 1 | 3 |
| **7** | 7 | 5 | 3 | 1 |

własności:
* każdy wiersz i każda kolumna w tabelce działań jest permutacją elementów z $G$
* Dwa rózne wiersze (dwie rózne kolumny) są różne
* Musi być dokładnie jeden wiersz (kolumna) w której permutacja jest identycznością 

Dla grup $G,H$ przez $G \times H$ oznaczamy grupę na zbiorze $G \times H$ i działaniu po współrzędnych (definicję rozszerzamy naturalnie na iloczyn karezjański dowolnej ilości grup)
$$
(g, h) \cdot (g', h') = (gg', hh')
$$

### Homomorfizm, Izomorfizm 
operacje  $\varphi : \mathbb{G} \rightarrow \mathbb{H}$ nazywamy homomorfizmem grup, jeśli zachowuje działanie grupowe, czyli $ \varphi(ab) = \varphi(a) \varphi(b)$
$\varphi$ jest izomorfizmem, jeśli istnieje $\varphi^{-1}$ które jest przekształceniem odwrotnym i homomorfizmem w szczególności $\varphi, \varphi^{-1}$ są bijekcjami

Homomorfizm przeprowadza element neutralny w neutralny
Homomorfizm przeprowadza element odwrotny w odwrotny 

### Rząd elementu 
Potęgą elementu $a$ nazywamy dowolny element postaci $a^n$, gdzi $n \in \Z$. Dla $n = 0$ oznacza on $e$, dla $n > 1: a^n = a \cdot a \cdot \cdot \cdot a$ dla $n < 0: a^n = (a^{-1})^{-n}$

rząd elementu to najmniejsza dotatni potęga $n$ taka że $a^n = e$
rząd elementu jest nieskończony (nieokreślony), jeśli nie ma takiego skończonego $n$ 
rząd grupy to ilość jej elementów (może, ale nie musi byc skończony) 

Rząd $a$ i rząd $a^{-1}$ jest taki sam 

W grupie skończonej każdy element ma rząd skończony 

$Jeśli \ a \in G \ ma \ skończony \ rząd \ p, \ to \ a^\ell = e \iff p | \ell$ 
czyli dla elementu $a$ o skończonym rzędzie $p$, podniesienie $a$ do potęgi $\ell$ da element neutralny $e$ wtedy i tylko wtedy gdy $\ell$ jest wielokrotnością $p$ ($p$ dzieli $\ell$)

### Podgrupy 
$H$ jest podgrupą $G$, co zapisujemy jako $H \leq G$, dgy $H \sube G$ oraz jest grupą 

W grupie skończonej $G$ niepusty zbiór $H$ jet podgrupą wtedy i tylko wtedy gdy jest zamknięty na działanie 
W grupie, w której rząd każdego elementu jest skończony, niepusty podzbiór H jest podgrupą wtedy i tylko wtedy gdy jest zamknięty na działanie 

Dla grupy $G$ oraz zbioru $A \sube G$ podgrupa generowana przez $A$, oznaczana jako $<A>$, to najmniejsza podgrupa $G$ zawierajaca $A$. W takim wypadku mówimy, że $A$ to zbiór generatorów tej podgrupy 

Aby znaleźć odwrotność złożonego iloczynu sprzężonych elementów trzeba:
1. odwrócić kolejność elementów w iloczynie
2. wziąć odwrotność każdego z elementów i ponownie je sprzęgnąć w odpowieniej kolejności 

$$
(x_1^{z_1} \cdot x_2^{z_2} \dots x_k^{z_k})^{-1} = (x_k^{-1})^{z_k} \cdot (x_{k - 1}^{-1})^{z_{k - 1}} \cdots (x_1^{-1})^{z_1}
$$

Niech $a_1, \dots, a_k \in G$. O iloczynie $a_1^{\ell_1} \cdot a_2^{\ell_2} \dots a_k^{\ell_k}$ mówimy że jest w **postaci zredukowanej**, jeśli $a_i \notin \{a_{i + 1}^{-1}, a_{i+1} \}$ dla każdego $i$ oraz $\ell_i \neq 0$ dla każdego $i$
Definicja mówi o tym, jak należy uporządkować elementy i ich potęgi w produkcie grupowym, aby wynikowa forma była "zredukowana", czyli nie zawierała zbędnych (redundantnych) elementów.Postać ta jest osiągana, gdy w iloczynie nie występują obok siebie elementy i ich odwrotności

Dk=la zbioru generatorów $X$ podgrupa $<X>$ to dokładnie zbiór elementów postaci: 
$$
<X> = \{x_1^{z_1} \cdot x_2^{z_2} \dots x_k^{z_k} : k \geq 0, x_1, \dots, x_k \in X, z_1, \dots, z_k \in \Z \}
$$

### Grupa cykliczna 
Grupa $G$ jest grupą cykliczną, gdy $G = <\{a\}>$ dla pewnego $a \in G$, czyli grupa jest generowana przez jeden element 

Każda grupa cylkiczna jest przemienna 

Dla każdego $n < \infty$ wszystkie grupy cyliczne rzędu $n$ są izomorficzne $(z \ (\Z_n, +))$
Wszystkie grupy cykliczne nieskończonego rzędu są izomorficzne $(z \ (\Z, +))$
(to w nawiasie to doprecyzowanie) 

Podgrupa grupy cylkicznej jest cykliczna

### grupa wolna 
Niech $\varGamma^{-1} = \{a^{-1} : a \in \varGamma \}$ będzie rozłączne z $\varGamma$
Grupa $G$ o zbiorze generatorów $\varGamma$ jest wolna (wonie generowana przez $\varGamma$) jeśli dla dowolnego słowa $w \in (\varGamma \cup \varGamma^{-1})^*$ w postaci zredukowanej zachodzi 
$$
w =_G e \implies w = \epsilon
$$
w tym $w = _G e$ znaczek $=_G$ odnosi się do równości w grupie G. więc czytasz to tak: jeśli słoso w jest równe elementowi neutralnemu to w jest pustym słowem 

Grupa wolna to grupa, w której każdy element jest unikalnym zredukowanym słowem złożonym z generatorów i ich odwrotności. W grupie wolnej nie ma innych relacji poza tymi, które wynikają z definicji odwrotności. Jeśli jakieś słowo w grupie wolnej jest równe elementowi neutralnemu, to to słowo musi być puste $\epsilon$ (czyli nie zawiera żadnych elementów)


$nf(w)$ oznacza postać zredukowaną $w$

**Domknięcie Kleene'ego** zbioru \( S \), oznaczone jako \( S^* \), to zbiór wszystkich możliwych ciągów (słów) utworzonych z elementów zbioru \( S \), w tym pusty ciąg. Matematycznie wyraża się to jako:
\[
S^* = \{ \epsilon \} \cup S \cup S^2 \cup S^3 \cup \dots
\]
gdzie \( \epsilon \) oznacza pusty ciąg.

Niech $\sum$ to zbiór różnych elementów (liter), $\sum^{-1} = \{a^{-1} : a \in \sum \}$ będzie rołączny z $\sum$. Rozpatrzmy zbiór $nf((\sum \cup \sum^{-1})^*)$ wszystkich słów zredukowanych z $(\sum \cup \sum^{-1})^*$. Mnożenie elementów $u \cdot w$ to postać zredukowana $nf(uw)$ słowa uw:
* tak zdefiniowana grupa jest grupą wolną (o generatorach $\sum$)
* każda grupa wolna jest izomorficzna z tak skonstuowaną grupą wonną 

kazda podgrupa grupy wolnej jest wolna 

### Skrócona Definicja

Niech \( w_1, \dots, w_\ell \) będą słowami w postaci zredukowanej nad alfabetem \( (\Sigma \cup \Sigma^{-1})^* \). 
Jeśli słowo \( w_1^{\ell_1} w_2^{\ell_2} \dots w_n^{\ell_n} \) w postaci zredukowanej równa się elementowi neutralnemu \( e \), 
to istnieją słowa \( u, v, w \) w zbiorze \( \{w_1, w_1^{-1}, \dots, w_\ell, w_\ell^{-1}\} \), takie że w słowie \( uvw \) 
całe \( v \) może zostać zredukowane (tj. istnieje ciąg skróceń, który usuwa całe \( v \)).

Lemat mówi, że jeśli pewne słowo w grupie wolnej redukuje się do elementu neutralnego, to można znaleźć 
takie podciągi (słowa \( u, v, w \)), które przy odpowiednim uporządkowaniu i redukcji prowadzą do całkowitego 
usunięcia jednego z tych podciągów (\( v \)). To oznacza, że nawet w złożonych słowach w grupach  
można wykryć i usunąć całe części słowa dzięki odpowiednim właściwościom redukcji.

---

# Rozdział 15

---

Grupa permutacji $S_n$ to zbiór wszystkich bijekcji ze zbioru $\{ 1, 2, \dots, n \}$ w siebie. operacją jest składanie funkcji. Dla dwóch permutacji $\sigma, \sigma'$ ich złożenie $\sigma \cdot \sigma'$ daje nową permutacje 

$$
(\sigma' \cdot \sigma)(i) = \sigma'(\sigma(i))
$$

przykład:

$$
\begin{pmatrix}
1 & 2 & 3 & 4 \\
2 & 3 & 1 & 4
\end{pmatrix}
\cdot
\begin{pmatrix}
1 & 2 & 3 & 4 \\
3 & 1 & 4 & 2
\end{pmatrix} =
\begin{pmatrix}
1 & 2 & 3 & 4 \\
1 & 2 & 4 & 3
\end{pmatrix}
$$

Permutacje zapisujemy:
$$
\begin{pmatrix}
1 & 2 & \dots & n \\
\sigma(1) & \sigma(2) & \dots & \sigma(n)
\end{pmatrix}
$$

Dla każdej grupy $G$ (o n elementach) istnieje podgrupa $S_n$ izomorficzna z $G$

### Cykl
cykl $\sigma$ to taka permutacja, że istnieja elementy $a_1, \dots, a_n, \ że \ \sigma(a_i) = a_{i +1}$ (gdzie $sigma(a_n) = a_1$), a na innych elementach jest identyczność. Cykl taki zapisujemy jako $(a_1, \dots, a_n)$. Elementy $\{a_1, \dots, a_n \}$ to dziedzina cyklu lub nośnik cyklu.

**Długość cyklu** $\{a_1, \dots, a_n \}$ to n 

**Cykle są rozłączne**, gdy operują na zupełnie różnych zbiorach elementów, czyli ich nośniki (zbiory elementów, które są przestawiane przez cykl) nie mają żadnych wspólnych elementów. W praktyce oznacza to, że te cykle można wykonywać niezależnie od siebie, a ich wynik będzie taki sam niezależnie od kolejności ich wykonania.

##### Transpozycja 
jest to cykl dwuelementowy

własności 
1. Rząd cyklu długości $k$ to $k$
2. Dla cyklu $(a_1, \dots, a_n)$ permutacja odwrotna to $(a_1, 
\dots, a_n)^{-1} = (a_n, a_{n-1}, \dots, a_1) = (a_1, \dots, a_n)^{n - 1}$
3. Jeśli masz zbiór cykli $\{ c_i \} _{i = 1} ^ k$ które są parami rozłączne, to wynikowa permutacja, którą otrzymasz, mnożąc te cykle w dowolnej kolejności, będzi zawsze taka sama, niezaleśnie od kolejności, w jakiej te cykle pomnożysz 
4. Jeśli masz zbiór cykli $\{ c_i \} _{i = 1} ^ k$ które są parami rozłączne, to **rząd** $c_1 \cdot \cdot \cdot c_k$ to nww rzedów poszczególnych cykli $c_1, \dots, c_k$ 
5. Jeśli $\sigma = c_1 c_2 \dots c_k$ gdzie $c_1, \dots, c_k$ są rozłącznymi cyklami, to $\sigma^{-1} = c_1^{-1} c_2^{-1} \dots c_k^{-1}$

więcej właśności: 
1. Każda permutacja $\sigma$ jednoznacznie (z dokładnościądo kolejności cykli) rozklada się na rozłączne cykle. Po ludzku: każdą permutacje można przedstawić jako zbiór rozłącznych cykli 
2. Cykl długości $k$ jest złożeniem $k - 1$ transpozycji 
3. każda transpozycja jest złożeniem nieparzystej liczby transpozycji elementów sąsiednich. po ludzku: dowolną zamianę dwóch elementów można osiągnąć za pomocą nieparzystej serii kroków, które zamieniają tylko sąsiednie elementy miejscami. Np. $(1, 3) = (2,3) \cdot (1, 2) \cdot (3, 2)$
4. każdą permutacje da się przedstawić jako złożenie transpozycji (niekoniecznie rozłącznych) 
5. każdą permutacje da się przedstawić jako złożenie transpozycji sąsiednich (niekoniecznie rozłącznych)
6. Grupa $S_n$ jest generowana przez zbiór transpozycji (sąsiednich) 

### Permutacje parzyste i nieparzyste 

Dla funkcji $f$ będącej bijekcją z podzbioru liczba naturalnych w ten sam zbiór (czyli w szczególności permutacji) **inwersja** to para $(i, j)$ taka że $i < j \ oraz \ f(i) > f(j)$ 

**parzystość permutacji** to parzystość ilosci jej inwersji 
**znak $sgn(\sigma)$** permutacji $\sigma$ to $+1$, gdy $\sigma$ jest parzysta i $-1$ gdy nieparyzsta

Niech $\sigma, \sigma' \in S_n$ będą permutacjami. Wtedy
$$
sgn(\sigma' \sigma) = sgn(\sigma')sgn(\sigma) 
$$

własności
* cykl parzysty jest permutacją nieparzysta 
* cykl nieparzysty jest permutacją parzystą 

wyjaśnienie: 
    permutacja jest parzysta jeśli można ja zapisać jako złożenie pazystej liczby transpozycji, permutaja jest nieparzysta jeśli można ją zapisać jano słożenie nieparystej liczby transpozycji. Cykl długości $k$ to permutajc która przedstawią $k$ elementów, cykl długości $k$ można zapisać jako złożenie $k - 1$ transpozycji 

więcej własności:
* permutaja jest parzysta wtedy, gdy liczba prarzystych cykli w jej rozkłądzie jest parzysta 
* permutaja jest nieparzysta wtedy, gdy liczba parzystych cykli w jej rozkłądzie jest nieparzysta 
* Permutacje parzyste stanowia podgrupę $S_n$ która ma ${n! \over 2} $ permutacji 

przykłady:
$\sigma = (1, 2)(3, 4)(5)(6, 7, 8)$
mamy dwa cykle parzyste: $(1, 2) \ i \ (3,4)$
mamy jeden cykl nieparysty: $(6, 7, 8)$
ilość cykli parzystych jest parzysta więc permutacja $\sigma$ jest parysta 

---

# Rozdział 16

---

### mnożenie podzbiorów grupy 
w podzbiorach grupy $G$ definiujemy dizałanie:
$$
U \cdot W = \{ uw: u \in U, w \in W \}
$$
jest ono łącznie:
$$
U \cdot (W \cdot V) = (U \cdot W) \cdot V = U \cdot W \cdot V
$$

rozdzielność mnożenia wzgledem sumy:
$$
U(V \cup W) = UV \cup UW  \\
(V \cup W) U = VU \cup WU
$$

Niech $G$ grupa, $H \leq G$ to jej podgrupa, wtedy:
$$
gG = Gg = G \\ 
gH = H \iff Hg = H \iff g \in H 
$$

### działania grupy na zbiorze
dla:
    $C$ zbioru obiektór kombinatorycznych 
    $S$ grupy permutacji elementów S(C): zbioru wszystkich możliwych przekształceń (permutacji) elementów zbioru C 
    $G$ grupy (tutaj definiujemy G jako grupe przekształceń)
Działanie grupy $G$ na $C$ to homomorfizm z $G$ w $S$. Zapisujemy to jako $g(c)$ lub $gc$. Działanie to można rozszeżyć na podzbiory G: jeśli $G$ działa na $C$ to dla $U \sube G$:
$$
Uc = \{ gc : g \in U \} 
$$

**Orbita** elementu $c : Gc \{g(c) : g \in G \}$ oznaczamy jako **$O_c$**. Orbita podazuje , w jakie różne elementy może przeksztaćić się $c$ pod działaniem grupy $G$
**Stabilizator** elementu $c : \{g \in G : g(c) = c\}$, oznaczamy jako **$G_c$**. Stabilizator to zbiór elementów grupy $G$, które nie zmieniają elementu $c$

Niech $G$ działa na zbiorze $C$ zaś $s \in C$ Wtedy stabilizator $G_s$ jest podgrupą $G$

Niech $G$ działa na zbiorze $C$ zaś $c, c' \in C$ wtedy $O_c, O_{c'}$ są równe lub rozłączne.

Niech $G$ dział na zbiorze $C$, i $c \in C$ wtedy $|O_c| \cdot |G_c| = |G|$

### Lemat Burnside'a 
Zliczanie orbit działania grupy odpowiada zliczaniu 'nierozróżnialnych' względem działaniu grupy obiktó, np. kostek nierozróżnialnych ze względu na obrót.

Dla grupy $G$ działającej na zbiorze $C$ mówimy, ze $c \in C$ jest punktem stałym $g \in G$ jeśli $g(c) = c$ 
$$
fix(g) = \{c \in C : g(c) = c \}
$$

stabilizator vs punkt stały: 
| punkt stały | stabilizator | 
| --- | --- |
| to zbiór elementów C które są niezmieniane przez dane g | to zbiór elementów G które nie zmieniają danego c |
| $fix(g) = \{c \in C : g(c) = c \}$ | $ G_s = \{g \in G : g(c) = c\}$

Niech $G$ działa na zbiorze $C$ a $O$ bęzie zbiorem orbit tego działania, wtedy:
$$
|O| = {1 \over |G|} \sum _ {g \in G} |fix(g)|
$$

---

# Rozdział 17

---

### Warstwy 
Niech $H \leq G$ będzie podgrupą. Definiujemy naturalne działanie $h \in H$ na $G$ :
$$
h(g) = hg
$$

**warstwa prawostronna** $Hg$:
* zbiór $Hg = \{hg : h \in H \}$
* orbiat elementu g to warstwa prawostonna $Hg$ dla działania $h(g) = hg$

**warstwa lewostonna** $gH$:
* zbiór $gH = \{gh : h \in H \} $
* orbita elementu g to warstwa lewostronna $gH$ dla działania $h(g) = gh^{-1}$
* zbiór warst wewostronnych $H$ w $G$ oznaczamy przez $G/H$

Niech $H \leq G$ :
* każde dwie warstwy H w G są równoliczne 
* każde dwie warstwy lewostonne (prawostronne) $H$ w $G$ są rozłączne lub identyczne 

Niech $H \leq G$:
$$
g_0H = g_1H \iff g_1^{-1}g_0 \in H \iff g_0^{-1}g_1 \in H \\
Hg_0 = Hg_1 \iff g_1g_0^{-1} \in H \iff g_0g_1^{-1} \in H
$$

##### kilka wniosków dla grupy skończonej 
* (twierdzenie Lengange'a) rząd podgrupy dzieli rząd grupy: dla grupy $G$ i podgrupy $H \leq G$: $|H| \  | \ |G|$
* Rząd elementu dzieli rząd grupy 
* każda grupa o p-pierwszym elementach jest cylkiczna i każdy jej element (poza e) jest generatorem: jeśli rząd grupy G jest liczbą pierwszą to G jest grupą cylkiczną 
* dla każdego $a$ zachodzi $a^{|G|} = e$

##### małe twierdzenie fermata
Jeśli $p$ jest liczbą pierwszą oraz $a$ liczbącałkowitą, która nie jest podzielna przez $p$ to
$$
a^{p - 1}  \ mod  \ p = 1
$$

##### Indeks podgrupy
Indeks podgrupy $H$ względem grupy $G$ to ilosć warstw lewostronnych $H$ w $G$, oznaczamy przez $G : H$. Indeks podgrupy $G : H$ mówi nam na ile róznych kawałków możemy podzielić grupę $G$ przy pomocy podgrypy $H$
przykłąd jeśli mamy grupę $G$ o 12 elementach i podgrupę $H$ o 3 elementach, to indeks $G : H$ wynosic 4, bo $12 / 3 = 4$. Oznacza to że $G$ dzieli się na 4 różne warsty lewostronne pod wzgledem podgrypy $H$ 

--- 

# Rozdział 18

---

### Homomorfizmy 
dla homomorfizmu $\varphi : G \rightarrow H$ jego:
**obraz** to $Im \, \varphi = \{ \varphi(g) : g \in G \} = \varphi(G)$
**jądro** to $ker \, \varphi = \{g : \varphi(g) = e \} = \varphi^{-1}(e)$

Dla homomorfizmu $\varphi : G \rightarrow H$ jego:
jądro to podgrupa G
obraz to podgrupa H 

### podgrupa normalna 
$H$ jes podgrupą normalną $G$, gdy $gH = Hg$ dla każdego elementu $g \in G$, zapisujemy to jako $H \trianglelefteq G$

Następujące warunki są równoważne dla podgrupy normalnej H:
1. $aH = Ha$ dla każdego elementu $a$ 
2. $aHa^{-1} = H$ dla każdego elemetnu a 

### podgrupa sprzężona 
Dla $H \leq G$ podgrupa postaci $gHg^{-1}$ to podgrupa sprzężona do H 

Podgrupy sprzężone są izomorficzne. W ogólności dla $g \in G$ przekształcenie $h \rightarrow gxg^{1}$ jest izomorfizmem grupy z samą sobą (może to być identyczność) 

Jeśli $\varphi : G \rightarrow H$ jest homomorfizmem, to $ ker \, \varphi$ jest podgrupą normalną 

### Działanie na warstwach 
Gdy $H$ jest podgrupą normalną $G$, to zbiór warstw $H$ w $G$, czyli $G / H$ ma strukturę grupy dla działania
$$
aH \cdot bH = abH
$$
Grupę tą nazywamy **grupą ilorazową**

Grupa ilorazowa jest grupą 

### Naturalny homomorfizm 
Niech $H \trianglelefteq G$ będzie podgrupą normalną $G$, wtedy naturalny rzut z $G$ na warsty $G$ to $\pi_H : G \rightarrow G / H$, gdzie $\pi_H(g) = gH$ jest homomorfizmem, co więcej $H = ker \, \pi_H$

Niech $\varphi : G \rightarrow G'$ będzie homomorfizmem. Wtedy istnieje izomorfizm $\psi: G / ker \, \varphi \rightarrow Im \, \varphi$
to twierdzenie mówi, że każdą grupę $G$ możemy 'skompresować' poprzez jej jądro, a następnie odzworować ję 'skompresowaną' wersję w obraz $G'$ przy poocy izomorfizmu 

### Kongruencje
Relacja $\equiv \sube G^2$na grupie $G$ jest **kongruencją**, jeśli:
* jest relacją równowazności 
* zachowuje działania, tzn. dla każdych $a, a', b, b' \in G$:
$$
a \equiv b \land a' \equiv b' \implies aa' \equiv bb' \\
a \equiv b \implies a^{-1} \equiv b^{-1}
$$

---

# Rozdział 19

---

### Pierścienie 
Pierścień oznaczany zwykle przez $R$ to zbiór z dwoam działąniami $+,\cdot$ spełniającymi warunki:
* $(R, \cdot)$ jest półgrupą (niekoniecznie przemienną)
* $(R, +)$ jest grupą przemienna 
ponadto zachodzi rozdzielność mnożenia wzdględem dodawania:
* $a(b + c) = ab + ac, (b + c)a = ba + ca$

pierścień jest z jednością, jeśli ma element neutralny dl amnożenia
pierścień jest przemienny, jeśli $ab = ba$ 

Ciało $\mathbb{F}$ to pierścień premienny z jednością w którym $(\mathbb{F}, \cdot)$ jest grupą tzn. kazdy element ma element odwrotny, roaz elementy neutralne dodawania i mnożenia są różne $('0 \neq 1')$

przykłady pierścieni:
* liczby całkowite $\Z$ 
* $\Z_m$
* $R[x]$ wielomiany o współczynnikach z $R$ 

$\Z_m \ jest \ ciałem \iff m \ jest \ pierwsze$

### Arytmetyka modularna
$a$ przystaje do $b$ modulo $m$ gdy $m | (a - b)$ oznaczenie:
$$
a \equiv_m b
$$

reszta z dzielenia przez $m$: 
$$
a \mod m = b \iff a \equiv_m b \land b \in \{0, 1, \dots, m - 1 \}
$$

Relacja $\equiv \sube R^2$ na pierścieniu $G$ jest kongruencją jeśli:
* jest relacją równowazności
* zachowuje działania, tzn. dla każdych $a, a', b, b' \in G$:
$$
a \equiv b \land a' \equiv b' \implies aa' \equiv bb' \\
a \equiv b \implies a^{-1} \equiv b^{-1}
$$

Dla dowolnego $m \in \Z_+$ relacja $\equiv_m$ jest kongruencją 

### Formuła pozytywna
Niech $t_1, t_2$ będą wyrażeniami zbudowanymi z nawiasó, zmiennych $x_1, x_2, \dots, x_n$, elementów z $A$ oraz działań $+, \cdot$. Wtedy formuła $\psi$ składające się ze spójników $\land, \lor$oraz równości $t_1 = t_2$, nazywamy **formułą pozytywną**. Czyli są to formuły logiczne w których może występować porównanie dwuch elementów $(=)$, ale nie może występować negacja

Niech $\psi$ będzie formułą pozytywną, zaś $\varphi : A \rightarrow B$ będie homomorfizmem na pierścień $B$. Jeśli:
$$
Q_1x_1Q_2x_2\dots Q_nx_n \ \psi (x_1, x_2, \dots, x_n)
$$

zachodzi w $A$ to w $B$ zachodzi:
$$
Q_1x_1Q_2x_2\dots Q_nx_n \ \psi' (x_1, x_2, \dots, x_n)
$$
gdzie $\psi'$ jest uzyskane z $\psi$ przez zmianę stałych $c$ w wyrażeniach przez $\varphi(c)$ zaś $Q_i$ jest kwantyfikatorem (uniwersalnym lub egzystencjonalnym)
Po ludzku: jeśli mamy pewne własności, które są wyrażone w formie formuły pozytywnej w pierściuniu $A$, to te same własności będą prawdziwe w pierściueniu $B$ po przekształceniu odpowiednich wyrażeń za pomocą homomofrizmu $\varphi$

### Algorytm eukidesa 
Liczba $0 \neq k \in \N$ jest **NWD** $a, b \in \Z$ jeśli $k | a, k |b$ i dla każdego $l$ zachodzi $l | a, l | b \implies l | k$

Niech $k \neq 0; \, ab,k \in \Z$ wtedy:
$$
Jeśli \ k| a \ i \ k | b \ to \ k |(a + b) \ i \ k|(a - b) \\
Jeśli \ k | a \ i \  k|b \ to \ k | (a \ mod \ b) \\
Jeśli \ k | (a \ mod \ b) \ i \ k | b \ to \ k | a 
$$

Algorytm Eukidesa zwraca NWD

W czasie działąnia algorytmu Euklidesa możemy przechowywane liczby reprezentować jako kombinacje liniowe (o współczynnikach całkowitych) a oraz b.

Dla $a, b \in \Z_+$ istnieją $x, y \ \in \Z$ takie że: 
$$
nwd(a, b) = xa + by
$$

W pierścieniu $\Z_m$ element $a$ ma element odwrotny $\iff nwd(a, m) = 1$ (czyli a i m są współpierwsze) 

### Elementy odwracalne
Element $a$ pierścienia $R$ nazywamy odwracalnym, jeśli istnieje $b \in R$ takie że $ab = 1$ 

Zbiór elementów odrwacalnych pierścienia $R$ oznaczamy jako $R^*$

Dla dowolnego pierrścienie $R$ z jednoścą zbiór elementów odwracalnych $R^*$ jest grupą na mnożenie, co oznacza, że elementy te mogą być mnożone ze sobą, a wynik również będzie odwracalny, istnieje element neutralny (1), oraz każdy element ma swój odwrotny, który pomnożony przez niego daje 1

Dla ciała skończonego $\mathbb{F}$ grupa $\mathbb{F}^*$ jest cykliczna

**symbol eulera** $\varphi(m)$ to liczba liczb względnie pierwszych z $m$ mniejszych od $m$ 

**twierdzenie eulera**  Niech $a,m$ są względnie pierwsze. Wtedy:
$$
a^{\varphi(m)} = 1 \mod m
$$

Jeśli $n, m$ są względnie pierwsze, to $\varphi(nm) = \varphi(n) \cdot \varphi(m)$

Jeśli $p$ jest pierwsze, $k > 0$ naturalne, to 
$$
\varphi(p^k) = (p - 1) p^{k - 1} = {p -1 \over p} p^k
$$

### Chińskie twierdzenie o resztach 
**Produkt pierścieni** definiujemy standardowo: dla pierścieni $R, R'$ ich produkt $R \times R'$ ma jako zbiór  iloczyn kartezjański zbiorów $R, R'$

własności:
* $R \times R$ i $ R' \times R$ są izomorficzne
* produkt kartezjański jest łączny: $R_1 \times (R_2 \times R_3)$ i $(R_1 \times R_2) \times R_3$ są izomorficzne
* Jeśli $R_1$ jest izomorficzne z $R_1'$, a $R_2$ jest izomorficzne z $R_2'$ to $R_1 \times R_2$ jest izomorficzne z $R_1' \times R_2'$


### Algorytm szyfrowania Rabina 

Grupa $\Z_p^*$ jest cykliczna 

Jeśli $p$ jest liczbąpierwszą, to $a^2 \equiv_q b^2$ wtedy i tylko wtedy gdy $a \equiv_p b$ lub $a \equiv _p -b$

Jeśli $p$ jest pierwsza w $\Z_p^*$ jeśli $a$ jest kwadratem, to $a^{(p - 1) / 2} = 1$ w przeciwnym przypadku $a^{(p - 1) / 2} = -1$

---

# Rozdział 20

---

### Pierścień wilelominów 
wielomian $f$ to ciąg $(a_0, \dots, a_n)$, myślimy o nich jako o $
\sum  a_ix^i$. 

Zbiór wielomianów o współczynnikach z pierścienia $R$ oraz naturalnym dodawaniem i mnożeniem to pierścień wielomianów $R[x]$. Zerem w tym pierścieniu jest wielomian 0. 

Liczby $a_0, \dots, a_n$ to współczynniki wielomianu, jesli $a_n \neq 0 $ to jest on współczynnikiem wiodącym
Stopień wielomianu $deg(a_0, \dots, a_n)$ dla $a_n \neq 0$ to n. W przypadku wielomianu zerowego stopień to $-\infty$

$R[x]$ z mnożeniem zdefiniowanym jako splot jest pierścieniem. Jeśli $R$ jest pierścieniem przeniemmym (z jednością), to $R[x]$ też jest pierścieniem przemiennym (z jednością) 

Jeśli myślimy o wielomianach jak o ciagach, to operację mnożenia nazywamy spletem dwóch ciągów (i często oznaczamy przez *)

Niech $f, g \in R[x]$ wtedy: 
$$
deg(f + g) \leq max(deg(f), deg(g)) \\ 
deg(f \cdot g) \leq deg(f) + deg(g) 
$$

### ewaluacja (wartościowanie) wielominów 
Wielomain $f \in R[x]$ równy $(a_0, \dots, a_n)$ możemy też potraktować jako funkcje z $R$ w $R$

Niech $f, g \in R[x]$ i $p \in R$ Wtedy:
$$
(f + g)(p) = f(p) + g(p)
$$
jeśli $R$ jest przemienny to dodatkowo:
$$
(fg)(p) = f(p) \cdot g(p)
$$

### dzieleni, podzielność i new wielomianów 
Niech $\mathbb{F}$ będzie ciałem a $\mathbb{F}[x]$ pierścieniem wielomianów o współczynnikach z $\mathbb{F}$. Dla wielomianów $f, g$ z tego pierścienia o stopniach $deg(f) = m$ oraz $deg(g) = n \neq -\infty$ istnieje dokładnie jedna para wielomianów $q,r$ taka że $f = gq + r$, gdzie $deg(r) < deg(g)$ 

Wielomian $f$ jest podzielny przez wielomain $g$ jeśli reszta z dzielenia $f$ przez $g$ wykosi 0: zapisujemy $f | g$

$f | g \iff istnieje \ wielomian \ q \ taki \ że \ g = fq$

Każdy wielomian dzieli 0 

Wielomian $f \in R[x]$ jest nierozkłądalny w $R[x]$, jeśli $deg(f) > 0$ i nie istnieją wielomiany $g, h \in R[x]$ takie że $f = gh$ oraz $deg(x), deg(h) < deg(f)$

nwd wielomianów $f i g$ to taki wielomian $h$ że $h|f, h|g$ oraz jeśli $h'|f, h'|g \implies h' | h$

każde dwa wielomiany $p, q \in \mathbb{F}[x]$ mająnwd. Jest on postaci $ap + bq$ dla pewnych wielomianów $a, b \in \mathbb{F}[x]$

Niech $f, f', g, g', h, a, b \in \mathbb{F}[x]$ jeśli $f = f'h, g = g'h$ to:
$$
nwd(f, g) = h \, nwd(f', g') 
$$


Jeśli $f$ jest nierozkładalny oraz $f | p_1p_2 \dots p_n$ to $f | p_i$ dla pewnego i 

**Bezut** Jeśli $\mathbb{F}$ jest ciałem, $\mathbb{F}[x]$ pierwśeniem weilomianów o współczynnikach z tego ciałą zas $f, \, (x - c) \in \mathbb{F}[x]$ wielomianami z tego pierścienia, to reszta z dzielenia $f$ przez $(x - c) to $f(c)
W szczególności $(x - c) | f \iff f(c) = 0$

c nazywamy **pierwiastkiem** (rozwiązaniem) wielomianu $f$, gdy $(x - c) | f$ . c jest pierwiastkiem k-krotnym, dla $k \geq 1$ gdy $ (x - c)^k | f$ 

wielomian $0 \neq f \in \mathbb{F}[x]$ ma najwyzej deg(f) różnych pierwiastków 