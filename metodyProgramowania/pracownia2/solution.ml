(*
	Jakub Iliński 346796 pracownia_2
	zamysł na zadanie:
		W rozwiązaniu szukam wyrażeń które mogę zamienić (szukam przy pomocy funkcji to replace)
		gdy mam już listę wszystkich wyrażeń do zamiany przechodzę się po niej i zamieniam wyrażenie
		(przy pomocy funkcji replace). Żeby to sprawdzić czy dwa wyrażenia są takie same używam zad 2
		z listy 8 z metodą 2 (indeksy de Brijna)

	funkcje które użyłem:
		(sprawdzanie czy wyrażenia są takie same)
		convert_to_idb : expr -> expr
			przekształca wyrażenie na reprezentacje wykorzystującą indeksy de Bruijna (zad2 lista 8)
		alpha_equivalent : expr -> expr -> bool
			sprawdza czy dwa wyrażenia są α-równoważne
		same_expressions : expr -> expr -> ident list -> bool
			sprawdza czy dwa wyrażenia są takie same

		(szukanie wyrażeń do zamiany)
		find_to_replace : expr -> ex
			znajduje wszystkie podwyrażenia, które można zastąpić

		(zamiana wyrażeń)
		replace : expr -> expr -> int -> expr
			zastępuje wyrażenia

		(funkcje pomocnicze)	
		free_vars : expr -> ident list
			zwraca listę zmiennych wolnych w wyrażeniu
		sub_expr : expr -> expr list
			zwraca liste wszystkich podwyrażeń (które nie są trywialne) w wyrażeniu
*)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq

type ident = string

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Var of ident
  | Let of ident * expr * expr

(* CSE *)

let convert_to_idb e =
	let rec idx_of f lst = 
		let rec aux index = function
		| [] -> None
		| x :: xs -> if f x then Some index else aux (index + 1) xs
		in aux 0 lst

	and conv_rec e acc =	
		match e with
		| Int v -> Int v
		| Bool v -> Bool v
		| Var v -> (match idx_of ((=) v) acc with
			| Some idx -> Var (string_of_int idx)
			| None -> Var v) 
		| Binop (op, e1, e2) ->
			Binop (op, conv_rec e1 acc, conv_rec e2 acc)
		| If (cond, e1, e2) ->
			If (conv_rec cond acc, conv_rec e1 acc, conv_rec e2 acc)
		| Let (var, e1, e2) ->
			Let ("", conv_rec e1 acc, conv_rec e2 (var :: acc))
		in conv_rec e []

(* zwraca liste zmiennych wolnych *)
let free_vars expr =
	let rec itr bounded = function
	| Int _ | Bool _ -> []
	| Var v -> if List.mem v bounded then [] else [v]
	| Binop (op, e1, e2) -> (itr bounded e1) @ (itr bounded e2)
	| If (cond, e1, e2) -> (itr bounded cond) @ (itr bounded e1) @ (itr bounded e2)
	| Let (v, e1, e2) -> (itr bounded e1) @ (itr (v::bounded) e2)
	in itr [] expr


let alpha_equivalent expr1 expr2 =
	let idb_expr1 = convert_to_idb expr1 
	and idb_expr2 = convert_to_idb expr2 in 
	idb_expr1 = idb_expr2

(* zwraca wszystkie podwyrażenia *)
let rec sub_expr expr = 
	match expr with
	| Int _ | Bool _ | Var _ -> []
	| Binop (op, e1, e2) -> expr :: sub_expr e1 @ sub_expr e2
	| If (cond, e1, e2) -> expr :: sub_expr cond @ sub_expr e1 @ sub_expr e2
	| Let (v, e1, e2) -> expr :: sub_expr e1 @ sub_expr e2

let int_of_bool b =
	if b then 1 else 0

let same_expressions e1 e2 free_var_e =
	let free_var_e1 = List.sort_uniq compare (free_vars e1)
	and free_var_e2 = List.sort_uniq compare (free_vars e2)
	in alpha_equivalent e1 e2 && free_var_e1 = free_var_e && free_var_e2 = free_var_e

let find_to_replace expr = 
	let sub_expr_e = sub_expr expr in
	let free_var_e = List.sort_uniq compare (free_vars expr) in 

	(*ilość wystąpień wyrażenia e w expr*)
	let occurrences e =
		let rec itr expr_list cnt =
			match expr_list with
			| [] -> cnt 
			| h::t -> itr t (cnt + int_of_bool (same_expressions h e free_var_e))
		in itr sub_expr_e 0
	in

	let rec not_in e e_list =
		match e_list with
		| [] -> true
		| h::t -> 
			if same_expressions e h free_var_e then false
			else not_in e t
	in
		
	let rec find_duplicates acc sub_expr =
		match sub_expr with
		| [] -> acc
		| h::t -> 
			if occurrences h > 1 && not_in h acc
			then find_duplicates (h::acc) t 
			else find_duplicates acc t
		in find_duplicates [] sub_expr_e 

let replace expr_to_replace main_expr idx =
	let fresh_var = "fresh_var" ^ (string_of_int idx) in
	let free_var_main = List.sort_uniq compare (free_vars main_expr) in
	let rec itr expr =
		if same_expressions expr expr_to_replace free_var_main
			then Var(fresh_var) else
			match expr with
			| Int _ | Bool _ | Var _ -> expr
			| Binop(op, e1, e2) -> Binop(op, itr e1, itr e2)
			| If(cond, e1, e2) -> If(itr cond, itr e1, itr e2)
			| Let(v, e1, e2) -> Let(v, itr e1, itr e2)
		in Let(fresh_var, expr_to_replace, itr main_expr)

let cse expr = 
	let to_replace = find_to_replace expr in
	match to_replace with
		| [] -> None (* nie ma co zamieniać*)
		| _ ->	     (* iteruje się po tych wyrażeniach i je zmieniam *)
			let rec itr acc expr =
			match acc with
			| [] -> Some expr
			| e::es -> itr es (replace e expr (List.length acc))
			in itr to_replace expr


	