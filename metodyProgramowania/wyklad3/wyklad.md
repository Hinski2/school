# Wyklad 3
---

## Funkcje wyższego rzędu

1. Funkcje map i filter
2. Funkcje foldl i foldr
3. Currying i uncurrying
4. Operator łączenia w potok |>

Funkcje wyższego rzędu to funkcje, które mogą przyjmować inne funkcje jako argumenty lub zwracać funkcje jako swoje wyniki. Pozwalają one na abstrakcję operacji, umożliwiając bardziej zwięzłe i ekspresyjne programowanie.

### Funkcja map
Funkcja map jest jednym z najbardziej fundamentalnych narzędzi w programowaniu funkcyjnym, służąc do transformacji list poprzez aplikację podanej funkcji do każdego z elementów listy. Ta operacja nie modyfikuje oryginalnej listy, lecz tworzy nową listę z wynikami.

```ocaml
let rec map f = function
  | [] -> []
  | x :: xs' -> f x :: map f xs'
```
Gdzie f to funkcja, którą chcemy zastosować do każdego elementu listy, a x :: xs' oznacza dekonstrukcję listy na głowę (x) i ogon (xs').

**Przykład** zwiększanie każdego elementu listy o 1:

```ocaml
map (fun x -> x + 1) [1; 2; 3];  (* Wynik: [2; 3; 4] *)
```
### Funkcja filter

Funkcja filter służy do wybierania z listy tych elementów, które spełniają określony warunek (predykat).

```ocaml
let rec filter pred = function
  | [] -> []
  | x :: xs' -> if pred x then x :: filter pred xs' else filter pred xs'
```
**Przyklad** Wybranie z listy tylko liczb parzystych:
```ocaml
filter (fun x -> x mod 2 = 0) [1; 2; 3; 4; 5];  (* Wynik: [2; 4] *)
```
### Funkcje foldl i foldr
Funkcje foldl (złożenie lewostronne) i foldr (złożenie prawostronne) redukują listę do jednej wartości, akumulując wynik za pomocą podanej funkcji.

**Definicja foldl**: 
```
let rec foldl f acc = function
  | [] -> acc
  | x :: xs' -> foldl f (f acc x) xs'
```

**Definicja foldr**:
```ocaml
let rec foldr f acc = function
  | [] -> acc
  | x :: xs' -> f x (foldr f acc xs')
```

**Przykład z wykładu dla foldl**: Sumowanie elementów listy
```ocaml
foldl (fun acc x -> acc + x) 0 [1; 2; 3];  (* Wynik: 6 *)
```

**Przykład z wykładu dla foldr**: Sumowanie elementów listy z użyciem foldr
```ocaml
foldr (fun x acc -> x + acc) 0 [1; 2; 3];  (* Wynik: 6 *)
```
### Currying i uncurrying
**Currying** przekształca funkcję wieloargumentową w serię funkcji jednoargumentowych.
```ocaml
let curried_add x y = x + y
let add = curried_add 5
let result = add 3 (* Wynik: 8 *)
```

**Uncurrying** to proces odwrotny do currying, który przekształca ciąg funkcji jednoargumentowych z powrotem w funkcję wieloargumentową.
```ocaml
let uncurried_add (x, y) = x + y
let result = uncurried_add (5, 3) (* Wynik: 8 *)
```

### Operator łączenia w potok |>
Operator |> (pipeline) pozwala na przekazywanie wyniku jednej funkcji jako argument do kolejnej, co ułatwia tworzenie czytelnych i zwięzłych sekwencji operacji. Jest to szczególnie przydatne w językach programowania funkcyjnego, takich jak OCaml, gdzie zwięzłość i czytelność kodu są wysoko cenione.

**Przyklad** Załóżmy, że chcemy najpierw zwiększyć każdy element listy o 1, a następnie wybrać z tej listy tylko te elementy, które są parzyste. Użycie operatora |> pozwala na eleganckie zapisanie tych operacji w jednej linii:

```ocaml
[1; 2; 3] |> map (fun x -> x + 1) |> filter (fun x -> x mod 2 = 0)
```
Pierwsza część sekwencji map (fun x -> x + 1) zwiększa każdy element listy o 1, wynik jest następnie przekazywany do funkcji filter (fun x -> x mod 2 = 0), która selekcjonuje tylko elementy parzyste. Cała operacja jest zapisana w sposób, który łatwo oddaje intencje programisty bez nadmiaru skomplikowanego kodu.

---

