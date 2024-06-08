open Ast

module M = Map.Make(String)

type env = tp M.t

let env_empty = M.empty
let env_add env x tp = M.add x tp env
let env_lookup env x = M.find_opt x env

let rec infer_type env (e : expr) =
  match e with
  | Unit   -> TUnit
  | Int  _ -> TInt
  | Bool _ -> TBool
  | Var  x ->
    (match env_lookup env x with
    | Some tp -> tp
    | None    -> failwith ("Unbound variable " ^ x))
  | Let (x, e1, e2) ->
    let tp = infer_type env e1 in
    infer_type (env_add env x tp) e2
  | Fun (x, tp1, e) ->
    TArr(tp1, infer_type (env_add env x tp1) e)
  | App (e1, e2) ->
    (match infer_type env e1 with
    | TArr(tp', tp) ->
      check_type env e2 tp';
      tp
    | _ -> failwith "type error")
  | Binop (bop, e1, e2) ->  (* implementacja Binop *)
    infer_type_Binop env bop e1 e2
  | If (e1, e2, e3) ->  (* implementacja if *)
    let t1 = infer_type env e1 in 
    (match t1 with 
    | TBool ->
      let t2 = infer_type env e2 and t3 = infer_type env e3 in 
      if t2 = t3 then t2 else failwith "type error"
    | _ -> failwith "type error")
  | Pair (e1, e2) ->  (* implementacja pary oraz fst i snd *)
    TArr (infer_type env e1, infer_type env e2)
  | Fst e ->
      (match e with
      | Pair (e1, _) -> infer_type env e1
      | _ -> failwith "type error")
  | Snd e ->
      (match e with
      | Pair (_, e2) -> infer_type env e2
      | _ -> failwith "type error")

and infer_type_Binop env bop e1 e2 =
  let t1 = infer_type env e1 and t2 = infer_type env e2 in 
  match t1, t2 with 
  | TInt, TInt -> (match bop with
    | Add | Sub | Mult | Div -> TInt 
    | Eq | Lt | Gt | Leq | Geq | Neq | And | Or -> TBool)
  | TBool, TBool -> (match bop with
    | Eq | Lt | Gt | Leq | Geq | Neq | And | Or -> TBool
    | _ -> failwith "type error")
  | _, _ -> failwith "type error"

and check_type env e tp =
  let tp' = infer_type env e in
  if tp = tp' then ()
  else
    failwith "type error"

let check_program p =
  let _ : tp = infer_type env_empty p in
  p
