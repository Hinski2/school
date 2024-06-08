(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq | And | Or

type ident = string
type cname = string

type pattern =
  | PWildcard
  | PVar  of ident
  | PInt  of int
  | PBool of bool
  | PCtor of cname * pattern list   (*zamiast pattern, pattern list*)
  | PAs   of pattern * ident

type expr =
  | Int of int
  | Bool of bool
  | Var of ident
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Let of pattern * expr * expr  
  | Fun of pattern * expr
  | App of expr * expr
  | Fst  of expr
  | Snd  of expr
  | Ctor of cname * expr list
  | Match of expr * clause list
  | Raise
  | Try of expr * expr

and clause = pattern * expr
