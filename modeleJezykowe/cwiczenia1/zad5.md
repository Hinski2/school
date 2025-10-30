# zad 5 

---

chcemy wygenerować dokładnie jeden wyraz 

* podajemy modelowi prefiksy z pełnych słów 
* mogel robi jeden krok przewidywania i zwraca rozklad prawdopodobieńst po wszystkich tokenach
* wybieramy ten token z największym prawdopodobieństwem
* jeśli ten token to cały wyrac 
    * mamy wynik

* jeśli ten token to niepełny wyraz:
    * wybieramy k najbardziej prawdopodobnych teoenów i zaczynamy proces na nowo
    * albo wybieramy 1 najbardziej prawdopodobny token
    * generujem aż nie dostaniemy spacji(lub przecink, kropka, ...)

* który z k wybrać: 
    * ten który ma największe łączne prawdopodobieństwo ścieżki 
    * $ P(w) = P(t_1) * P(t_2 | t_1) * P(t_3| t_1, t_2) ...$
    * $ score(w) = \sum_{i = 1}^{n} log P(t_i | t_1, t_2, ... t_{i - 1})$

    * ewentualnie mozna robić $avg_score(w) = \frac{1}{n}\sum_{i = 1}^n log P(t_i)$