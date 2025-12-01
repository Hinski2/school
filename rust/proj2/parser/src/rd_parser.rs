use lexer::token::Token;
use std::{collections::LinkedList};
use crate::{pc_parser::parse_expr};
use super::grammar::{Stmt, Block, Program, List, Arg, Item};

pub fn parse_program(tokens: &mut LinkedList<Token>) -> Result<Program, Box<dyn std::error::Error>> {
    let mut line_no: usize = 1;
    let mut program = Program{ body: LinkedList::new() };

    loop {
        while tokens.front() == Some(&Token::EOL) {
            line_no += 1;
            tokens.pop_front();
        }

        match tokens.front() {
            Some(Token::EOF) => break,
            Some(_) => program.body.push_back(parse_stmt(tokens, &mut line_no)?),
            None => return Err(format!("parser error in line {} : insufficient ammount of tokens", line_no).into()),
        }
    }

    Ok(program)
}

pub fn parse_list(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<List, Box<dyn std::error::Error>> {
    // consume [ token
    tokens.pop_front();

    let mut items: LinkedList<Item> = LinkedList::new();

    loop {
        match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::LROUNDBRACKET) | Some(Token::VARREF(_)) => {
                items.push_back(Item::EXPR(parse_expr(tokens)?));
            },
            Some(Token::VARNAME(name)) => {
                items.push_back(Item::VARNAME(name.to_string()));
                tokens.pop_front();
            },
            Some(Token::COLOR(c)) => {
                items.push_back(Item::COLOR(c.clone()));
                tokens.pop_front();
            }
            Some(Token::LSQUAREDBRACKET) => items.push_back(Item::LIST(parse_list(tokens, line_no)?)),
            Some(Token::RSQUAREDBRACKET) => break,
            Some(t) => return Err(format!("parser error in line {}: expected list item, recieved: {:#?}", line_no, t).into()),
            None => return Err(format!("parser error in line {}: insufficient ammoutn of tokens, expected list item", line_no).into()),
        }
    }

    // consume ] token
    tokens.pop_front();
    Ok(List { items })
}

pub fn parse_arg(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Arg, Box<dyn std::error::Error>> {
    match tokens.front() {
        Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::LROUNDBRACKET) | Some(Token::VARREF(_)) => {
            Ok( Arg::EXPR(parse_expr(tokens)?))
        },
        Some(Token::VARNAME(name)) => {
            let name = name.to_string();
            tokens.pop_front();
            Ok( Arg::VARNAME(name) )
        },
        Some(Token::PROCEDUREID(name)) => {
            let name = name.to_string();
            tokens.pop_front();
            Ok( Arg::PROCEDUREID(name) )
        } 
        Some(Token::LSQUAREDBRACKET) => {
            Ok( Arg::LIST(parse_list(tokens, line_no)?))
        }
        Some(t) => Err(format!("parser error in line {}: expected argument, recieived: {:#?}", line_no, t).into()),
        None => Err(format!("parser error in line {}: insufficient ammount of tokens, expected argumetn", line_no).into()),
    }
}

