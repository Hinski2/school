
(* The type of tokens. *)

type token = 
  | TRUE
  | TIMES
  | THEN
  | RPAREN
  | PLUS
  | MINUS
  | LPAREN
  | INT of (int)
  | IF
  | FALSE
  | EQ
  | EOF
  | ELSE
  | DIV

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
