(* reprezentacja danych *)

(* krotka *)
let t2 = (42,  "foo");;
let t3 = 42, "foo", false;;

print_int (fst t2);;
print_string (snd t2);;

(* użycie dopasowania wzorca *)
let a, b, c = t3;;

(* inna opcja *)
let fst_of_3 (a, b, c) = a;;

(* jeśli jakieś zmienne nas nie interesują to możemy napisać _ jako nazwe zmiennych *)
let snd_of_3 (_, b, _) = b;; 

(* konstruktor opcji *)
let o = Some 3;;
let on = None;;

(* korzystanie z option *)
print_int (Option.get o);;
Option.get on (*tutaj się dzieje wyjąek *)

(* predykaty *)
Option.is_none o;;
Option.is_none o;;

match o with Some a -> a | None -> 0;;

let int_of_int_option o b =
	match o with
	| Some a -> a
	| None -> b

(* własne typy (synonimy typów)*)
type vec2 = float * float;;
let make_vec2 x y = ((x, y): vec2);;
make_vec2 2. 3. ;;
let a, b = make_vec2 2. 3.;;

let vec2_x (v: vec2) = fst v;;
let vec2_y (v: vec2) = snd v;;


(* te funkcje działają tak samo *)
let is_vec_zero (v: vec2) = fst v = 0. && snd v = 0.;;
let is_vec_zero ((x, y): vec2) = x = 0. && y = 0.;;

let square x = x *. x
let vec_length v = sqrt (square (vec2_x v) +. square(vec2_y v))



