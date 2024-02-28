(* Definicja funkcji sumującej dwie liczby *)
let sum a b = a + b;;

(* Wywołanie funkcji sum i przypisanie wyniku do zmiennej *)
let result = sum 5 3;;

(* Wypisanie wyniku na standardowym wyjściu *)
print_endline ("Suma 5 i 3 to " ^ string_of_int result);;
