let parens_ok s = 
    let rec sprawdzenie ile_okr = function
    | [] -> if ile_okr == 0 then true else false
    | h :: t -> match h with
        | '(' -> sprawdzenie (ile_okr + 1) t
        | ')' -> if ile_okr - 1 < 0 then false else sprawdzenie (ile_okr - 1) t
        | _ -> failwith "niepoprawny char"
    in sprawdzenie 0 (List.of_seq(String.to_seq s));;
