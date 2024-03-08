let matrix_mult (a, b, c, d) (e, f, g, h) =
    (a * e + b * g, a * f + b * h, c * e + d * g, c * f + d * h);;

let matrix_id = (1, 0, 0, 1);;
let matrix_fib = (1, 1, 1, 0);; 

let matrix_exp_slow matrix k = 
    let rec itr acc k = match k with
    | 0 -> acc
    | _ -> itr (matrix_mult acc matrix) (k - 1)
    in itr matrix_id k

let rec matrix_exp_fast matrix k =
    if k = 0 then matrix_id
    else let res = matrix_exp_fast (matrix) (k / 2) in
        if k mod 2 = 1 then matrix_mult (matrix_mult res res) (matrix)
        else matrix_mult (res) (res);;

(* k = 0 -> matrix_id
   
   res = matrix^(k / 2)     
   k mod 2 = 1 -> res^2 * matrix_id
   k mod 2 = 0 -> res^2 
*)


(*wypisywanie*)
let wypisz_wynik (_, _, a, _) = 
    a;;
let wypisz_fast k =
    let rec loop n =
        if n <= k then (
            print_int (wypisz_wynik (matrix_exp_fast matrix_fib n));
            print_char ' ';
            flush stdout;  (* Wymuszenie natychmiastowego wypisania danych *)
            loop (n + 1))
        else
            print_char '\n' 
    in loop (k - 5);;

let wypisz_slow k =
    let rec loop n =
        if n <= k then (
            print_int (wypisz_wynik (matrix_exp_slow matrix_fib n));
            print_char ' ';
            flush stdout;  (* Wymuszenie natychmiastowego wypisania danych *)
            loop (n + 1))
        else
            print_char '\n' 
    in loop (k - 5);;


wypisz_fast 5;; (*5 pierwszych*)
print_char '\n';;

wypisz_slow 50000000;; (*50 milionów*)
print_char '\n';;

wypisz_fast 50000000;;
print_char '\n';;
