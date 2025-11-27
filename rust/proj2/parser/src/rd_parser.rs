use lexer::token::Token;
use std::collections::LinkedList;
use crate::{grammar::Expr, pc_parser::parse_expr};
use super::grammar::{Stmt, Block, Program};

pub fn parse_program(tokens: &mut LinkedList<Token>) -> Result<Program, Box<dyn std::error::Error>> {
    let mut program = Program{ body: LinkedList::new() };
    loop {
        while tokens.front() == Some(&Token::EOL) {
            tokens.pop_front();
        }

        match tokens.front() {
            Some(Token::EOF) => break,
            Some(_) => program.body.push_back(parse_stmt(tokens)?),
            None => return Err(format!("parser error: insufficient ammount of tokens").into()),
        }
    }

    Ok(program)
}

// parse Stmt
pub fn parse_stmt(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
    fn parse_procedure_def(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume Token::Begin
        tokens.pop_front();

        while tokens.front() == Some(&Token::EOL) {
            tokens.pop_front();
        }
        
        let id = match tokens.pop_front() {
            Some(Token::PROCEDUREID(id)) => id, 
            Some(t) => return Err(format!("parser error: expected procedure id, received: {:#?}", t).into()),
            None => return Err(format!("parse error: insufficient ammount of tokens, expected procedure id").into()),
        };

        let mut args: LinkedList<String> = LinkedList::new();
        loop {
            match tokens.front() {
                Some(Token::VARREF(name))=> {
                    args.push_back(name.clone());
                    tokens.pop_front();
                }
                Some(Token::EOL) => {
                    tokens.pop_front();
                },
                _ => break,
            }
        }

        let mut content: LinkedList<Stmt> = LinkedList::new();
        loop {
            while tokens.front() == Some(&Token::EOL) {
                tokens.pop_front();
            }

            match tokens.front() {
                Some(Token::END) => break,
                Some(_) => content.push_back(parse_stmt(tokens)?),
                None => return Err(format!("parser error: error while parsing procedure").into()),
            } 
        } 

        // consume Token::End
        tokens.pop_front();
        Ok(Stmt::PROCEDUREDEF{ id, args, content })
    }

    fn parse_procedure_call(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
        let id = match tokens.pop_front() {
            Some(Token::PROCEDUREID(id)) => id, 
            Some(t) => return Err(format!("parser error: expected procedure id, received: {:#?}", t).into()),
            None => return Err(format!("parse error: insufficient ammount of tokens, expected procedure id").into()),
        };

        let mut args: LinkedList<Expr> = LinkedList::new();
        loop {
            match tokens.front() {
                Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => args.push_back(parse_expr(tokens)?),
                _ => break,
            }
        }

        Ok(Stmt::PROCEDURECALL { id, args })
    }

    fn parse_procedure_if_stmt(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume if token
        tokens.pop_front();
        let cond = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error: expected expr token, received {:#?}", t).into()),
            None => return Err(format!("parser error: insufficient ammount of tokens, expected expr token").into()),
        };

        let body = parse_block(tokens)?;
        return Ok(Stmt::IFSTMT { cond, body } )
    }

    fn parse_procedure_ifelse_stmt(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume ifelse token
        tokens.pop_front();
        let cond = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error: expected expr token, received {:#?}", t).into()),
            None => return Err(format!("parser error: insufficient ammount of tokens, expected expr token").into()),
        };

        let body1 = parse_block(tokens)?;
        let body2 = parse_block(tokens)?;

        return Ok(Stmt::IFELSE {cond, body1, body2} )
    }

    fn parse_procedure_repeat_stmt(tokens: &mut LinkedList<Token>) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume repeat token
        tokens.pop_front();
        let repeat_no = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error: expected expr token, received {:#?}", t).into()),
            None => return Err(format!("parser error: insufficient ammount of tokens, expected expr token").into()),
        };

        let body = parse_block(tokens)?;
        return Ok(Stmt::REPEATSTMT{ repeat_no, body })
    }


    while tokens.front() == Some(&Token::EOL) {
        tokens.pop_front();
    }

    match tokens.front() {
        Some(Token::BEGIN) => Ok(parse_procedure_def(tokens)?),
        Some(Token::PROCEDUREID(_)) => Ok(parse_procedure_call(tokens)?),
        Some(Token::IF) => Ok(parse_procedure_if_stmt(tokens)?),
        Some(Token::IFELSE) => Ok(parse_procedure_ifelse_stmt(tokens)?),
        Some(Token::REPEAT) => Ok(parse_procedure_repeat_stmt(tokens)?),
        Some(t) => Err(format!("parser error: expected Stmt begin token, received {:#?}", t).into()),
        None => Err(format!("parse error: insufficient ammount of tokens, expecteds Stmt begin token").into()),
    }
}

// parse Block
pub fn parse_block(tokens: &mut LinkedList<Token>) -> Result<Block, Box<dyn std::error::Error>> {
    match tokens.pop_front() {
        Some(Token::LSQUAREDBRACKET) => (),
        Some(t) => return Err(format!("parser error: expected [ token, received {:#?}", t).into()),
        None => return Err(format!("parser error: insufficient ammount of tokens, expected [ token").into()),
    };

    let mut block = Block { stmts: LinkedList::new() };
    loop {
        while tokens.front() == Some(&Token::EOL) {
            tokens.pop_front();
        }

        match tokens.front() {
            Some(Token::RSQUAREDBRACKET) => break,
            Some(_) => block.stmts.push_back(parse_stmt(tokens)?),
            None => return Err(format!("parser error: insufficient ammount of tokens, expected ] token").into()),
        }
    }

    // we need to consume ] token
    tokens.pop_front();

    Ok(block)
}