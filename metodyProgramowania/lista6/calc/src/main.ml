open Ast

let parse (s : string) : expr =
  Parser.prog Lexer.read (Lexing.from_string s)

type value =
  | VInt of int
  | VBool of bool

let modulo = fun x -> (( x mod 5) + 5) mod 5;;
let invm = fun x -> x * x * x |> modulo ;; (*a ^ (m - 2) == a ^ (-1) mod m*)

let eval_op (op : bop) (v1 : value) (v2 : value) : value =
  match op, v1, v2 with
  | Add,  VInt i1, VInt i2 -> VInt ((modulo i1) + (modulo i2) |> modulo)
  | Sub,  VInt i1, VInt i2 -> VInt ((modulo i1) - (modulo i2) |> modulo)
  | Mult, VInt i1, VInt i2 -> VInt ((modulo i1) * (modulo i2) |> modulo)
  | Div,  VInt i1, VInt i2 -> VInt (i1 / i2 |> modulo)
  | Eq,   VInt i1, VInt i2 -> VBool ((modulo i1) = (modulo i2))
  | Neq,  VInt i1, VInt i2 -> VBool ((modulo i1) <> (modulo i2))
  | Lt,   VInt i1, VInt i2 -> VBool ((modulo i1) < (modulo i2))
  | Le,   VInt i1, VInt i2 -> VBool ((modulo i1) <= (modulo i2))
  | Gt,   VInt i1, VInt i2 -> VBool ((modulo i1) > (modulo i2))
  | Ge,   VInt i1, VInt i2 -> VBool ((modulo i1) >= (modulo i2))
  | _ -> failwith "type error"

let rec eval (e : expr) : value =
  match e with
  | Int n -> VInt n
  | Bool b -> VBool b
  | If (p, t, e) ->
      (match eval p with
      | VBool true -> eval t
      | VBool false -> eval e
      | _ -> failwith "type error") 
  | Binop (op, e1, e2) -> eval_op op (eval e1) (eval e2)

let interp (s : string) : value =
  eval (parse s)

