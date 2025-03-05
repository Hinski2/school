# rozszeżony algorytm euklidesa 

---

Zwykły algorytm euklidesa znajduje tylko GCD(a, b), podczas gdy rozszezony znajduje sposób na zapisanie $a \cdot x + b \cdot y = gcd(a, b)$

Gdy puścimy $gcd(a, b) = g$ to na koniec zostaniemy z $b = 0$ i $a = g$, wtedy możemy znaleźć łatwo współczynniki $g\cdot1 + 0 \cdot 0 = g$

startując ze współczynników $(x, y) = (1, 0)$ możemy cofnąć się rekurencyjnie w wywołąniach. to co musimy sprawdzić to jak wsþłczynniki $x$ i $y$ zmienają się podczas przejścia $(a, b) \implies (b, a \ mod \ b)$

załużmy że mamy współczynniki $(x_1, y_1)$ dla $(b, a \ mod \ b)$ t.ż:
$$
b \cdot x_1 + (a \ mod \ b) \cdot y_1 = g
$$ 

i chcemy znaleźć pare $(x_2, y_2)$ dla $(a, b)$:
$$
a \cdot x_2 + b \cdot y_2 = g
$$

z def modulo mamy $ a \mod b = a - \lfloor \frac{a}{b} \rfloor \cdot b$ podstawiamy i mamy:
$$
g = b \cdot x_1 + (a \mod b) \cdot y_1 = b \cdot x_1 + (a - \lfloor \frac{a}{b} \rfloor \cdot b) \cdot y_1
$$

po poprzestawianu otrzymujemy:
$$
g = a \cdot y_1 + b \cdot (x_1 - y_1 \cdot \lfloor \frac{a}{b} \rfloor) \\
(x_2, y_2) = (y_1, x_1 - y_1 \cdot \lfloor \frac{a}{b} \rfloor)
$$


---

gdy już mamy: $ax + by = g$ t.ż. wszytkie te liczby są całkotite, to możemy znaleźć więcej takich współczynników x i y dla których ax + by jest liczba całkowitą 

weźmy takie $c$ że $g | c$, wtedy mamy:
$$
ax + by = g \\
a(x\frac{c}{g}) + b(y \frac{c}{g}) = c
$$

#### wyznaczanie wszystkich rozwiązań:
* $ x = x_0 + \frac{b}{g} \cdot k$
* $ y = y_0 - \frac{a}{g} \cdot k$

bo doanie $\frac{b}{g}$ do $x_0$ oraz jednoczesne odjęcie $\frac{a}{g}$ od $y_0$ nie zmieni wartości 
$$
a(x_0 + \frac{b}{g} \cdot k) + b(y_0 - \frac{a}{g} \cdot k) = ax_0 + by_0 = g
$$

