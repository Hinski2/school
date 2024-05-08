(* abstract syntax tree *)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq | And | Or

type ident = string
                                                                         
type expr =
  | Int of int
  | Bool of bool
  | Var of ident
  | Binop of bop * expr * expr
  | If of expr * expr * expr
  | Let of ident * expr * expr

(* Funkcja sprawdzająca, czy wyrażenie jest zamknięte w kontekście listy zmiennych związanych *)
let rec closed_with_env (env : ident list) (e : expr) : bool =
  match e with
  | Int _ -> true
  | Bool _ -> true
  | Var x -> List.mem x env (*True jeśli x w env, jeśli nie to False*)
  | Binop (_, e1, e2) -> closed_with_env env e1 && closed_with_env env e2
  | If (e1, e2, e3) ->
      closed_with_env env e1 && closed_with_env env e2 && closed_with_env env e3
  | Let (x, e1, e2) ->
      closed_with_env env e1 && closed_with_env (x :: env) e2

let closed (e : expr) : bool = 
  closed_with_env [] e