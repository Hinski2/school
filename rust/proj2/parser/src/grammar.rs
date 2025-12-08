/*
    <expr> ::= 
        | numb
        | <varref>
        | <repcount>
        | <expr> <op> <expr>

    <item> := 
        | <expr> 
        | <varname>
        | <color>
        | <list>

    <returnable> :=
        | <item> 
        | <procedure-call>
    
    <list> ::= [ <item>* ]

    <procedure-def> ::= to <PROCEDURECALL>  <varref>* <stmt>* end
    <procedure-call> ::= <PROCEDURECALL> <item>*

    <stmt> ::= 
        | <procedure-def>
        | <procedure-call> 
        | if <expr> <block>
        | ifelse <expr> <block> <block>
        | repeat <expr> <block>
        | output <returnable>
        | stop
        | make <varname> <returnable>

    <block> := [ <stmt>* ]
    
    <program> ::= <stmt>*
*/

use std::{collections::LinkedList};
use turtlelib::color::Color;

// expr
#[derive(Debug, PartialEq, Clone)]
pub enum BinOp {
    ADD,    // + 
    SUB,    // -
    MULT,   // *
    DIV,    // / 
    MOD,    // %

    EQP,    // =
    NEQP,   // <>
    GEQP,   // >=
    LEQP,   // <= 
    GTP,    // > 
    LTP,    // <

    AND,    // AND
    OR,     // OR
}

#[derive(Debug, PartialEq, Clone)]
pub enum UnOp {
    NOT,    // NOT
}

#[derive(Debug, PartialEq, Clone)]
pub enum Expr {
    INT(i64),
    FLOAT(f64),
    VARREF(String),
    REPCOUNT,

    BINARY {
        e1: Box<Expr>,
        op: BinOp,
        e2: Box<Expr>,
    },

    UNARY {
        op: UnOp,
        e1: Box<Expr> 
    }
}

#[derive(Debug, PartialEq, Clone)]
pub enum Returnable {
    ITEM(Item),
    PROCEDURECALL(ProcedureCall),
}

#[derive(Debug, PartialEq, Clone)]
pub struct ProcedureCall {
    pub id: String,
    pub args: LinkedList<Item>,
}

// list
#[derive(Debug, PartialEq, Clone)]
pub struct List {
    pub items: LinkedList<Item>,
}

// item 
#[derive(Debug, PartialEq, Clone)]
pub enum Item {
    EXPR(Expr),
    VARNAME(String),
    COLOR(Color),
    LIST(List),
}

// stmt
#[derive(Debug, PartialEq, Clone)]
pub enum Stmt {
    PROCEDUREDEF {
        id: String,
        args: LinkedList<String>,
        content: LinkedList<Stmt>,
    },
    PROCEDURECALL(ProcedureCall),
    IFSTMT {
        cond: Expr,
        body: Block,
    },
    IFELSE {
        cond: Expr,
        body1: Block,
        body2: Block,
    },
    REPEATSTMT {
        repeat_no: Expr, 
        body: Block,
    },
    OUTPUT(Returnable),
    STOP,
    MAKE {
        name: String, 
        val: Returnable,
    }
}

#[derive(Debug)]
pub struct RepeatStmt {
    pub repeat_no: Expr, 
    pub body: Block,
}

// block
#[derive(Debug, PartialEq, Clone)]
pub struct Block {
    pub stmts: LinkedList<Stmt>,
}

// program 
#[derive(Debug)]
pub struct Program {
    pub body: LinkedList<Stmt>
}
