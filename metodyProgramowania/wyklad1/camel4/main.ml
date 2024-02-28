let y : int list = [1; 2; 3];;
let is_list_empty (l: int list) : int =
  begin match l with
  | [] -> 1
  | h::t -> 0
  end;;

print_int (is_list_empty y)