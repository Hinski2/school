open Ast

module H = Map.Make(String)

type heap = int H.t

let lookup_var heap x =
  match H.find_opt x heap with
  | Some v -> v
  | None   -> failwith ("Unbound variable " ^ x)

let assign_var heap x v =
  match H.find_opt x heap with
  | Some _ -> H.add x v heap
  | None   -> failwith ("Unbound variable " ^ x)

let declare_var heap x : heap =
  H.add x 0 heap

let eval_binop op =
  match op with
  | Mul -> ( * )
  | Div -> ( / )
  | Add -> ( + )
  | Sub -> ( - )

let rec eval_aexp heap e =
  match e with
  | Int n -> n
  | Var x -> lookup_var heap x
  | Binop(op, e1, e2) ->
    eval_binop op (eval_aexp heap e1) (eval_aexp heap e2)

let eval_cmpop op =
  match op with
  | Eq  -> ( = )
  | Neq -> ( <> )
  | Lt  -> ( < )
  | Gt  -> ( > )
  | Leq -> ( <= )
  | Geq -> ( >= )

let rec eval_bexp heap e =
  match e with
  | Bool b -> b
  | Cmp(op, e1, e2) ->
    eval_cmpop op (eval_aexp heap e1) (eval_aexp heap e2)
  | And(e1, e2) ->
    eval_bexp heap e1 && eval_bexp heap e2
  | Or(e1, e2) ->
    eval_bexp heap e1 || eval_bexp heap e2
  | Not e -> not (eval_bexp heap e)

let rec eval_stmt heap s =
  match s with
  | Block ss    -> List.fold_left eval_stmt heap ss
  | Assgn(x, e) -> assign_var heap x (eval_aexp heap e)
  | If(e, s1, s2) ->
    if eval_bexp heap e then eval_stmt heap s1
    else eval_stmt heap s2
  | While(e, s) ->
    eval_while heap e s
  | Read x ->
    read_line () |> int_of_string |> assign_var heap x
  | Write e ->
    eval_aexp heap e |> string_of_int |> print_endline;
    heap

and eval_while heap e s =
  if eval_bexp heap e then
    eval_while (eval_stmt heap s) e s
  else
    heap

let run_prog (xs, stmt) =
  let heap = List.fold_left declare_var H.empty xs in
  let _ : heap = eval_stmt heap stmt in
  ()
