(* pętala while *)
let rec fact n =
  	if n = 0 then 1 else n * fact (n - 1);;

let f = fact 20;;
(*print_int f;; *)

let fact_iter n =
	let rec itr n acc =
		if n = 0 then acc else itr (n - 1) (acc * n)
	in itr n 1 ;;

(* print_int (fact_iter 7) *)

