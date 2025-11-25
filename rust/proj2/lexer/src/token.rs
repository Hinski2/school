use std::{collections::HashMap};

#[derive(Clone, PartialEq, Debug)]
pub enum Token {
    // special
    EOL,            // end of line
    EOF,            // end of file
    COMMENT(String),// ;[_]*
    
    // values
    INT(i64),
    FLOAT(f64),

    // var
    VARNAME(String),    // "[A-Za-z][A-Za-z0-9]*
    VARREF(String),     // :[A-Za-z][A-Za-z0-9]*
    MAKE,               // MAKE

    // // data structures 
    // PICK,               // PICK 
    // RANDOM,             // RANDOM

    // brackets
    LSQUAREDBRACKET,    // [
    RSQUAREDBRACKET,    // ]
    LROUNDBRACKET,      // (
    RROUNDBRACKET,      // )

    // procedures
    BEGIN,                  // TO
    END,                    // END
    PROCEDUREID(String),    // [A-Za-z][A-Za-z0-9]*

    // arithmetic
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

    // logical 
    AND,    // AND 
    OR,     // OR 
    NOT,    // NOT

    // control structures 
    REPEAT,     // REPEAT
    IF,         // IF
    IFELSE,     // IFELSE
    WAIT,       // WAIT
}

const MAX_TOKEN_LEN: usize = 7;
pub struct TokenDictionary {
    dict: [HashMap<&'static str, Token>; MAX_TOKEN_LEN],
}

impl TokenDictionary {
    pub fn new() -> TokenDictionary {
        let dict: [HashMap<&'static str, Token>; MAX_TOKEN_LEN] = [
            HashMap::new(), // 0
            HashMap::from([ // 1     
                ("[", Token::LSQUAREDBRACKET),
                ("]", Token::RSQUAREDBRACKET),
                ("(", Token::LROUNDBRACKET),
                (")", Token::RROUNDBRACKET),
                ("+", Token::ADD),
                ("-", Token::SUB),
                ("*", Token::MULT),
                ("/", Token::DIV),
                ("%", Token::MOD),
                ("=", Token::EQP),
                (">", Token::GTP),
                ("<", Token::LTP),
            ]),
            HashMap::from([ // 2
                ("TO", Token::BEGIN),
                ("IF", Token::IF),
                ("OR", Token::OR),
                ("<>", Token::NEQP),
                (">=", Token::GEQP),
                ("<=", Token::LEQP),
            ]),
            HashMap::from([ // 3
                ("AND", Token::AND),
                ("NOT", Token::NOT),
                ("END", Token::END),
            ]),
            HashMap::from([ // 4
                ("MAKE", Token::MAKE),
                ("WAIT", Token::WAIT),
            ]),
            HashMap::new(), // 5
            HashMap::from([
                ("REPEAT", Token::REPEAT),
                ("IFELSE", Token::IFELSE),
            ]),
        ];

        return TokenDictionary { dict }
    } 

    pub fn try_match_keyword(&self, s: &[char]) -> Option<(Token, usize)> {
        if s.is_empty() {
            return None;
        }

        for i in (1..MAX_TOKEN_LEN).rev() {
            if i > s.len() {
                continue;
            }

            let key: String = s[..i].iter().collect();
            if let Some(t) = self.dict[i].get(key.as_str()) {
                return Some((t.clone(), i));
            }
        }

        None
    }

    pub fn try_match_value(&self, s: &[char]) -> Option<(Token, usize)> {
        if s.is_empty() {
            return None;
        }

        let minus: i64 = if s[0] == '-' {-1} else {1};
        let mut i = if minus == -1 {1} else {0};

        while i < s.len() && s[i].is_numeric() {
            i += 1;
        } 

        if (minus == -1 && i == 1) || (minus == 1 && i == 0) {
            return None;
        }

        if i < s.len() && s[i] == '.' {
            i += 1;
        } else {
            let numb: i64 = s[0..i]
                .iter()
                .collect::<String>()
                .parse()
                .unwrap();

            return Some((Token::INT(minus * numb), i))
        }

        while i < s.len() && s[i].is_numeric() {
            i += 1;
        }

        let numb: f64 = s[0..i]
            .iter()
            .collect::<String>()
            .parse()
            .unwrap();

        Some((Token::FLOAT(minus as f64 * numb), i))
    }

    pub fn try_match_ident(&self, s: &[char]) -> Option<(Token, usize)> {
        if s.is_empty() {
            return None;
        }

        if s[0] == ';' {
            return Some((Token::COMMENT(s.iter().skip(1).collect()), s.len()));
        }

        let mut i = if s[0] == '"' || s[0] == ':' {1} else {0};

        if i >= s.len() || !s[i].is_alphabetic() {
            return None;
        } else {
            i += 1;
        }

        while i < s.len() && s[i].is_alphanumeric() {
            i += 1;
        }

        match s[0] {
            '"' => Some((Token::VARNAME(s[1..i].iter().collect()), i)),
            ':' => Some((Token::VARREF(s[1..i].iter().collect()), i)),
            _ => Some((Token::PROCEDUREID(s[0..i].iter().collect()), i))
        }
    }
}
