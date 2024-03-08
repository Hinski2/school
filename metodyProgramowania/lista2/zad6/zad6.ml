let reverse xs =
    let rec itr xs rxs =
    match xs with
    | [] -> rxs
    | head :: tail -> itr tail (head :: rxs)
in itr xs [];;

let suffixes xs =
    let rec itr acc xss =
    match xss with
    | [] -> [] :: acc
    | _ -> itr (xss :: acc) (List.tl xss)
in  reverse (itr [] xs);;
