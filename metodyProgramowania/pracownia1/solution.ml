(*
	README.ml
	pomysł na program był taki, że dla każdego wiersza
	 	1. tworze liste kandydatów zgodnych ze spocyfikacja dla konkretnego wiersza
		2. (mam liste częściowo obliczonych kandydatów na rozwiązanie całego nanogramu, na samym początku to lista pusta) 
			dla każdego potencjalnego rozwiązania dla każdego elementu z wygenerowane listy z kroku 1. dodaje na koniec
			potencjalnego kondydata nowy wiersz 
				np.
				jeden z potencjalnych kandydatów na rozwiązanie
				#0###0#
				000#000
				#00000#
				mam liste nowych wierszy zgodnych z konkretną specyfikacją wiersza [[#####00]; [0#####0]; [00#####]]
				i dokłdam każdy z wierszy na koniec kandydata otrzymując:
				#0###0#		#0###0# 	#0###0#  
				000#000		000#000 	000#000 
				#00000#		#00000# 	#00000# 
				#####00		#####00		#####00
				tę czynność powtarzam dla wszystkich kandydatów na rozwiązanie
		3. podczas etapu 2. nasza lista kandydatów na rozwiązanie mocno rośnie więc w tym momencie robie nawroty
			przy użyciu filtracji i specyfilacji kolumn usówam kandadatów którzy nie spełniają specyfikacji kolumnowej
	na sam koniec otrzymuje rozwiązanie

	Czas wykonywania się example_1: instant
	Czas wykonywania się example_2: instant
	Czas wykonywania się big_Example: ~3s (gdyby nie krok 3. big_Example by się nie obliczyło)

	poco sią niektóre funkcje:
		Popcnt i sum_blocks_in_row: pozwalają mi szybciej odrzucić kandydatów na nowy wiersz niezgodne ze specyfikacją
		list_from_mask: dla zadanej maski zwraca mi liste booli, pozwala mi to na łatwe generowanie nowych wierszy
		from_bool_to_int_list: dzięki niej zamieniał liste booli otrzymaną przy pomocy list_from mask na liste bloków,
		 	dzięki czemu łatwo mi sprawdzić czy dany wiersz jest zgodny ze specyfikacją
		iloczyn_list: dzięki niej łatwo mogę wykonać krok 2. 
		cz1 i cz2: webcat wymaga by build_candidate był postaci: int list list -> int -> bool list list list,
			ale do robiena nawrotów (filtracji) potrzebuje oprócz nono.rows nono.cols, ale nie mogę ich przekazać oddzielnie
			więc przekazuje ich połączenie a cz1 i cz2 pozwalają mi na ich rozłączenie
		partialy_verify_row i partialy_verify_rows: służą do kroku 3. sprawdzają czy kandydat jest zgodny
			ze specyfikacją kolumn
*)
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
let transpose xss = 
	let rec transRec acc xss =
		match xss with
		| [] :: _ -> List.rev acc
		| xss -> transRec ((List.map List.hd xss) :: acc) (List.map List.tl xss)
	in if xss = [] then [] else transRec [] xss
;;  (* dzięki tamu działa tez dla listy pustej *)

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

let partialy_verify_row ps xs =
	let ys = from_bool_to_int_list xs in
	let rec itr ans ps ys = match ps with
	| [] -> if ys = [] then ans else false
	| h::t -> match ys with
        | [] -> true
		| [x] -> if x > h then false else true
        | a::b -> if a <> h then false else itr ans t b
	in if ys = [] && ps = [] then true else itr true ps ys (* dodatkowe spawdzenie jeśli obie listy są puste to true*)
;;

let partialy_verify_rows pss xss = 
	let rec itr ans pss xss = match pss with
	| [] -> ans
	| h::t -> itr (partialy_verify_row h (List.hd xss) && ans) t (List.tl xss)
	in itr true pss xss
;; 

let verify_rows pss xss = 
	let rec itr ans pss xss = match pss with
	| [] -> ans
	| h::t -> itr (verify_row h (List.hd xss) && ans) t (List.tl xss)
	in itr true pss xss
;;
let cz2 xss n = 
	let m = List.length xss - n in 
	let rec itr acc idx = function
	| [] -> List.rev acc
	| h::t -> if idx >= m then itr (h :: acc) (idx + 1) t 
	else itr acc (idx + 1) t
	in itr [] 0 xss
;; 

let cz1 xss n = 
	let m = List.length xss - n in
	let rec itr acc idx = function
	| [] -> List.rev acc
	| h::t -> if idx < m then itr (h :: acc) (idx + 1) t 
	else itr acc (idx + 1) t
	in itr [] 0 xss
;; 

let build_candidate xss n = 
	let pss = cz1 xss n and css = cz2 xss n in
	let rec generator acc = function
	| [] -> List.map List.rev acc
	| h::t -> let new_acc = iloczyn_list acc (build_row h n) in
        let filterd_new_acc =  new_acc |> List.filter (fun xss -> xss |> List.rev |> transpose  |> partialy_verify_rows css) in
        generator filterd_new_acc t
	in generator [[]] pss
;;

type nonogram_spec = {rows: int list list; cols: int list list}

let solve_nonogram nono =
  build_candidate ((nono.rows) @ (nono.cols)) (List.length (nono.cols)) (* lekko zmieniam specyfikacje i daje do liste kolumn i wierszy by móc robić nawroty (potem rozdzielie tą liste na cols i rows, ale musze je polączyć bo webcat narzeka)*)
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