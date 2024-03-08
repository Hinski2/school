let select xs = 
  let rec find_min mini rest ys = match ys with
    | [] -> (mini, rest)
    | head :: tail ->
        if head < mini then find_min head (mini :: rest) tail (*jeśli head < mini to sprawdzam head staje się mini, wcześniejsze mini dołączam do rest i ide dalej*)
        else find_min mini (head :: rest) tail (*jeśli nie to mini pozostaje bez zmian, dołączam head do rest i ide dalej *)
  in match xs with
    | head :: tail -> find_min head [] tail
    | [] -> failwith "select: empty list";; (* to się nie wywoła*)


(*dla każdegy wywołania szukam najmniejszy elementa z listy rest i dodaje go do wyniku*)
let rec select_sort xs = 
    match xs with
    | [] -> []
    | _ -> let (min, rest) = select xs (*najpierw znajduje min i res przy użyciu select*)
    in min :: (select_sort rest);; (*potem łącze minimalny element z tym co wróci select_sort rest, czyli następnymi najmniejszymi elementami*)


