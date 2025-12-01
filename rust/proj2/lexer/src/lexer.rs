use super::token::{Token, TokenDictionary};
use std::{collections::LinkedList, fs::File, io::{BufRead, BufReader}};

pub fn lexer(line: String, token_dictionary: &TokenDictionary) -> Result<LinkedList<Token>, Box<dyn std::error::Error>> {
    let chars: Vec<char> = line.chars().collect();
    let mut i = 0;
    let mut tokens: LinkedList<Token> = LinkedList::new();

    while i < chars.len() {
        if chars[i].is_whitespace() {
            i += 1;
            continue;
        }

        if let Some((t, l)) = token_dictionary.try_match_keyword(&chars[i..]) {
            tokens.push_back(t);
            i += l;
        } else if let Some((t, l)) = token_dictionary.try_match_value(&chars[i..]) {
            tokens.push_back(t);
            i += l;
        } else if let Some((t, l)) = token_dictionary.try_match_ident(&chars[i..]) {
            tokens.push_back(t);
            i += l;
        } else {
            return Err(format!("lexer error: found unknown token in line: {}", line).into())    
        }
    }

    tokens.push_back(Token::EOL);

    Ok(tokens)
}

pub fn tokenize_file(file_path: String) -> Result<LinkedList<Token>, Box<dyn std::error::Error>> {
    let file = File::open(file_path)?;
    let reader = BufReader::new(file);
    let mut tokens = LinkedList::new();

    let token_dictionary = TokenDictionary::new();
    for line in reader.lines() {
        tokens.append(&mut lexer(line?, &token_dictionary)?);
    }

    tokens.push_back(Token::EOF);
    return Ok(tokens);
}

pub fn tokenize_code(code: String) -> Result<LinkedList<Token>, Box<dyn std::error::Error>> {
    let mut tokens = LinkedList::new();
    let token_dictionary = TokenDictionary::new();

    for line in code.lines() {
        tokens.append(&mut lexer(line.to_string(), &token_dictionary)?);
    }

    tokens.push_back(Token::EOF);
    return Ok(tokens);
}