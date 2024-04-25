# zad4

---

Plan jest taki, że każde pole rozwazamy osobno jako Vx_y
1. Vx_y musi być w zakresize [0, 1]
```prolog
Vx_y ins 0 .. 1
```
2. sprawdzenie czy wiersz się zgadza

najpierw zakodujmy funkcje która dla liste booli zwraca liste intów

```prolog
% robie funkcje która zala listy booli zwraca mi liste bloków 
to_int_list(List, Blocks) :-
    to_int_list_rec(List, 0, [], BlocksRev),
    reverse(BlocksRev, Blocks). % odraca liste bloków i zapisuje ją do Blocks

% funkcja pomocnicza

% obecny element to 1 a wcześniejszy to 
to_int_list_rec([1|T], X, Acc, Blocks) :-
    to_int_list_rec(T, X + 1, Acc, Blocks).

% obecny element to 0 w wcześniejszy to 
to_int_list_rec([0|T], X, Acc, Blocks) :-
    (X > 0 ->
        to_int_list_rec(T, 0, [X | Acc], Blocks);
        to_int_list_rec(T, 0, Acc, Blocks)
    ).

% koniec, przypadek bazowy
to_int_list_rec([], X, Acc, Blocks) :-
    (X > 0 -> 
        Blocks = [X | Acc];
        Blocks = Acc
    ).
```

teraz wystarczy dodać dodatkową funcje mówiąco że Blocks = rowx
```prolog
equal_lists(L1, L2) :-
    maplist(#=, L1, L2),
    lenght(L1, Length1),
    lenght(L2, Lenght2),
    Lenght1 #= Lenght2.
```
i ostatecznie mamy:
```prolog
to_int_list([Vx_0, Vx_1, ...], Blocks),
equal_lists(Blocks,rowx)
```

3. warunek na to że kolumny są odpowiednie
```prolog
to_int_list([V0_y, V1_y, ...], Blocks),
equal_lists(Blocks, coly)
```