## Diagramy pudełkowe
1. Diagramy pudełkowe dla list
2. Współdzielenie i kopiowanie
3. Pojęcie nieużytku
4. Operatory porównania strukturalnego = oraz fizycznego ==

Diagramy pudełkowe to graficzna reprezentacja struktur danych, takich jak listy, drzewa, czy inne złożone typy, które pomagają wizualizować ich budowę i sposób organizacji danych.

### Diagramy pudełkowe dla list

Listy w językach funkcyjnych często są reprezentowane jako ciąg połączonych "pudełek" (komórek), gdzie każde "pudełko" zawiera element listy oraz wskaźnik do następnego "pudełka" w sekwencji. Ostatnie "pudełko" wskazuje na pustą listę, reprezentując koniec listy.

**Przuklad** listy w OCaml, gdzie diagram pudełkowy może wyglądać następująco dla listy [1; 2; 3]:

```ocaml
[1] -> [2] -> [3] -> []
```
Każde pudełko zawiera wartość i wskazówkę na następne pudełko, z wyjątkiem ostatniego, które wskazuje na listę pustą.

### Współdzielenie i kopiowanie
W kontekście struktur danych, współdzielenie odnosi się do sytuacji, w której różne części programu mogą odnosić się do tej samej instancji danych, podczas gdy kopiowanie tworzy nową, niezależną instancję danych.

**Przyklad** W tym przypadku lista2 współdzieli dane z lista1, nie ma tutaj kopiowania danych.

```ocaml
let lista1 = [1; 2; 3]
let lista2 = lista1
```

### Pojęcie nieużytku
Nieużytek to dane, do których program już nie ma dostępu. W językach z automatycznym zarządzaniem pamięcią, takich jak OCaml, nieużytki są usuwane przez mechanizm zwanym garbage collector.

**Przyklad** Po wykonaniu funkcji tworz_liste, lista [1; 2; 3] staje się nieużytkiem, ponieważ nie ma do niej więcej referencji.

```ocaml
let tworz_liste () = [1; 2; 3]
let _ = tworz_liste ()
```

### Operatory porównania strukturalnego = oraz fizycznego ==
OCaml oferuje dwa rodzaje porównań: strukturalne i fizyczne. Strukturalne (=) porównuje wartości danych, podczas gdy fizyczne (==) porównuje, czy dwie zmienne wskazują na ten sam obszar w pamięci.

**Przyklad** Poniższy kod ilustruje różnicę między porównaniem strukturalnym a fizycznym.

```ocaml
let lista1 = [1; 2; 3]
let lista2 = [1; 2; 3]
let lista3 = lista1

let _ = print_endline (string_of_bool (lista1 = lista2))   (* true, porównanie strukturalne *)
let _ = print_endline (string_of_bool (lista1 == lista2))  (* false, porównanie fizyczne *)
let _ = print_endline (string_of_bool (lista1 == lista3))  (* true, porównanie fizyczne *)
```

---

## Drzewiaste struktury danych

1. Algebraiczne typy danych
2. Dopasowanie wzorca z algebraicznymi typami danych
3. Drzewa przeszukiwań binarnych

Drzewiaste struktury danych to hierarchiczne struktury, które pozwalają na efektywne przechowywanie i organizację danych w formie drzewa. Drzewa składają się z węzłów połączonych krawędziami, gdzie każdy węzeł poza korzeniem ma dokładnie jednego rodzica.

**Definicja drzewa binarnego** 
```ocaml
type 'a binary_tree =
  | Empty
  | Node of 'a binary_tree * 'a * 'a binary_tree
```

Ta definicja reprezentuje drzewo binarne, gdzie każdy węzeł może mieć dwoje dzieci: lewe i prawe.

### Algebraiczne typy danych
Algebraiczne typy danych (ADT) to typy złożone, które mogą być definiowane przez użytkownika w językach programowania takich jak OCaml. Pozwalają one na konstruowanie bardziej złożonych struktur danych.

**Przyklad** definicja typu option
```ocaml
type 'a option =
  | None
  | Some of 'a
```
typ option jest przykładem algebraicznego typu danych, który może być użyty do reprezentowania wartości, które mogą być obecne lub nie.

### Dopasowanie wzorca z algebraicznymi typami danych
Dopasowanie wzorca (pattern matching) pozwala na inspekcję algebraicznych typów danych i wykonanie różnych operacji w zależności od ich konkretnego kształtu.

**Przyklad** dopasowanie wzorca dla option:

```ocaml
let safe_head = function
  | [] -> None
  | x :: _ -> Some x
```

