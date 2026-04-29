#pragma once
#include <string>
#include <vector>
#include <stdexcept>

namespace expression_tree {

enum class TokenType {
    LIT,      // 0, 1
    VAR,      
    NOT,      // !
    AND,      // &
    XOR,      // ^
    OR,       // |
    IMP,      // =>
    EQV,      // <=>
    LPAREN,   // (
    RPAREN,   // )
    END 
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    static std::vector<Token> tokenize(const std::string& input);
};

}
