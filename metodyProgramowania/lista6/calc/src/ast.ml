(* abstract syntax tree *)

type bop = 
  | Mult | Div | Add | Sub
  | Eq | Neq                    (* Nowy operator różności *)
  | Lt | Le | Gt | Ge           (* Nowe operatory porównań *)

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
                               
