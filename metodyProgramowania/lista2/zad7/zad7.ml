let is_sorted xs =
    if xs = [] then true
    else
        let rec itr ys last = match ys with
        | [] -> true (*to się nie wykona*)
        | [x] -> if last > x then false else true
        | head :: tail -> if head > List.hd tail then false else itr tail head
        in itr xs (List.hd xs);;

let print_bool b =
    match b with
    | true -> print_endline "true"
    | false -> print_endline "false";;

print_bool (is_sorted []);;
print_bool (is_sorted [1]);;
print_bool (is_sorted [1; 2]);;
print_bool (is_sorted [2; 2]);;
print_bool (is_sorted [2; 1]);;
