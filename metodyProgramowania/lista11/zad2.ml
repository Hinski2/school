let find (type t) p (xs : t list) = 
	let exception Found of t in 
	try 
		List.fold_left (fun _ x -> 
			if p x then raise (Found x)
			else ()
		) () xs;
		raise Not_found
	with
	| Found x -> x

let pred = fun x -> x >= 5;;
let test1 = find pred [6;4;3;5];;
let test2 = find pred [4; 3; 1];;
let test3 = find pred [];;
let test4 = find pred [4;3;6;7];;


