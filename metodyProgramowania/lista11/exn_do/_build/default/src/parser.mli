
(* The type of tokens. *)

type token = 
  | WITH
  | TRY
  | TRUE
  | TIMES
  | THEN
  | SND
  | RPAREN
  | RAISE
  | PLUS
  | OR
  | NEQ
  | MINUS
  | LT
  | LPAREN
  | LET
  | LEQ
  | INT of (int)
  | IN
  | IF
  | IDENT of (string)
  | GT
  | GEQ
  | FUN
  | FST
  | FALSE
  | EQ
  | EOF
  | ELSE
  | DIV
  | COMMA
  | ARR
  | AND

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
