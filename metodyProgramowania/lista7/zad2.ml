(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq | And | Or

type ident = string
type range = int * int
                                                                         
type expr =
  | Int of int
  | Bool of bool
  | Var of ident
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Let of ident * expr * expr
;;

type for_loop = 
  | Loop of ident * range * for_loop list
  | Instruction of expr
;;

(* w for i := n to m do ... end (* pętla w Pascalu *) i - string, n - var, m - var, reszta - seq list *)

(* całka *) 

type integral = ident * range * expr

