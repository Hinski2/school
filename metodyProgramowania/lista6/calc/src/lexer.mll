{
open Parser
}

let white = [' ' '\t']+
let digit = ['0'-'9']
let number = '-'? digit+

rule read =
  parse
  | white { read lexbuf }
  | "=" { EQ }
  | "true" { TRUE }
  | "false" { FALSE }
  | "if" { IF }
  | "then" { THEN }
  | "else" { ELSE }
  | "*" { TIMES }
  | "+" { PLUS }
  | "-" { MINUS }
  | "/" { DIV }
  | "(" { LPAREN }
  | ")" { RPAREN }
  | ">" { GT }
  | ">=" { GE }
  | "<" { LT }
  | "<=" { LE }
  | "<>" { NEQ }
  | number { INT (int_of_string (Lexing.lexeme lexbuf)) } 
  | eof { EOF }
