x;;
(*Wolne wystąpienie: x (nie ma lokalnej deklaracji x, więc jest to wolne wystąpienie).*)

let x = 3 in x + y;;
(*Związane wystąpienie: x (wiązane przez let x = 3).
Wolne wystąpienie: y (nie ma lokalnej deklaracji y, więc jest to wolne wystąpienie).*)

let x = 1
and y = x + 2
in x + y;;
(*Związane wystąpienie: pierwsze x (wiązane przez let x = 1).
Związane wystąpienie: y (wiązane przez and y = x + 2).
wolne wystąpienie: x + 2, przy użyciu and zmienne są związywane "nednocześnie"*)

let x = 1 in
let y = x + 2 in
x + y;;
(*obie związane*)

let f x y = x * y * z;;
(*z nie związane*)

let f x =
let g y z = x * y * z in
g ( h x ) z;;
(*Wolne wystąpienie: h (funkcja h nie jest zdefiniowana lokalnie, więc jest to wolne wystąpienie).
 drugie z w g ( h x ) z (nie jest związane przez let g y z, ponieważ jest używane poza g).*)