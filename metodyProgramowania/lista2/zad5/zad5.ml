let porownaj s f = 
    match s with
    | Some s -> Some (max s f) 
    | None -> Some f;; 
(* po prawje stronie jest potrzebne Some, bo funkca ma zwracać option float, a nie zwykłego float*)

let wypisz x =
    match x with
    | Some x -> print_float x; print_char '\n'
    | None -> print_endline "neg_inf";;

let mx xs =
    let rec itr xs2 maximum = match xs2 with
    | [] -> maximum
    | head :: tail -> itr tail (porownaj maximum head) in
    wypisz (itr xs None);;

mx [];;
mx [2.; 4.; 10.5];;
mx [-1.; -5.];;