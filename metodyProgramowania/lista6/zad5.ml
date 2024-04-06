type 'a stack = 
| Empty
| Entry of 'a * 'a stack

let empty = Empty

let push x s =
	Entry (x, s)

let peek = function
| Empty -> failwith "stack is empty"
| Entry (x, s) -> x

let pop = function
| Empty -> failwith "stack is empty"
| Entry (x, s) -> s


let parens_ok s = 
	let rec sprawdzenie stos = function
	| [] -> if stos == Empty then true else false
	| h :: t -> match h with
		| '(' | '[' | '{' -> sprawdzenie (push h stos) t
		| ')' -> if stos != Empty && (peek stos) == '(' then sprawdzenie (pop stos) t else false
		| ']' -> if stos != Empty && (peek stos) == '[' then sprawdzenie (pop stos) t else false
		| '}' -> if stos != Empty && (peek stos) == '{' then sprawdzenie (pop stos) t else false
		| _ -> false
	in sprawdzenie empty (List.of_seq(String.to_seq s));;
