let ( let* ) xs ys = List.concat_map ys xs

let rec choose m n =
  if m > n then [] else m :: choose (m+1) n

(* licznik zapalonych bitów *)
let popcnt x =
	let rec itr acc = function
	| 0 -> acc
	| x -> itr (acc + x land 1) (x lsr 1)
	in itr 0 x
;;

(* liczy sume długości bloków w rzedzie *)
let sum_blocks_in_row xs = 
	let rec itr acc = function
	| [] -> acc
	| h::t -> itr (acc + h) t
	in itr 0 xs
;;

(* z maski bitowej oraz długości listy tworzy liste*)
let list_from_mask mask n = 
	let rec itr acc mask = function
	| -1 -> List.rev acc
	| n -> itr ((mask lsr n land 1 = 1) :: acc) mask (n - 1) (* sprawdza czy n'ty bit jest zapalony *)
	in itr [] mask (n - 1)
;;

(*zamiana listy booli na liste intów *)
let from_bool_to_int_list xs =
	let rec itr acc_ps ile_acc = function 
	| [] -> if ile_acc > 0 then List.rev (ile_acc :: acc_ps) else List.rev acc_ps
	| h::t -> if h then itr acc_ps (ile_acc + 1) t else 
		if ile_acc > 0 then itr (ile_acc :: acc_ps) 0 t
		else itr acc_ps 0 t
	in itr [] 0 xs
;;
let verify_row ps xs = 
	let ys = from_bool_to_int_list xs in
	let rec itr ans ps ys = match ps with
	| [] -> if ys = [] then ans else false
	| h::t -> if ys = [] || List.hd ys <> h then false else itr ans t (List.tl ys)
	in if ys = [] && ps = [] then true else itr true ps ys (* dodatkowe spawdzenie jeśli obie listy są puste to true*)
;;


let build_row ps n = 
	let maks = 1 lsl n and sum = sum_blocks_in_row ps in
		let* mask = choose 1 maks in
		if popcnt mask == sum && verify_row ps (list_from_mask mask n) (* jeśli maska ma tyle samo zapalonych bitów co suma boków w ps oraz maska jest dobra*)
			then [list_from_mask mask n]
			else []
;;

(* dla każdego elementu z xss dla każdego elementu z ys funkcja dodaje do na początek elementu z xss element x ys *)
let iloczyn_list (xss: bool list list list) (ys: bool list list) = 
	let* a = xss in 
	let* b = ys in
		[b::a]
;;


let build_candidate (pss: int list list) (n: int) = 
	let rec generator acc = function
	| [] -> List.map List.rev acc
	| h::t -> generator (iloczyn_list acc (build_row h n)) t
	in generator [[]] pss
;;

let verify_rows pss xss = 
	let rec itr ans pss xss = match pss with
	| [] -> ans
	| h::t -> itr (verify_row h (List.hd xss) && ans) t (List.tl xss)
	in itr true pss xss
;; 

let transpose xss = 
	let rec transRec acc xss =
		match xss with
		| [] :: _ -> List.rev acc
		| xss -> transRec ((List.map List.hd xss) :: acc) (List.map List.tl xss)
	in if xss = [] then [] else transRec [] xss;;  (* dzięki tamu działa tez dla listy pustej *)

type nonogram_spec = {rows: int list list; cols: int list list}

let solve_nonogram nono =
  build_candidate (nono.rows) (List.length (nono.cols))
  |> List.filter (fun xss -> transpose xss |> verify_rows nono.cols)

let example_1 = {
  rows = [[2];[1];[1]];
  cols = [[1;1];[2]]
}

let example_2 = {
  rows = [[2];[2;1];[1;1];[2]];
  cols = [[2];[2;1];[1;1];[2]]
}

let big_example = {
  rows = [[1;2];[2];[1];[1];[2];[2;4];[2;6];[8];[1;1];[2;2]];
  cols = [[2];[3];[1];[2;1];[5];[4];[1;4;1];[1;5];[2;2];[2;1]]
}