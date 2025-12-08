// precedence Climbing Parser

use std::{collections::LinkedList};
use lexer::token::Token;
use crate::grammar::{BinOp, Expr, UnOp};

#[derive(PartialEq)]
pub enum Assoc {
    Left, 
    Right,
}

pub enum Op {
    BINARY(BinOp),
    UNARY(UnOp),
}

pub struct OpInfo {
    pub precedence: usize, 
    pub assoc: Assoc,
    pub op: Op,
}

pub fn get_op_info(token: &Token) -> Result<OpInfo, Box<dyn std::error::Error>> {
    match token {
        Token::OR    => Ok(OpInfo { precedence: 1, assoc: Assoc::Left, op: Op::BINARY(BinOp::OR) }),
        Token::AND   => Ok(OpInfo { precedence: 2, assoc: Assoc::Left, op: Op::BINARY(BinOp::AND) }),

        Token::EQP   => Ok(OpInfo { precedence: 3, assoc: Assoc::Left, op: Op::BINARY(BinOp::EQP) }),
        Token::NEQP  => Ok(OpInfo { precedence: 3, assoc: Assoc::Left, op: Op::BINARY(BinOp::NEQP) }),
        
        Token::LTP   => Ok(OpInfo { precedence: 4, assoc: Assoc::Left, op: Op::BINARY(BinOp::LTP) }),
        Token::LEQP  => Ok(OpInfo { precedence: 4, assoc: Assoc::Left, op: Op::BINARY(BinOp::LEQP) }),
        Token::GTP   => Ok(OpInfo { precedence: 4, assoc: Assoc::Left, op: Op::BINARY(BinOp::GTP) }),
        Token::GEQP  => Ok(OpInfo { precedence: 4, assoc: Assoc::Left, op: Op::BINARY(BinOp::GEQP) }),

        Token::ADD   => Ok(OpInfo { precedence: 5, assoc: Assoc::Left, op: Op::BINARY(BinOp::ADD) }),
        Token::SUB   => Ok(OpInfo { precedence: 5, assoc: Assoc::Left, op: Op::BINARY(BinOp::SUB) }),

        Token::MULT  => Ok(OpInfo { precedence: 6, assoc: Assoc::Left, op: Op::BINARY(BinOp::MULT) }),
        Token::DIV   => Ok(OpInfo { precedence: 6, assoc: Assoc::Left, op: Op::BINARY(BinOp::DIV) }),
        Token::MOD   => Ok(OpInfo { precedence: 6, assoc: Assoc::Left, op: Op::BINARY(BinOp::MOD) }),

        Token::NOT   => Ok(OpInfo { precedence: 7, assoc: Assoc::Right, op: Op::UNARY(UnOp::NOT) }),

        _ => Err(format!("parser error: inapropriate token: {:#?}", token).into()),
    }
}

pub fn parse_expr(tokens: &mut LinkedList<Token>) -> Result<Expr, Box<dyn std::error::Error>> {
    let lhs = parse_primary(tokens)?;
    let res = parse_expr_1(tokens, lhs, 0)?;

    Ok(res)
}

pub fn parse_expr_1(tokens: &mut LinkedList<Token>, mut lhs: Expr, min_precedence: usize) -> Result<Expr, Box<dyn std::error::Error>> { 
    loop {
        let lookahead_token = match tokens.front() {
            Some(t) => t,
            None => break, // no more tokens
        };

        let op_info = match get_op_info(lookahead_token) {
            Ok(x) => x, 
            Err(_) => break,
        };

        if op_info.precedence < min_precedence {
            break;
        }

        let bin_op = match op_info.op {
            Op::BINARY(b) => b,
            Op::UNARY(_) => break,
        };

        tokens.pop_front();
        let mut rhs = parse_primary(tokens)?;

        loop {
            let next_look = match tokens.front() {
                Some(t) => t,
                None => break,
            };

            let next_op_info = match get_op_info(next_look) {
                Ok(x) => x, 
                Err(_) => break,
            };

            let higher_precedence = next_op_info.precedence > op_info.precedence;
            let right_assoc_and_equal = next_op_info.precedence == op_info.precedence && next_op_info.assoc == Assoc::Right;

            if !higher_precedence && !right_assoc_and_equal {
                break;
            }

            let new_min_precedence = op_info.precedence + if higher_precedence {1} else {0};
            rhs = parse_expr_1(tokens, rhs, new_min_precedence)?;
        }

        let new_lhs = Expr::BINARY { 
            e1: Box::new(lhs),
            op: bin_op,
            e2: Box::new(rhs), 
        };

        lhs = new_lhs;
    }
    Ok(lhs)
}

pub fn parse_atom(token: Token) -> Result<Expr, Box<dyn std::error::Error>> {
    match token {
        Token::INT(x) => Ok(Expr::INT(x)),
        Token::FLOAT(x) => Ok(Expr::FLOAT(x)),
        Token::VARREF(x) => Ok(Expr::VARREF(x)),
        Token::REPCOUNT => Ok(Expr::REPCOUNT),
        _ => Err(format!("parser error: innapropriate token: {:#?}, expected atomic token", token).into()),
    }
}

pub fn parse_primary(tokens: &mut LinkedList<Token>) -> Result<Expr, Box<dyn std::error::Error>> {
    let token = tokens.pop_front().ok_or("parser error: insufficient ammount of tokens")?;
    match token {
        Token::INT(_) | Token::FLOAT(_) | Token::VARREF(_) | Token::REPCOUNT => parse_atom(token),
        Token::NOT => {
            let e = parse_primary(tokens)?;
            Ok(Expr::UNARY {
                op: UnOp::NOT,
                e1: Box::new(e), 
            })
        }
        Token::LSQUAREDBRACKET => {
           let e = parse_expr(tokens)?;
           let t2 = tokens.pop_front().ok_or("parser error: insufficient ammount of tokens, expected ) token")?;

            if t2 != Token::RSQUAREDBRACKET {
                Err(format!("parser error: innapropriate token {:#?}, expected ] token", token).into())
            } else {
                Ok(e)
            }
        }
        _ => Err(format!("parser error: innapropriate token: {:#?}, expected primary token", token).into()),
    }
}