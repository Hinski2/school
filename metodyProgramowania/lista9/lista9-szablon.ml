type expr =
  | Int of int
  | Add of expr * expr
  | Mult of expr * expr

let rec eval (e : expr) : int =
  match e with
  | Int n -> n
  | Add (e1, e2) -> eval e1 + eval e2
  | Mult (e1, e2) -> eval e1 * eval e2

type rpn_cmd =
  | Push of int
  | RAdd
  | RMult

type rpn = rpn_cmd list

let rec to_rpn (e : expr) : rpn =
  match e with
  | Int n -> [Push n]
  | Add (e1, e2) -> to_rpn e1 @ to_rpn e2 @ [RAdd]
  | Mult (e1, e2) -> to_rpn e1 @ to_rpn e2 @ [RMult]

let rec eval_rpn (r : rpn) (s : int list) : int =
  match r, s with
  | [], [n] -> n
  | Push n :: r', _ -> eval_rpn r' (n :: s)
  | RAdd :: r', n1 :: n2 :: s' -> eval_rpn r' (n2 + n1 :: s')
  | RMult :: r', n1 :: n2 :: s' -> eval_rpn r' (n2 * n1 :: s')
  | _,_ -> failwith "error!"

(* ZAD1 *)

(*

forall e. eval_rpn (to_rpn e) [] = eval e

*)

(* zad2 *)
let rec from_rpn (r : rpn) (s : expr list) : expr =
  match r, s with
  | [], [e] -> e
  | Push n :: r', _ -> from_rpn r' (Int n :: s)
  | RAdd :: r', e1 :: e2 :: s' -> from_rpn r' (Add (e2, e1) :: s')
  | RMult :: r', e1 :: e2 :: s' -> from_rpn r' (Mult (e2, e1) :: s')
  | _, _ -> failwith "Błąd: niepoprawna sekwencja RPN lub stos."

let rpn_expr = [Push 3; Push 4; RAdd; Push 2; RMult]
let ast_expr = from_rpn rpn_expr []
  
(* zad3 *)

(* porównaj zad 3. z listy 6. *)

let rec random_expr (max_depth : int) : expr =
  let open Random in
  if max_depth = 0 then
    Int (int 10)  (* Losowa liczba całkowita od 0 do 9 *)
  else
    match int 3 with  (* Losowanie typu operacji: 0 = Int, 1 = Add, 2 = Mult *)
    | 0 -> Int (int 10)  (* Losowa liczba całkowita od 0 do 9 *)
    | 1 -> Add (random_expr (max_depth - 1), random_expr (max_depth - 1))
    | 2 -> Mult (random_expr (max_depth - 1), random_expr (max_depth - 1))
    | _ -> failwith "Nieprawidłowe losowanie"


let rec test (max_depth : int) (sample : int) : bool =
  let rec aux n =
    if n = 0 then true
    else
      let expr = random_expr max_depth in
      let rpn_expr = to_rpn expr in
      let back_to_expr = from_rpn rpn_expr [] in
      if expr = back_to_expr then aux (n - 1)
      else false
  in
  aux sample

(* zad4 *)

let rec test_ce (max_depth : int) (sample : int) : expr option =
  let rec aux n =
    if n = 0 then None
    else
      let expr = random_expr max_depth in
      let rpn_expr = to_rpn expr in
      let back_to_expr = from_rpn rpn_expr [] in
      if expr = back_to_expr then aux (n - 1)
      else Some expr
  in
  aux sample

(*  zad5 *)

type bop = Mult | Div | Add | Sub | Eq | Lt | Gt | Leq | Geq | Neq

module T = struct

type cmd =
  | PushInt of int
  | PushBool of bool
  | Prim of bop
  | Jmp of string
  | JmpFalse of string
  | Grab
  | Access of int
  | EndLet
  | PushClo of string
  | Call of string
  | Return
  | Lbl of string

end