// parse Stmt
pub fn parse_stmt(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
    fn parse_procedure_def(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume Token::Begin
        tokens.pop_front();

        while tokens.front() == Some(&Token::EOL) {
            tokens.pop_front();
            *line_no += 1;
        }
        
        let id = match tokens.pop_front() {
            Some(Token::PROCEDUREID(id)) => id, 
            Some(t) => return Err(format!("parser error in line {} : expected procedure id, received: {:#?}", line_no, t).into()),
            None => return Err(format!("parse error in line {} : insufficient ammount of tokens, expected procedure id", line_no).into()),
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
                    *line_no += 1;
                },
                _ => break,
            }
        }

        let mut content: LinkedList<Stmt> = LinkedList::new();
        loop {
            while tokens.front() == Some(&Token::EOL) {
                tokens.pop_front();
                *line_no += 1;
            }

            match tokens.front() {
                Some(Token::END) => break,
                Some(_) => content.push_back(parse_stmt(tokens, line_no)?),
                None => return Err(format!("parser error in line {} : error while parsing procedure", line_no).into()),
            } 
        } 

        // consume Token::End
        tokens.pop_front();
        Ok(Stmt::PROCEDUREDEF{ id, args, content })
    }

    fn parse_procedure_call(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
        let id = match tokens.pop_front() {
            Some(Token::PROCEDUREID(id)) => id, 
            Some(t) => return Err(format!("parser error in line {}: expected procedure id, received: {:#?}", line_no, t).into()),
            None => return Err(format!("parse error in line {}: insufficient ammount of tokens, expected procedure id", line_no).into()),
        };

        let mut args: LinkedList<Arg> = LinkedList::new();
        loop {
            match tokens.front() {
                Some(Token::EOL) => {
                    *line_no += 1;
                    break;
                },
                Some(Token::RSQUAREDBRACKET) => break,
                Some(_) => args.push_back(parse_arg(tokens, line_no)?),
                None => return Err(format!("parser error in line {}: insufficient ammoutn of tokens, expected functions argumet", line_no).into()),
            }
        }

        Ok(Stmt::PROCEDURECALL { id, args })
    }

    fn parse_procedure_if_stmt(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume if token
        tokens.pop_front();
        let cond = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error in line {} : expected expr token, received {:#?}", line_no, t).into()),
            None => return Err(format!("parser error in line {} : insufficient ammount of tokens, expected expr token", line_no).into()),
        };

        let body = parse_block(tokens, line_no)?;
        return Ok(Stmt::IFSTMT { cond, body } )
    }

    fn parse_procedure_ifelse_stmt(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume ifelse token
        tokens.pop_front();
        let cond = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error in line {} : expected expr token, received {:#?}", line_no, t).into()),
            None => return Err(format!("parser error in line {} : insufficient ammount of tokens, expected expr token", line_no).into()),
        };

        let body1 = parse_block(tokens, line_no)?;
        let body2 = parse_block(tokens, line_no)?;

        return Ok(Stmt::IFELSE {cond, body1, body2} )
    }

    fn parse_procedure_repeat_stmt(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Stmt, Box<dyn std::error::Error>> {
        // consume repeat token
        tokens.pop_front();
        let repeat_no = match tokens.front() {
            Some(Token::INT(_)) | Some(Token::FLOAT(_)) | Some(Token::VARREF(_)) => parse_expr(tokens)?,
            Some(t) => return Err(format!("parser error in line {} : expected expr token, received {:#?}", line_no, t).into()),
            None => return Err(format!("parser error in line {} : insufficient ammount of tokens, expected expr token", line_no).into()),
        };

        let body = parse_block(tokens, line_no)?;
        return Ok(Stmt::REPEATSTMT{ repeat_no, body })
    }


    while tokens.front() == Some(&Token::EOL) {
        tokens.pop_front();
        *line_no += 1;
    }

    match tokens.front() {
        Some(Token::BEGIN) => Ok(parse_procedure_def(tokens, line_no)?),
        Some(Token::PROCEDUREID(_)) => Ok(parse_procedure_call(tokens, line_no)?),
        Some(Token::IF) => Ok(parse_procedure_if_stmt(tokens, line_no)?),
        Some(Token::IFELSE) => Ok(parse_procedure_ifelse_stmt(tokens, line_no)?),
        Some(Token::REPEAT) => Ok(parse_procedure_repeat_stmt(tokens, line_no)?),
        Some(t) => Err(format!("parser error in line {} : expected Stmt begin token, received {:#?}", line_no, t).into()),
        None => Err(format!("parse error in line {} : insufficient ammount of tokens, expecteds Stmt begin token", line_no).into()),
    }
}

// parse Block
pub fn parse_block(tokens: &mut LinkedList<Token>, line_no: &mut usize) -> Result<Block, Box<dyn std::error::Error>> {
    match tokens.pop_front() {
        Some(Token::LSQUAREDBRACKET) => (),
        Some(t) => return Err(format!("parser error in line {} : : expected [ token, received {:#?}", line_no, t).into()),
        None => return Err(format!("parser error in line {} : insufficient ammount of tokens, expected [ token", line_no).into()),
    };

    let mut block = Block { stmts: LinkedList::new() };
    loop {
        while tokens.front() == Some(&Token::EOL) {
            tokens.pop_front();
            *line_no += 1;
        }

        match tokens.front() {
            Some(Token::RSQUAREDBRACKET) => break,
            Some(_) => block.stmts.push_back(parse_stmt(tokens, line_no)?),
            None => return Err(format!("parser error in line {} : insufficient ammount of tokens, expected ] token", line_no).into()),
        }
    }

    // we need to consume ] token
    tokens.pop_front();

    Ok(block)
}