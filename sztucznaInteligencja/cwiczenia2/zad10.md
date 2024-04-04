# zad 10

# nie działą !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

**heurystyka różnicowa:** \[ h(n) = \max_{L \in \text{Landmarks}} (C^*(n, L) - C^*(L, \text{goal})) \]
**Optymizm**: Heurystyka jest optymistyczna, jeśli $h(n) \leq h^*(n)$, gdzie $h^*(n)$ jest rzeczywistym minimalny kosztem dotarcia z n do celu 

#### Dowód, że differential heuristic jest optymistyczna:

Aby wykazać, że \( h(n) \) jest optymistyczna, musimy pokazać, że dla każdego węzła \( n \), \( h(n) \leq h^*(n) \).

**Optymalna ścieżka przez punkt orientacyjny**: Dla każdego punktu orientacyjnego \( L \) i węzła \( n \), różnica \( C^*(n, L) - C^*(L, goal) \) reprezentuje, jak bardzo "naokoło" musimy iść, aby dostać się od \( n \) do celu przez \( L \). Jeżeli \( L \) leży na optymalnej ścieżce z \( n \) do celu, to \( C^*(n, goal) \leq C^*(n, L) + C^*(L, goal) \).

**Własność optymistyczna**: Skoro \( h(n) \) to maksimum różnic między kosztami do punktów orientacyjnych a kosztami z tych punktów do celu, możemy zapisać, że \( h(n) = \max_{L \in \text{Landmarks}} (C^*(n, L) - C^*(L, goal)) \leq C^*(n, goal) - 0 = C^*(n, goal) = h^*(n) \). Różnica \( C^*(n, L) - C^*(L, goal) \) może być ujemna, ale wtedy heurystyka przyjmuje wartość 0, co zachowuje optymizm.

**Zachowanie dolnego ograniczenia**: Niezależnie od wyboru punktu orientacyjnego \( L \), \( h(n) \) nigdy nie przekroczy \( h^*(n) \), co oznacza, że heurystyka zawsze podaje oszacowanie mniejsze lub równe rzeczywistemu minimalnemu kosztowi dotarcia do celu.
  
