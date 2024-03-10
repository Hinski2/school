let rev xs =
    let rec itr acc = function
    | [] -> acc
    | head::tail -> itr (head :: acc) tail
in itr [] xs

let build_list n f =
    let rec aux i acc =
        if i >= n then acc
        else aux (i + 1) (f i :: acc)
    in rev (aux 0 []);;

let negatives n = 
    build_list n (fun x -> -x);;

let reciprocals n =
    build_list n (fun x -> 1.0 /. float_of_int(x + 1));;

let evens n =
    build_list n (fun x -> 2 * (x + 1))

let identyM n =
    build_list n (fun x -> build_list n (fun j -> if x = j then 1 else 0)) 




    