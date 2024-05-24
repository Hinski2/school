exception Found

let exists f xs = 
	try
		List.fold_left (fun acc x -> 
			if f x then raise Found
			else false
		) false xs
	with
	| Found -> true


let test1 = exists (fun x -> x == 5) [6;4;3;5];;
let test2 = exists (fun x -> x == 5) [6;4;3];;
let test3 = exists (fun x -> x == 5) [];;
let test4 = exists (fun x -> x == 5) [5;3;2];;