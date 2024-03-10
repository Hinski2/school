type 'a tree = 
    | Leaf
    | Node of 'a tree * 'a * 'a tree;;

let rec insert x = function
    | Leaf -> Node (Leaf, x, Leaf)
    | Node (l, y, r) -> 
        if x < y then Node ((insert x l), y, r)
        else if x > y then Node (l, y, (insert x r))
        else Node (l, y, r);;

let t =
  Node (Node (Leaf, 2, Leaf),
  5,
  Node (Node (Leaf, 6, Leaf),
  8,
  Node (Leaf, 9, Leaf)));;


(* Które fragmenty drzewa t są współdzielone międzydrzewem t i insert_bst 7 t:
    W OCaml, drzewa są niemutowalne, co oznacza, że każda operacja na drzewie, taka jak wstawienie nowego elementu, nie modyfikuje oryginalnego drzewa, lecz tworzy nowe drzewo. W nowym drzewie niektóre części mogą być współdzielone z oryginalnym drzewem, jeśli te części nie zostały zmienione podczas operacji.
    2, 9
*)


