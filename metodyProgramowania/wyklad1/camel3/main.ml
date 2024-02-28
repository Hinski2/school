let is_zero (x: int) : string = 
  match x with
    | 0 -> "true"
    | _ -> "false";;

print_endline (is_zero 0)