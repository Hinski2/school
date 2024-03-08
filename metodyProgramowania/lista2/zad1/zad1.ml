let rec fib_rec n = 
	if n == 0 then 0
	else if n == 1 || n == 2 then 1
	else fib_rec (n - 1) + fib_rec (n - 2);;

let fib_iter n =
	let rec itr i a b = 
		if i = n then b
		else itr (i + 1) (b) (a + b)
	in match n with
    | 0 -> 0
    | _ -> itr 1 0 1;;

print_int (fib_iter 40);;
print_char '\n';;
flush stdout;  (* Wymuszenie natychmiastowego wypisania danych *)

print_int (fib_rec 40);;
print_char '\n';;
flush stdout;  (* Wymuszenie natychmiastowego wypisania danych *)

print_int (fib_iter 1000);;
print_char '\n';;
flush stdout;  (* Wymuszenie natychmiastowego wypisania danych *)