#pragma once 
#include "tokenType.hpp"
#include <string>
using namespace std;

struct Token {
    TokenType type;
    span<const char> view;
    
    friend ostream& operator<<(ostream &out, const Token& token) {
        out << "{ " << to_string(token.type) << ' ' << token.view.size() << " } ";
        return out;
    }
};

vector<Token> lexer(string &s);