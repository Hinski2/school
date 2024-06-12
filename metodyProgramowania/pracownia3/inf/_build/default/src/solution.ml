open Ast

(* 
      Pracownia #3 Jakub Iliński 346796 
      mój program dla większej czytelności podzieliłem na kilka sekcji
*)

(* trzymam położenie zmiennych na stosie przy użyciu mapy *)
module H = Map.Make(String)
type heap = int H.t

(* oddzielna zmienna mówiąca jak duży jest stos *)
let stack_size = ref 0

(*
################################################
    (* funkcje do obsługi zmiennych na stosie *)
lookup_var (heap : heap) (v : string) : int
assign_var (heap : heap) (v : string) (x : int) : heap
declare_var (heap : heap) (v : var) : heap
initiate_vars (var_list : var list) (cmd_list : cmd list) (heap : heap) : cmd list * heap 

*)

let lookup_var (heap : heap) (v : string) : int =
  match H.find_opt v heap with
  | Some x -> x
  | None   -> failwith ("Unbound variable " ^ v)

let assign_var (heap : heap) (v : string) (x : int) : heap =
  match H.find_opt v heap with
  | Some _ -> H.add v x heap
  | None   -> failwith ("Unbound variable " ^ v)

let declare_var (heap : heap) (v : var) : heap =
  H.add v !stack_size heap 

(* inicjalizuje odpowiednią ilość zmiennych  *)
let rec initiate_vars (var_list : var list) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  match var_list with
  | [] -> (cmd_list, heap)
  | h::t -> 
    let heap = declare_var heap h in
    stack_size := !stack_size + 1; 

    let cmd_list = cmd_list @ [ENTER 1] in
    initiate_vars t cmd_list heap