Ta funkcja zwraca Some z pierwszym elementem listy lub None, jeśli lista jest pusta, używając dopasowania wzorca.

### Drzewa przeszukiwań binarnych
Drzewa przeszukiwań binarnych to specjalny rodzaj drzew binarnych, które umożliwiają efektywne przeszukiwanie, wstawianie i usuwanie elementów. W drzewie BST dla każdego węzła wszystkie elementy w lewym poddrzewie są mniejsze od węzła, a wszystkie elementy w prawym poddrzewie są większe.

**Przyklad** Usuwanie z BST:
Usuwanie elementu z BST może być bardziej skomplikowane niż wstawianie, ponieważ trzeba rozważyć kilka przypadków, takich jak brak dzieci, obecność jednego dziecka lub obu dzieci.

```ocaml
let rec delete x = function
  | Empty -> Empty
  | Node (l, y, r) ->
    if x < y then Node (delete x l, y, r)
    else if x > y then Node (l, y, delete x r)
    else match l, r with
      | Empty, _ -> r
      | _, Empty -> l
      | _, _ ->
        let succ = min_value r in
        Node (l, succ, delete succ r)

let rec min_value = function
  | Empty -> failwith "Tree is empty"
  | Node (Empty, x, _) -> x
  | Node (l, _, _) -> min_value l
```
W tym kodzie funkcja delete usuwa węzeł z drzewa. Jeśli węzeł ma oba dzieci, wyszukuje następcę (najmniejszą wartość w prawym poddrzewie) i zastępuje węzeł tą wartością, a następnie usuwa następcę z prawego poddrzewa. Funkcja min_value pomaga znaleźć najmniejszą wartość w drzewie.

**Przyklad** wstawianie do BST
```ocaml
let rec insert x = function
  | Empty -> Node (Empty, x, Empty)
  | Node (l, y, r) as n ->
      if x < y then Node (insert x l, y, r)
      else if x > y then Node (l, y, insert x r)
      else n
```

Ta funkcja insert dodaje nowy element do drzewa BST, zachowując jego własności.

***Przyklad** Wyszukiwanie w BST:
Wyszukiwanie wartości w BST wykorzystuje strukturę drzewa do efektywnego przeszukiwania.
```ocaml
let rec find x = function
  | Empty -> false
  | Node (l, y, r) ->
    if x = y then true
    else if x < y then find x l
    else find x r
```
Ta funkcja find zwraca true, jeśli element jest obecny w drzewie, i false w przeciwnym razie, przeszukując rekursywnie odpowiednie poddrzewa.

---

## Podsumowanie
Wykład 3 skupiał się na zaawansowanych konceptach w programowaniu funkcyjnym, z naciskiem na funkcje wyższego rzędu, diagramy pudełkowe, algebraiczne typy danych, oraz drzewa przeszukiwań binarnych. Główne punkty to:

- Funkcje Wyższego Rzędu
    - Funkcje map i filter - niezbędne narzędzia do transformacji i selekcji elementów list bez zmiany oryginalnych danych.
    - Funkcje foldl i foldr - umożliwiają redukcję listy do jednej wartości, akumulując wyniki.
    - Currying i uncurrying - techniki umożliwiające transformację funkcji wieloargumentowych.
    - Operator łączenia w potok |> - ułatwia tworzenie czytelnych ciągów operacji.

- Diagramy Pudełkowe
    - Znacząco ułatwiają zrozumienie struktury i organizacji danych w listach i innych strukturach.
    - Współdzielenie i kopiowanie - kluczowe koncepcje w zarządzaniu pamięcią i strukturami danych.
    - Pojęcie nieużytku - odnosi się do danych, które są już niepotrzebne i mogą zostać usunięte przez garbage collector.
    - Porównania strukturalne i fizyczne - różne sposoby oceny równości danych w OCaml.

- Drzewiaste Struktury Danych
    - Algebraiczne typy danych - pozwalają na definiowanie złożonych struktur danych, które mogą lepiej modelować problemy.
    - Dopasowanie wzorca z algebraicznymi typami danych - potężna technika analizy i dekonstrukcji danych.
    - Drzewa przeszukiwań binarnych (BST) - specjalny typ drzewa binarnego, który umożliwia efektywne przeszukiwanie, wstawianie i usuwanie elementów. Omówiono kluczowe operacje, takie jak wstawianie i wyszukiwanie, podkreślając ich znaczenie w efektywnym zarządzaniu danymi.
    



