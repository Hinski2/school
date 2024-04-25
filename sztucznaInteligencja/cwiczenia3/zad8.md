# Zad 8
 
### Parametry funkcji heurystycznej:
1. **Liczba gęsi na planszy** (\(G\)): Jest to podstawowy parametr określający siłę strony gęsi. Im więcej gęsi na planszy, tym trudniej dla lisa znaleźć bezpieczną ścieżkę do poruszania się bez ryzyka zablokowania.
 
2. **Liczba możliwych ruchów lisa** (\(M_L\)): Parametr określający liczbę możliwych ruchów, które lis może wykonać z aktualnej pozycji. Mniejsza liczba ruchów sugeruje, że lis jest bardziej zagrożony zablokowaniem.
 
3. **Liczba gęsi w otoczeniu lisa** (\(G_O\)): Ilość gęsi bezpośrednio sąsiadujących z polem, na którym znajduje się lis. Wysoka wartość wskazuje na zwiększone ryzyko zablokowania lisa.
 
4. **Liczba gęsi, które lis może zbić w najbliższym ruchu** (\(B_G\)): Liczba gęsi, które znajdują się w zasięgu bicia przez lisa. Wysoka liczba sugeruje większe możliwości zmniejszenia siły przeciwnika.
 
### Funkcja heurystyczna:
Funkcja może przyjąć formę liniowej kombinacji ważonej tych parametrów:
\[ H = w_1 * G + w_2 * M_L + w_3 * G_O + w_4 * B_G \]
 
Gdzie:
- \( w_1, w_2, w_3, w_4 \) to wagi dla poszczególnych parametrów,
- \( w_1 \) jest wagą negatywną (mniejsza liczba gęsi na planszy jest korzystniejsza dla lisa),
- \( w_2 \) jest wagą dodatnią (więcej możliwych ruchów lisa jest korzystniejsze),
- \( w_3 \) jest wagą negatywną (więcej gęsi w bezpośrednim otoczeniu lisa zwiększa ryzyko jego zablokowania),
- \( w_4 \) jest wagą dodatnią (więcej możliwości bicia gęsi jest korzystne).
 
### Przykładowe wartości wag:
- \( w_1 = -1 \)
- \( w_2 = 2 \)
- \( w_3 = -3 \)
- \( w_4 = 4 \)
 
Wagi można dostosować w zależności od preferencji strategii, ale generalnie większe wagi przy \( w_4 \) i \( w_2 \) mogą promować agresywne dążenie do bicia gęsi i utrzymanie mobilności lisa, podczas gdy wysoka wartość \( w_3 \) akcentuje zagrożenie zablokowania lisa przez gęsi.