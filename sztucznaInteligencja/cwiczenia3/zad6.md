# zad6

---

Czyli dostajemy na początku dostajemy listę list [id_zajec, id_klasy]

1. teraz do każdej listy trzeba przydzielić id_goziny w ktorej odbędą się zajęcia z przedziału [1,50]

```prolog
    assign_time(Poczatkowa_lista_zajec, Zajecia) :-
        maplist(assign_id_godziny, Poczatkowa_lista_zajec, Zajecia)
    
    assign_id_godziny([IdZajec, IdKlasy], [IdZajec, IdKlasy, IdGodziny]) :-
        IdGodziny ins 1..50.
       
        
```

2. wszystkie te liczby mają być różne 
```prolog
% najpierw funkcja która zwróci liste samych id_godziny
get_id_godziny([_, _, X], Id_godziny) :-
    Id_godziny = X.

get_ids_godziny(Zajecia, ids_godziny) :-
    maplist(get_id_godziny, Zajecia, ids).

all_distinct(ids_godziny)
```

3. sprawdzanie okieniek
najpierw trzeba napisać funkcje ktora zamienia następujące po sobie wystąpienia liczby w liście na jedną wartość np. [1,1,1,2,3,2] -> [1,2,3,2]

``` prolog
%zakładam że nie dostane pustej listy
head([H|T], Result) :-
    Result = H

filtr_rep(List, Result) :-
    head(List, H), 
    firlt_rep_rec(List, H, Acc, Result).
% wynik bedzie w odwróconej kolejności ale to nie ma znaczenia

filtr_rep_rec([H|T], last, Acc, Result) :-
    (H == last -> 
        filtr_rep_rec(T, H, Acc, Result);
        filtr_rep_rec(T, H, [last | Acc], Result)
    ).

filtr_rep_rec([], last, Acc, Result) :-
    Result = [last | Acc].
```

trzeba dodać funkcje która która tworzy plan lekcji
```prolog
make_timetable(Zajecia, timetable) :-
    matrix = [make_list(1, 10), make_list(11, 20), make_list(21, 30), make_list(31, 40), make_list(41, 50)]
    set_time(Zajecia, timetable)

set_time([[IdZajec, IdKlasy, IdGodziny]|T], timetable) :-
    replace_nth(idGodziny, IdKlasy, timetable) %funkcja ktora zmiena itą wartośc na liście na IdKlasy
    set_time(T, new_timetable).

%teraz rozbiore plan lekcji na poszczególne dni tygodnia
get(1, 10, timetable, pon)
get(11, 20, timetable, wt)
...

get(x, y, timetable day) :-
    get_rec(x, y, i, timetable, acc, dayrev),
    day = reverselist(dayrev).

get_rec(x, y, i, [H|T], acc, day) :-
    (x =< i , i =< y ->
        get_rec(x, y, i + 1, T, [H|acc], day);
        get_rec(x, y, i + 1, T, acc, day)
    ).

get_rec(x, y, i, [], acc, day) :-
    day = acc.
```

teraz gdy już mam funkcje filtr_rep można dodać ograniczenie mówiące że wszystkie wartości na liście mszą być różne
```prolog
    filtr_rep(pon, filteredPon)
    all_different(filteredPon)
    % itd dla każdego dnia tygodnia
```