open Ast

module M = Map.Make(String)

exception Type_error
exception Unbound_var of ident

exception MyExn

type env = value M.t

and value =
  | VUnit
  | VInt of int
  | VBool of bool
  | VClosure of pattern * expr * env 
  | VPair of value * value
  | VCtor of cname * value

let eval_op (op : bop) (v1 : value) (v2 : value) : value =
  match op, v1, v2 with
  | Add,  VInt i1, VInt i2 -> VInt (i1 + i2)
  | Sub,  VInt i1, VInt i2 -> VInt (i1 - i2)
  | Mult, VInt i1, VInt i2 -> VInt (i1 * i2)
  | Div,  VInt i1, VInt i2 -> VInt (i1 / i2)
  | Eq,   VInt i1, VInt i2 -> VBool (i1 = i2)
  | Lt,   VInt i1, VInt i2 -> VBool (i1 < i2)
  | Gt,   VInt i1, VInt i2 -> VBool (i1 > i2)
  | Leq,  VInt i1, VInt i2 -> VBool (i1 <= i2)
  | Geq,  VInt i1, VInt i2 -> VBool (i1 >= i2)
  | Neq,  VInt i1, VInt i2 -> VBool (i1 <> i2)
  | _ -> raise Type_error

let rec match_pattern env v p =
  match v, p with
  | _,       PWildcard  -> Some env
  | VUnit,   PUnit      -> Some env
  | _,       PUnit      -> None
  | VInt n,  PInt m when n = m -> Some env
  | _,       PInt _     -> None
  | VBool x, PBool y when x = y -> Some env
  | _,       PBool _    -> None
  | _,       PVar  x    -> Some (M.add x v env)
  | VCtor(c1, v), PCtor(c2, p) when c1 = c2 ->
    match_pattern env v p
  | _, PCtor _ -> None
  | VPair(v1, v2), PPair(p1, p2) ->
    (match match_pattern env v1 p1 with
    | None -> None
    | Some env -> match_pattern env v2 p2)
  | _, PPair _ -> None
  | _, PAs(p, x) -> 
    (match match_pattern env v p with 
    | Some env -> Some (M.add x v env)
    | None -> None)
  | _, PWhen(p, e) ->                 
    (match match_pattern env v p with
    | Some env -> if ((eval_env env e = VBool(true)))
      then Some env
      else None
    | None -> None)
  | _, PAlt(p1, p2) -> (* dodanie PAlt*)
    (match match_pattern env v p1 with 
      | Some env -> Some env
      | None -> (match match_pattern env v p2 with
        | Some env -> Some env
        | None -> None))

and check_pattern p =
  let rec aux p ids = 
    match p with
    | PWildcard | PUnit | PInt _ | PBool _ -> ids
    | PVar id -> if List.mem id ids 
      then failwith ("duplicate id " ^ id)
      else id::ids
    | PPair(p1, p2) -> 
      let new_ids = aux p1 ids in
      aux p2 new_ids
    | PCtor(_, pat) -> aux pat ids
    | PAs(_, id) ->     
      if List.mem id ids
      then failwith ("duplicate id " ^ id)
      else id::ids
    | PWhen(pat, _) -> aux pat ids
    | PAlt(p1, p2) ->
      let p1Ids = aux p1 ids and p2Ids = aux p2 ids in (* sprawdzanie czy maja takie same ids*)
      if (List.sort compare p1Ids) = (List.sort compare p2Ids)
      then p1Ids 
      else failwith("different vars") 
    in ignore(aux p [])

and add_pattern env v p =
    check_pattern p; 
    match match_pattern env v p with
    | Some env -> env
    | None -> failwith "match failure"

and eval_env (env : env) (e : expr) : value =
  match e with
  | Unit  -> VUnit
  | Int n -> VInt n
  | Bool b -> VBool b
  | Ctor(c, e) -> VCtor(c, eval_env env e)
  | If (p, t, e) ->
      (match eval_env env p with
      | VBool true -> eval_env env t
      | VBool false -> eval_env env e
      | _ -> raise Type_error)
  | Binop (And, e1, e2) ->
      (match eval_env env e1 with
      | VBool true -> eval_env env e2
      | VBool false -> VBool false
      | _ -> raise Type_error)
  | Binop (Or, e1, e2) ->
      (match eval_env env e1 with
      | VBool false -> eval_env env e2
      | VBool true -> VBool true
      | _ -> raise Type_error)
  | Binop (op, e1, e2) -> eval_op op (eval_env env e1) (eval_env env e2)
  | Let (pat, e1, e2) ->
      let r = eval_env env e1 in
      let new_env = add_pattern env r pat in 
      eval_env new_env e2
  | Var x ->
      (match M.find_opt x env with
      | Some v -> v
      | None -> raise (Unbound_var x))
  | Fun (pat, e) -> VClosure (pat, e, env)
  | App (e1, e2) ->
      (match eval_env env e1, eval_env env e2 with
      | VClosure (pat, body, clo_env), v -> eval_env (add_pattern clo_env v pat) body 
      | _, _ -> raise Type_error)
  | Pair(e1, e2) ->
      VPair(eval_env env e1, eval_env env e2)
  | Fst e ->
      (match eval_env env e with
      | VPair(v1, _) -> v1
      | _ -> raise Type_error)
  | Snd e ->
      (match eval_env env e with
      | VPair(_, v2) -> v2
      | _ -> raise Type_error)
  | Raise -> raise MyExn
  | Try(e1, e2) ->
      (try eval_env env e1 with
      | MyExn -> eval_env env e2)
  | Match(e, cs) ->
    match_clauses env (eval_env env e) cs

and match_clauses env v cs =
  match cs with
  | [] -> failwith "match failure"
  | (p, e) :: cs ->
    check_pattern p;  
    match match_pattern env v p with
    | Some env -> eval_env env e
    | None -> match_clauses env v cs

let eval_prog = eval_env M.empty

let rec string_of_value v =
  match v with
  | VUnit       -> "()"
  | VInt n      -> string_of_int n
  | VBool true  -> "true"
  | VBool false -> "false"
  | VClosure _  -> "<fun>"
  | VPair(v1, v2) -> print_VPair (v1, v2) true
  | VCtor(c, v) -> print_VCtor (c, v)

and print_VPair (v1, v2) add =
  if add then "(" ^ print_VPair (v1, v2) false ^ ")"
  else
    match v1 with
    | VPair(a, b) -> print_VPair (a, b) false ^ ", " ^ string_of_value v2
    | _ -> string_of_value v1 ^ ", " ^ string_of_value v2

and print_VCtor (c, v) =
  match v with
  | VInt n -> c ^ " " ^ string_of_int n 
  | VBool true -> c ^ " true"
  | VBool false -> c ^ " false"
  | VClosure _ -> c ^ " <fun>"
  | VCtor(_, _) -> c ^ "(" ^ string_of_value v ^  ")"
  | _ -> c ^ string_of_value v

let print_value v =
  print_endline (string_of_value v)
