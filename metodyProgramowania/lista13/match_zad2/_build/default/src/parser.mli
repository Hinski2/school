
(* The type of tokens. *)

type token = 
  | WITH
  | UNDERSCORE
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
  | MATCH
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
  | END
  | ELSE
  | DIV
  | COMMA
  | CNAME of (string)
  | BAR
  | AS
  | ARR
  | AND

(* This exception is raised by the monolithic API functions. *)

exception Error

(* The monolithic API. *)

val prog: (Lexing.lexbuf -> token) -> Lexing.lexbuf -> (Ast.expr)
