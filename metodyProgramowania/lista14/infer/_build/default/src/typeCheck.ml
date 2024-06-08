open Ast

module M = Map.Make(String)

type env = tp M.t

let env_empty = M.empty
let env_add env x tp = M.add x tp env
let env_lookup env x = M.find_opt x env

let rec occurs x (tp : tp) =
  match tp_view tp with
  | TUVar y -> uvar_equal x y
  | TInt | TBool | TUnit -> false
  | TArr(tp1, tp2) ->
    occurs x tp1 || occurs x tp2

let rec unify_type tp1 tp2 =
  match tp_view tp1, tp_view tp2 with
  | TUVar x, TUVar y when uvar_equal x y -> ()
  | TUVar x, _ ->
    if occurs x tp2 then failwith "unification error"
    else set_uvar x tp2
  | _, TUVar x ->
    if occurs x tp1 then failwith "unification error"
    else set_uvar x tp1
  | TInt, TInt -> ()
  | TInt, _    -> failwith "unification error"
  | TBool, TBool -> ()
  | TBool, _    -> failwith "unification error"
  | TUnit, TUnit -> ()
  | TUnit, _    -> failwith "unification error"
  | TArr(ta1, tb1), TArr(ta2, tb2) ->
    unify_type ta1 ta2;
    unify_type tb1 tb2
  | TArr _, _    -> failwith "unification error"

let rec infer_type env (e : expr) =
  match e with
  | Unit   -> t_unit
  | Int  _ -> t_int
  | Bool _ -> t_bool
  | Var  x ->
    (match env_lookup env x with
    | Some tp -> tp
    | None    -> failwith ("Unbound variable " ^ x))
  | Let (x, e1, e2) ->
    let tp = infer_type env e1 in
    infer_type (env_add env x tp) e2
  | Fun (x, tp1, e) ->
    t_arr tp1 (infer_type (env_add env x tp1) e)
  | App (e1, e2) ->
    (match tp_view (infer_type env e1) with
    | TArr(tp', tp) ->
      check_type env e2 tp';
      tp
    | TUVar r ->
      let tp' = fresh_uvar () in
      let tp  = fresh_uvar () in
      set_uvar r (t_arr tp' tp);
      check_type env e2 tp';
      tp
    | _ -> failwith "type error")

and check_type env e tp =
  let tp' = infer_type env e in
  unify_type tp tp'

let check_program p =
  let _ : tp = infer_type env_empty p in
  p
