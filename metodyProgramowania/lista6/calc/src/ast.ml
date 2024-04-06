(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq

type expr =
  | Int of int
  | Bool of bool
  | Binop of bop * expr * expr
  | If of expr * expr * expr
                               
