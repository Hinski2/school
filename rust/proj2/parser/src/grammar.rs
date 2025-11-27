/*
    <expr> ::= 
        | numb
        | <varref>
        | <expr> <op> <expr>

    <procedure-def> ::= to <procedureid>  <varname>* <stmt>* end
    <procedure-call> ::= <procedureid> <expr>*

    <stmt> ::= 
        | <procedure-def>
        | <procedure-call> 
        | if <expr> <block>
        | ifelse <expr> <block> <block>
        | repeat <expr> <block>

    <block> := [ <stmt>* ]
    
    <program> ::= <stmt>*
*/

use std::collections::LinkedList;

// expr
#[derive(Debug, PartialEq)]
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

#[derive(Debug, PartialEq)]
pub enum UnOp {
    NOT,    // NOT
}

#[derive(Debug, PartialEq)]
pub enum Expr {
    INT(i64),
    FLOAT(f64),
    VARREF(String),

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

// stmt
#[derive(Debug, PartialEq)]
pub enum Stmt {
    PROCEDUREDEF {
        id: String,
        args: LinkedList<String>,
        content: LinkedList<Stmt>,
    },
    PROCEDURECALL {
        id: String,
        args: LinkedList<Expr>,
    },
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
}

#[derive(Debug)]
pub struct RepeatStmt {
    pub repeat_no: Expr, 
    pub body: Block,
}

// block
#[derive(Debug, PartialEq)]
pub struct Block {
    pub stmts: LinkedList<Stmt>,
}

// program 
#[derive(Debug)]
pub struct Program {
    pub body: LinkedList<Stmt>
}