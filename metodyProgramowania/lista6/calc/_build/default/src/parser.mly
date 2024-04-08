%{
open Ast
%}

%token <int> INT
%token TIMES
%token DIV
%token PLUS
%token MINUS
%token LPAREN
%token RPAREN
%token EQ
%token TRUE
%token FALSE
%token IF
%token THEN
%token ELSE
%token EOF
%token NEQ
%token LT
%token LE
%token GT
%token GE

%start <Ast.expr> prog

%nonassoc ELSE
%nonassoc EQ
%nonassoc NEQ
%nonassoc LT 
%nonassoc LE
%nonassoc GT
%nonassoc GE
%left PLUS MINUS
%left TIMES DIV

%%

prog:
  | e = expr; EOF { e }
  ;

expr:
  | i = INT { Int i }
  | e1 = expr; PLUS; e2 = expr { Binop(Add, e1, e2) }
  | e1 = expr; MINUS; e2 = expr { Binop(Sub, e1, e2) }
  | e1 = expr; DIV; e2 = expr { Binop(Div, e1, e2) }
  | e1 = expr; TIMES; e2 = expr { Binop(Mult, e1, e2) }
  | LPAREN; e = expr; RPAREN { e }
  | TRUE { Bool true }
  | FALSE { Bool false }
  | e1 = expr; EQ; e2 = expr { Binop(Eq, e1, e2) }
  | e1 = expr; NEQ; e2 = expr { Binop(Neq, e1, e2) }
  | e1 = expr; LT; e2 = expr { Binop(Lt, e1, e2) }
  | e1 = expr; LE; e2 = expr { Binop(Le, e1, e2) }
  | e1 = expr; GT; e2 = expr { Binop(Gt, e1, e2) }
  | e1 = expr; GE; e2 = expr { Binop(Ge, e1, e2) }
  | IF; e1 = expr; THEN; e2 = expr; ELSE; e3 = expr { If(e1, e2, e3) }
  ;
