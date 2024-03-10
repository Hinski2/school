let rec is_element_of x xs =
  match xs with
  	| [] -> false
  	| head::tail -> if head = x then true else is_element_of x tail;;
  
let rec 