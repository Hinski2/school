(* lista *)
[1; 2];;

(* listy w ocamlu są monomorficzne czyli tak jak w c i nie tak jak w python *)
(* można zrobić liste funkcji *)

[Some 1; None];;
[(+); (-)];;
[fst; snd];;

(* konstruktory do listy *)
(* pusta list *)
[];;

(* tworzenie listy *)
List.cons 1 (List.cons 2 []);;
(* lub operator :: *)
let l = 1 :: 2 :: [];; (*lista 1, 2*)
(* może też być już istniejąca lista na końcu *)
1 :: 2 :: l;;

let rec linf = 1 :: linf;; (*nieskończona lista, która zajmuje skończoną liczbe miejsca (lista z pętlą*)

(* selektory do list *)
List.hd l;;(*daje dostęp do głowy*)

let xs = [1; 2];;
List.hd xs;; (*daje 1*)
List.tl xs;; (*daje [1:] czyli 2 element i dalej*)


(* wyjątek *)
List.tl [];;

(* definicje ciekawych funkcji do list *)
(* funkcja zwracająca n elemente listy *)
let rec nth xs n =
  if n = 0 
  then List.hd xs
  else nth (List.tl xs) (n - 1);; (* wywołanie ogonowe, czyli funkcja iteracyjna*)

nth xs 0;;
nth xs 1;;
nth xs 2;; (*wyjątek bo lista jest za krótka*)

List.tl linf;;
nth linf 10000;; (*wywoła się 10k razy*)

(* scalanie 2 lista razem *)
let rec append xs ys = 
  if xs = []
  then ys
  else List.hd xs :: append (List.tl xs) ys;; (*nie jest ogonowa*)

append [3;5;8] [1; 2; 3];; (*wynik to [3;5;8;1;2;3]*)

let rec append xs ys = 
  match xs with
  | [] -> ys
  | x :: xs2 -> x :: append xs2 ys;;

(* funkcja odwracająca listę *)
let rev xs = 
  let rec itr xs ys =
    match xs with
    | [] -> ys
    | x :: xs2 -> itr xs2 (x :: ys)
  in itr xs [];;

  let rec rev2 xs =
    match xs with
    | [] -> []
    | x :: xs2 -> append (rev2 xs2) [x];; (*to jest słabe bo robi nam się złożoność kwadratowa*)

(* tworzy nam liste o n elementach gdzie na itej pozycji jest i *)
let rec mk_list n =
  if n = 0 then [] else n :: mk_list (n - 1);;

let rec all_but_last xs =
  match xs with
  | [] -> failwith "empty list"
  | [x] -> []
  | x :: xs2 -> x :: all_but_last xs2;;

let rec last xs = 
  match xs with
  | [] -> failwith "empty list"
  | [x] -> x
  | x :: xs2 -> last xs2

(* nie jest strukturalnie rekurencyjnie *)
let rec rev3 xs =
  if xs == [] then [] else last xs :: rev3 (all_but_last xs)

(* sortowanie list, typ: sortowanie przez wstawianie *)
(* funkcja wstawiająca element do listy zachowująca porządek listy *)
let rec insert n xs =
  match xs with
  | [] -> [n]
  | x:: xs2 -> 
    if n < x
    then n :: xs
    else x :: insert n xs;;

let rec insertion_sort xs =
  match xs with
  | [] -> []
  | x :: xs2 -> insert x (insertion_sort xs2)

(* można to napisać rekursją ogonową *)
let insertion_sort_iter xs =
  let rec itr xs ys =
    match xs with
    | [] -> ys
    | x :: xs2 -> itr xs2 (insert x ys)
  in itr xs []
