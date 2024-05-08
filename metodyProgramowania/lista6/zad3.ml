module Zad3 = struct

    open List
  
    type 'a symbol =
        | T of string       (*symbol terminalny*)
        | N of 'a           (*symbol nieterminalny*)
  
    type 'a grammar = ('a * ('a symbol list) list) list

    let rec generate (g : 'a grammar) (s : 'a) : string =
        let productions = List.assoc s g in  (* Może dać wyjątek Not_found *)
        let production = List.nth productions (Random.int (List.length productions)) in
            String.concat "" (List.map (function    
            | T str -> str
            | N nonterm -> generate g nonterm
            ) production)

    let pol : string grammar =
        [ "zdanie", [[N "grupa-podmiotu"; N "grupa-orzeczenia"]]
        ; "grupa-podmiotu", [[N "przydawka"; N "podmiot"]]
        ; "grupa-orzeczenia", [[N "orzeczenie"; N "dopelnienie"]]
        ; "przydawka", [[T "Piękny "];
                        [T "Bogaty "];
                        [T "Wesoły "]]
        ; "podmiot", [[T "policjant "];
                    [T "student "];
                    [T "piekarz "]]
        ; "orzeczenie", [[T "zjadł "];
                        [T "pokochał "];
                        [T "zobaczył "]]
        ; "dopelnienie", [[T "zupę."];
                        [T "studentkę."];
                        [T "sam siebie."];
                        [T "instytut informatyki."]]]
    
    (* generate pol "zdanie" *)
    
    let expr : unit grammar =
        [(), [[N (); T "+"; N ()];
            [N (); T "*"; N ()];
            [T "("; N (); T ")"];
            [T "1"];
            [T "2"]]]
    
    (* generate expr () *)
  
  end
    (* 
        funkcja generate przujmuje gramatyke i symbol nieterminalny 
        najpierw szukamy w gramatyce listy produkcji dla symbolu nieterminalnego
        jeśli znajdziezmy liste produjcji to losowy wynieramy jedna z nich przy użyciu Random.int i List.nth
        używamy map by dla każdego symbolu w wybranej produkcji:
            * dla symboli terminalnych: (T str) dodajemy str do wynikowego słowa
            * dla symboli nieterminalnych: (N nonterm) rekurencyjnie wywolujemy sibie z nonterm 
        na koniec robimy konkatenacje listy stringów
    *)

    (* 
    lista asocjacyjna (czyli lista par klucz–warto´s´c), w której kluczami s ˛a
    symbole nieterminalne, a warto´sciami lista prawych stron produkcji dla danego symbolu nieterminalnego. Kazda prawa strona produkcji to lista, która ˙
    moze zawiera´c symbole terminalne i nieterminalne.   
    *)