
# Tutorial OCaml

Tutorial ten wprowadza do programowania w języku OCaml, który jest funkcjonalnym językiem programowania oferującym zaawansowane mechanizmy typów i funkcji. Poniżej przedstawiono kluczowe koncepty wraz z przykładami kodu.

## 1. Rekurencja i Iteracja (`sprawdzenie0.ml`)

### Rekurencyjne funkcje

Rekurencja jest fundamentalną techniką w programowaniu funkcyjnym. Poniższy przykład ilustruje definicję funkcji rekurencyjnej obliczającej silnię:

```ocaml
(* Definicja funkcji rekurencyjnej do obliczania silni *)
let rec fact n =
  if n = 0 then 1 else n * fact (n - 1);;
```

### Iteracyjne podejście

Iteracja może być realizowana za pomocą rekursji ogonowej, co pozwala kompilatorowi na optymalizację wykorzystania stosu:

```ocaml
(* Iteracyjne obliczanie silni za pomocą rekursji ogonowej *)
let fact_iter n =
  let rec itr n acc =
    if n = 0 then acc else itr (n - 1) (acc * n)
  in itr n 1 ;;
```

## 2. Reprezentacja Danych i Dopasowanie Wzorców (`sprawdzenie1.ml`)

### Krotki

Krotki pozwalają na grupowanie różnych typów danych. Można je łatwo destrukturyzować za pomocą dopasowania wzorców:

```ocaml
(* Przykład krotki *)
let t2 = (42,  "foo");;
let t3 = 42, "foo", false;;

(* Dopasowanie wzorca do destrukturyzacji krotki *)
let a, b, c = t3;;
```

### Typ opcjonalny `option`

Typ `option` służy do obsługi wartości, które mogą być nieobecne (None) lub obecne (Some wartość):

```ocaml
(* Użycie typu opcjonalnego *)
let o = Some 3;;
let on = None;;

(* Bezpieczne dostęp do wartości typu opcjonalnego *)
print_int (Option.get o);;
```

## 3. Listy i Polimorfizm (`sprawdzenie2.ml`)

### Listy

Listy w OCaml są jedną z podstawowych struktur danych. Poniżej znajduje się przykład tworzenia listy:

```ocaml
(* Tworzenie i manipulacja listami *)
let l = 1 :: 2 :: [];; (* Lista zawierająca 1 i 2 *)
```

### Polimorfizm

OCaml pozwala na tworzenie list funkcji, co jest przykładem polimorfizmu:

```ocaml
(* Lista funkcji *)
[(+); (-)];;
```

## Podsumowanie

Ten tutorial przedstawia podstawy języka OCaml, skupiając się na rekurencji, iteracji, reprezentacji danych, dopasowaniu wzorców, listach i polimorfizmie. Przykłady kodu zapewniają praktyczne wprowadzenie do tych koncepcji, co stanowi solidne fundamenty dla dalszej nauki i eksploracji OCaml.
