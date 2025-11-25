pub mod token;
pub mod lexer;

#[cfg(test)]
mod tests {
    use crate::token::{Token, TokenDictionary};
    use crate::lexer::lexer;

    #[test]
    fn test_one_char_keyword() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("+".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::ADD, Token::EOL]);
    }

    #[test]
    fn test_two_char_keyword() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("<>".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::NEQP, Token::EOL]);
    }

    #[test]
    fn test_five_char_keyword() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("REPEAT".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::REPEAT, Token::EOL],);
    }

    #[test]
    fn test_a() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("1 + 1.1".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::INT(1),Token::ADD, Token::FLOAT(1.1), Token::EOL],);
    }

    #[test]
    fn test_b() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("1".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::INT(1), Token::EOL],);
    }

    #[test]
    fn test_c() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer("XD42 ;some comment".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::PROCEDUREID("XD42".to_string()), Token::COMMENT("some comment".to_string()), Token::EOL],);
    }

    #[test]
    fn test_d() {
        let token_dictionary = TokenDictionary::new();
        let tokens: Vec<Token> = lexer(":XD  \"XD".to_string(), &token_dictionary)
            .unwrap()
            .into_iter()
            .collect();
        
        assert_eq!(tokens, vec![Token::VARREF("XD".to_string()), Token::VARNAME("XD".to_string()), Token::EOL],);
    }

}