(* The standard library of FUN *)

let stdlib =
  [ Ast.PVar "abs", "fun x -> if x < 0 then 0 - x else x"
  ; Ast.PVar "mod", "fun x -> fun y -> x - (x / y) * y"
  ; Ast.PVar "fix", "fun f -> (fun x -> fun y -> f (x x) y) 
                     (fun x -> fun y -> f (x x) y)"
  ; Ast.PVar "map", "fix (fun map -> fun f -> fun xs ->
      match xs with
      | Nil() -> Nil()
      | Cons(h, t) -> Cons(f h, map f t)
      end)"
  ; Ast.PVar "append", "fix (fun append -> fun xs -> fun ys ->
      match xs with
      | Nil() -> ys
      | Cons(h, t) -> Cons(h, append t ys)
      end)"
  ; Ast.PVar "insert", "fix (fun insert -> fun bst -> fun x -> 
      match bst with
      | Leaf() -> Node(x, (Leaf(), Leaf()))
      | Node(v, (left, right)) ->
        if x < v then Node(v, (insert left x, right))
        else if x > v then Node(v, (left, insert right x))
        else Node(v, (left, right))
      end)"
  ; Ast.PVar "flatten", "fix (fun flatten -> fun bst -> 
      match bst with
      | Leaf() -> Nil()
      | Node(v, (left, right)) -> append (append (flatten left) (Cons(v, Nil()))) (flatten right)
      end)"
  ; Ast.PVar "sort", "fun xs ->
      let bst_of_xs = fix(fun bst_of_xs -> fun xs -> fun bst ->
        match xs with
        | Nil() -> bst
        | Cons(h, t) -> bst_of_xs (t) (insert bst h)
      end) in
    flatten (bst_of_xs (xs) (Leaf()))"
  ; Ast.PVar "fold_left", "fix(fun fold_left -> fun f -> fun acc -> fun xs ->
        match xs with
        | Nil() -> acc
        | Cons(h, t) -> fold_left (f) (f acc h) (t)
      end)"
  ]

let parse_string str =
  Parser.prog Lexer.token (Lexing.from_string str)

let include_def (pat, str) prog =
  Ast.Let(pat, parse_string str, prog)

let include_stdlib prog =
  List.fold_right include_def stdlib prog
