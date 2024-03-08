let rec mem x xs = 
    match xs with
    | [] -> false
    | head :: tail -> if head = x then true else mem x tail;;

let print_bool x = 
    match x with
    | true -> print_endline "true" 
    | false -> print_endline "false";;

print_bool (mem 2 [5; 2; 3;]);;
print_bool (mem 2 [2; 1]);;
print_bool (mem 2 [1; 2]);;
print_bool (mem 2 [1; 1]);;



