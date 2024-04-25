# zad5

---

### Zasady:
* suma zamalowany pixeli w wierszu / kolumnie jest podana
* trzeba zniszczyć
    * jeden statek długości 4
    * dwa statki długości 3
    * tzy statki długości 2
    * cztery statki długości 1
* statki nie stykają się 

### Ograniczenia:
1. suma zapalonych pól w wierszu / kolumnie musi być równa podanej
```prolog
Vx0 + Vx1 + ... Vxn #= Rowx
V0y + V1y + ... Vmy #= Coly
```

2. jeśli zamaluje pole Vxy to pola na rogach Vxy muszą być niezamalowane
```prolog
%oczywiście trzeba obsłużyć wychodzenie poza tablice
V(x, y) #=> V(x - 1, y - 1) + V(x + 1, y - 1) + V(x - 1, y + 1) + V(x + 1, y + 1) #= 0
```

3. liczba statków musi być odpowiedna

```python
# daje mi liste list co najwyżej x na y, tak by statek znajdował się
# na planszy, pola puste mogą wystawać poza plansze ale wtedy ich nie
# zwracam dla tego co najwyżej x na y

def get_lists(x, y):
    res = []
    a, b = x - 2, y - 2

    for i in range(n - a):
        for j in range(m - b):
            res.append(get_list(i - 1, j - 1, x, y))
    return res

def get_list(startI, startJ, x, y):
    res = []
    for i in range(startI, startI + x + 1):
        for j in range(startJ, startJ + y + 1):
            if 0 <= i < n and 0 <= j < m:
                res.append(V(i, j))
```
```prolog
filter(Lista, No, Ans) :-
    filter_rec(Lista, No, [], Ans).

filter_rec([H|T], No, Acc, Ans) :-
    (sum(H) == No ->
        filter_rec(T, No, [H|Acc], Ans);
        filter_rec(T, No, Acc, Ans)
    ).

filter_rec([], No, Acc, Ans) :-
    Ans = Acc.


List3x3 = get_lists(3, 3), %tą liste robie w pythonie
filter_lists(List3x3, 1, single),
len(single) #= 4, %ilość elementów listy ma być równa 4

List3x4 = get_lists(3, 4),
List4x3 = get_lists(4, 3),
filter_lists(List3x4, 2, double1),
filter_lists(List4x3, 2, double2),
double1 + double2 #= 3,

List3x5 = get_lists(3, 5),
List5x3 = get_lists(5, 3),
filter_lists(List3x5, 3, triple1),
filter_lists(List5x3, 3, triple2),
triple1 + triple2 #= 2,

List3x5 = get_lists(3, 6),
List5x3 = get_lists(6, 3),
filter_lists(List3x6, 4, quad1),
filter_lists(List6x3, 4, quad2),
quad1 + quad2 #= 1,
```