(* 
#########################################################################
    (* funkcje pomocnicze do ładowania odpowiednich rzeczy do rejestru *)
(* funkcje dla aexp *)

 (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list
process_to_acc_var (v : string) (cmd_list : cmd list) (heap : heap) : cmd list 
process_to_acc_binop (op : primop) (ae1 : aexp) (ae2 : aexp) (cmd_list : cmd list) (heap : heap) : cmd list

(* funkcje dla bexp *)
process_to_acc_b_expr (b_expr : bexp) (cmd_list : cmd list) (heap : heap) : cmd list
process_to_acc_cmp (op : cmpop) (ae1 : aexp) (ae2 :aexp) (cmd_list : cmd list) (heap : heap) : cmd list
process_to_acc_not (b_expr : bexp) (cmd_list : cmd list) (heap : heap) : cmd list
process_to_acc_and (be1 : bexp) (be2 : bexp) (cmd_list : cmd list) (heap : heap) : cmd list
process_to_acc_or (be1 : bexp) (be2 : bexp) (cmd_list : cmd list) (heap : heap) : cmd list
*)

let rec process_to_acc_var (v : string) (cmd_list : cmd list) (heap : heap) : cmd list = 
  (* bierzemy odpowiedzni adres na stosie *)
  let n = lookup_var heap v in 
  let n = !stack_size - (n + 1) in 

  (* biore odpowiednią zmieną do akumulatora *)
  cmd_list @ [TOP; LOAD n]

and process_to_acc_binop (op : primop) (ae1 : aexp) (ae2 : aexp) (cmd_list : cmd list) (heap : heap) : cmd list =
  (* obliczanie pierwszej wartości do akumulatora i wrzucanie na stos *)
  let cmd_list = process_to_acc_a_expr ae1 cmd_list heap in
  let cmd_list = cmd_list @ [PUSH] in
  stack_size := !stack_size + 1;  

  (* obliczanie drugiej wartości *)
  let cmd_list = process_to_acc_a_expr ae2 cmd_list heap in

  (* wartości są gotowe (jedna na stosie jedna w acc) można policzyc op *)
  stack_size := !stack_size - 1; (* bo PRIM siąga jedną wartość ze stosu *)
  cmd_list @ [PRIM op]

(* dodaje odpowiednie komendy po których w akumulatorze bedzie int *)
and process_to_acc_a_expr (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list = 
  match a_expr with 
  | Int x                    -> cmd_list @ [CONST x] 
  | Var v                    -> process_to_acc_var v cmd_list heap
  | Binop (op, ae1, ae2)     -> process_to_acc_binop op ae1 ae2 cmd_list heap 
  | Call (name, a_expr_list) -> process_to_acc_call name a_expr_list cmd_list heap

(* trzeba dodać konwersje bool na int i na odwrót *)
and bool_of_int (x : int) : bool = 
  if x == 0 then false else true

and int_of_bool (x : bool) : int = 
  if x == false then 0 else 1

(* dodaje odpowiednie komendy po których w akumulatorze będzie bool *)
and process_to_acc_b_expr (b_expr : bexp) (cmd_list : cmd list) (heap : heap) : cmd list =  
  match b_expr with 
  | Bool x              -> cmd_list @ [CONST (int_of_bool x)]
  | Cmp (op, ae1, ae2)  -> process_to_acc_cmp op ae1 ae2 cmd_list heap
  | And (be1, be2)      -> process_to_acc_and be1 be2 cmd_list heap
  | Or (be1, be2)       -> process_to_acc_or be1 be2 cmd_list heap
  | Not (b_expr)        -> process_to_acc_not b_expr cmd_list heap

and process_to_acc_cmp (op : cmpop) (ae1 : aexp) (ae2 : aexp) (cmd_list : cmd list) (heap : heap) : cmd list = 
  (* wyliczam ae1 do wartości *)
  let cmd_list = process_to_acc_a_expr ae1 cmd_list heap in 

  (* wrzucam je na stos *)
  let cmd_list = cmd_list @ [PUSH] in
  stack_size := !stack_size + 1;

  (* wyliczam ae2 do wartości i robie porównanie*)
  let cmd_list = process_to_acc_a_expr ae2 cmd_list heap in 
  stack_size := !stack_size - 1;
  cmd_list @ [CMP op]

and process_to_acc_not (b_expr : bexp) (cmd_list : cmd list) (heap : heap) : cmd list = 
  (* najpierw wyliczam do bool (int) *)
  let cmd_list = process_to_acc_b_expr b_expr cmd_list heap in 

  (* mam już bool (int) w akumulatore więc go neguje *)
  cmd_list @ [BRANCH ([CONST 0], [CONST 1])]

and process_to_acc_and (be1 : bexp) (be2 : bexp) (cmd_list : cmd list) (heap : heap) : cmd list =
  (* obliczenie be1 do acc *)
  let first = process_to_acc_b_expr be1 cmd_list heap in
  let second = process_to_acc_b_expr be2 [] heap in

  first @ [BRANCH(second, [CONST 0])]

and process_to_acc_or (be1 : bexp) (be2 : bexp) (cmd_list : cmd list) (heap : heap) : cmd list =
  (* obliczenie be1 do acc *)
  let first = process_to_acc_b_expr be1 cmd_list heap in
  let second = process_to_acc_b_expr be2 [] heap in

  first @ [BRANCH([CONST 1], second)]

and push_args_on_stack (a_expr_list : aexp list) (cmd_list : cmd list) (heap : heap) : cmd list = 
  match a_expr_list with 
  | [] -> cmd_list 
  | h :: t ->
    let cmd_list = process_to_acc_a_expr h cmd_list heap in
    let cmd_list = cmd_list @ [PUSH] in
    stack_size := !stack_size + 1; 
    push_args_on_stack t cmd_list heap 

and process_to_acc_call (name : string) (a_expr_list : aexp list) (cmd_list : cmd list) (heap : heap) : cmd list = 
  (* obliczenie argumentów i wrzucanie ich na stos *)
  let cmd_list = push_args_on_stack a_expr_list cmd_list heap in
    
  (* wartości są już na stosie można wywoływać funkcje *)
  let cmd_list = cmd_list @ [CALL name] in

  (* trzeba zdiąć ze stosu argumetny funkji *)
  let cmd_list = cmd_list @ [LEAVE (List.length a_expr_list)] in
  stack_size := !stack_size - (List.length a_expr_list);

  (* wartość którą zwróciła funckja jest już w akumulatorze*)
  cmd_list


(* 
##################################
    (* funkcja do obsługi state *)
handle_stm (stm : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap

    (* funkcje pomocnicze do obsługi state *)
handle_block (stms : stmt list) (cmd_list : cmd list) (heap : heap) : cmd list * heap
handle_assgn (v : string) (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list * heap
handle_if (b_expr : bexp) (stm1 : stmt) (stm2 : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap
handle_while (b_expr : bexp) (stm : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap
handle_read (v : string) (cmd_list : cmd list) (heap : heap) : cmd list * heap
handle_write (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list * heap

*)

let rec handle_stm (stm : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  match stm with 
  | Block stms              -> handle_block stms cmd_list heap 
  | Assgn (v, a_expr)       -> handle_assgn v a_expr cmd_list heap
  | If (b_expr, stm1, stm2) -> handle_if b_expr stm1 stm2 cmd_list heap
  | While (b_expr, stm)     -> handle_while b_expr stm cmd_list heap
  | Read v                  -> handle_read v cmd_list heap 
  | Write a_expr            -> handle_write a_expr cmd_list heap
  | Return a_expr           -> handle_return a_expr cmd_list heap

(* obsluga return *)
and handle_return (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list * heap =
  (* ret do cmd_list dodaje w innym miejscu po zwolnieniu zmiennych lokalnych, tutaj wyliczam wartość do rejestru *)
  (process_to_acc_a_expr a_expr cmd_list heap, heap)

(* obsługa while *)
and handle_while (b_expr : bexp) (stm : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  (* while to WHILE  of cmd list * cmd list, nie potrzebuje heap w ponirzszych wyrażeniach *)
  let while_check = process_to_acc_b_expr b_expr [] heap in 
  let (while_do, _) = handle_stm stm [] heap in 

  (cmd_list @ [WHILE(while_check, while_do)], heap)

(* obsługa if *)
and handle_if (b_expr : bexp) (stm1 : stmt) (stm2 : stmt) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  (* obliczam przypadki *)
  let (cmd_then, _) = handle_stm stm1 [] heap and (cmd_else, _) = handle_stm stm2 [] heap in 

  (* obliczam b_expr do acc i zapisuje wynik*)
  let cmd_list = process_to_acc_b_expr b_expr cmd_list heap in
  (cmd_list @ [BRANCH(cmd_then, cmd_else)], heap)


(* obsługa listy bloków *)
and handle_block (stms : stmt list) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  match stms with 
  | [] -> (cmd_list, heap)
  | h::t -> 
    let (cmd_list, heap) = handle_stm h cmd_list heap in 
    handle_block t cmd_list heap 

and handle_assgn (v : string) (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list * heap =
  (* wyznaczam miejsce zmiennej na stosie *)
  let n = lookup_var heap v in 
  let n = !stack_size - (n + 1) in 
  let cmd_list = cmd_list @ [TOP;PUSH] in
  stack_size := !stack_size + 1;

  (* sprawdzam co mam przypisać do zmiennej *)
  let cmd_list = process_to_acc_a_expr a_expr cmd_list heap in

  (* rbie przypisanie *)
  stack_size := !stack_size - 1;
  (cmd_list @ [STORE n], heap)


and handle_read (v : string) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  (* bierzemy odpowiedzni adres na stosie *)
  let n = lookup_var heap v in 
  let n = !stack_size - (n + 1) in 
  let cmd_list = cmd_list @ [TOP] in 

  (* wrzucam adres na stos i wczytuje liczbe*)
  let cmd_list = cmd_list @ [PUSH; READ] in 

  (* nadpisuje odpowiedni adres na stosie *)
  let cmd_list = cmd_list @ [STORE n] in 
  (cmd_list, heap)

and handle_write (a_expr : aexp) (cmd_list : cmd list) (heap : heap) : cmd list * heap = 
  let cmd_list = process_to_acc_a_expr a_expr cmd_list heap in 
  (cmd_list @ [WRITE], heap)

(* 
########################################
  (* funkcje do przetwarzania funkcji *)

*)
let rec process_functions (funct_list : func list) (heap : heap) =
  let rec itr funct_list heap acc = 
    match funct_list with
    | [] -> acc
    | h :: t -> itr t heap (acc @ [process_function h [] heap])
  in itr funct_list heap []

and bind_arguments (arg_list : var list) (itr : int) (heap : heap) : heap =
  match arg_list with 
  | [] -> heap 
  | h::t -> 
    let heap = H.add h (!stack_size - (itr + 1)) heap in 
    bind_arguments t (itr + 1) heap

and process_function (funct : func) (cmd_list : cmd list) (heap : heap) : name * cmd list = 
  let Func (name, arg_list, local_var_list, _ , stm) = funct in

  (* przejście się po staku i przypisanie argumentów do heap *)
  let arg_list = List.rev arg_list in 
  let heap = bind_arguments arg_list 1 heap in

  (* dodanie zmiennych lokanych *)
  let (cmd_list, heap) = initiate_vars local_var_list cmd_list heap in 

  (* tutaj powinno się dodać funkcje zagnieżdżone, ale ja pomijam tą część *)

  (* obsługa ciała *)
  let (cmd_list, _) = handle_stm stm cmd_list heap in

  (* usunięcie zmiennych lokalnych *)
  let cmd_list = cmd_list @ [LEAVE (List.length local_var_list)] in
  stack_size := !stack_size - (List.length local_var_list);
  (name, cmd_list @ [RET])

(* 
##########
    główna funkcja 
compile_prog (program : prog) : vm_prog = 

*)

let compile_prog (program : prog) : vm_prog = 
  let cmd_main = []
  and heap = H.empty in

  (* wyodrębnienie programu na 3 elementy, dla wygody i czytelności *)
  let (var_list, funct_list, stm) = program in

  (* inicjalizacja zmiennych *)
  let (cmd_main, heap) = initiate_vars var_list cmd_main heap in 

  (* inicjalizacja funkcji *)
  let cmd_funs = process_functions funct_list H.empty in 

  (* obsługa stm *)
  let (cmd_list, _) = handle_stm stm cmd_main heap in
  (cmd_list, cmd_funs)

