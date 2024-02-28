"foo" ^ 42;;
(*Error: This expression has type int but an expression was expected of type
string *)

" foo " ^ string_of_int 42;;
(*- : string = " foo 42"*)

1. = 2;;
(*Error: This expression has type int but an expression was expected of type
         float
  Hint: Did you mean `2.'?*)

fun a -> a + 5;;
(*- : int -> int = <fun>*)

fun a -> if a > 5 then a else " foo";;
(*Error: This expression has type string but an expression was expected of type
int*)

fun a b -> if a > 5 then a else b;;
(*- : int -> int -> int = <fun>*)

fun a b ->
let c = a = b in
if a > 3 && b = " foo "
then c
else false ;;
(*Error: This expression has type string but an expression was expected of type
int*)

fun a ->
let f a b = a * a + b * b in
f ( f a a ) a;;
(* int -> int = <fun>*)

let f a = a > 2 in
if 3 > 2 then true else f ( f 2);;
(*Error: This expression has type bool but an expression was expected of type int*)