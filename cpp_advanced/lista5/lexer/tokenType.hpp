#pragma once
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include <cstdint>
#include <string_view>
#include <utility>
using namespace std;

enum class TokenType {
    // special 
    TOK_NONE,
    TOK_EOF, 

    // values 
    TOK_FLOAT,
    TOK_INT,
    TOK_BOOL,       // True, False

    // bop
    TOK_ADD,        // +
    TOK_SUB,        // -
    TOP_MULT,       // *
    TOK_DIV,        // /
    TOK_MOD,        // %

    TOK_EQ,         // ==
    TOK_NEQ,        // !=
    TOK_GEQ,        // >=
    TOK_LEQ,        // <=
    TOK_GT,         // >
    TOK_LT,         // <
    TOK_LOG_AND,    // and
    TOK_LOG_OR,     // or
    TOK_BIT_AND,    // &
    TOK_BIT_OR,     // |  
    TOK_XOR,        // ^
    TOK_NOT,        // !

    // paren
    TOK_L_ROUND_PAREN, // (
    TOK_R_ROUND_PAREN, // )
    
    // ident
    TOK_ASSIGN,     // =
    TOK_IDENT,
};

constexpr string_view to_string(TokenType t) {
    switch(t) {
        // special
        case TokenType::TOK_NONE:  return "NONE";
        case TokenType::TOK_EOF:   return "EOF";
        
        // values
        case TokenType::TOK_FLOAT: return "FLOAT";
        case TokenType::TOK_INT:   return "INT";
        case TokenType::TOK_BOOL:  return "BOOL";
        
        // bop
        case TokenType::TOK_ADD:   return "ADD";
        case TokenType::TOK_SUB:   return "SUB";
        case TokenType::TOP_MULT:  return "MULT";
        case TokenType::TOK_DIV:   return "DIV";
        case TokenType::TOK_MOD:   return "MOD";

        case TokenType::TOK_EQ:    return "EQ";
        case TokenType::TOK_NEQ:   return "NEQ";
        case TokenType::TOK_GEQ:   return "GEQ";
        case TokenType::TOK_LEQ:   return "LEQ";
        case TokenType::TOK_GT:    return "GT";
        case TokenType::TOK_LT:    return "LT";
        case TokenType::TOK_LOG_AND: return "LOG_AND";
        case TokenType::TOK_LOG_OR:  return "LOG_OR";
        case TokenType::TOK_BIT_AND: return "BIT_AND";
        case TokenType::TOK_BIT_OR:  return "BIT_OR";
        case TokenType::TOK_XOR:     return "XOR";
        case TokenType::TOK_NOT:     return "NOT";
    
        // paren
        case TokenType::TOK_L_ROUND_PAREN: return "LPAREN";
        case TokenType::TOK_R_ROUND_PAREN: return "RPAREN";
        
        // ident
        case TokenType::TOK_ASSIGN: return "ASSIGN";
        case TokenType::TOK_IDENT:  return "IDENT";
    }

    return "NONE";
}

class TokenTypeDict {
    using entry = std::pair<std::string_view, TokenType>;

    constexpr static entry dict0[] = {
        {"", TokenType::TOK_NONE},  // never used, without this compiler screams
    };
    constexpr static entry dict1[] = {
        {"!",  TokenType::TOK_NOT},
        {"%",  TokenType::TOK_MOD},
        {"&",  TokenType::TOK_BIT_AND},
        {"*",  TokenType::TOP_MULT},
        {"+",  TokenType::TOK_ADD},
        {"-",  TokenType::TOK_SUB},
        {"/",  TokenType::TOK_DIV},
        {"<",  TokenType::TOK_LT},
        {"=",  TokenType::TOK_ASSIGN},
        {">",  TokenType::TOK_GT},
        {"^",  TokenType::TOK_XOR},
        {"|",  TokenType::TOK_BIT_OR},
    };
    constexpr static entry dict2[] = {
        {"!=", TokenType::TOK_NEQ},
        {"<=", TokenType::TOK_LEQ},
        {">=", TokenType::TOK_GEQ},
        {"==", TokenType::TOK_EQ},
        {"or", TokenType::TOK_LOG_OR},
    };

    constexpr static entry dict3[] = {
            {"and", TokenType::TOK_LOG_AND},
    };

    static constexpr array dict {
        span<const entry>(dict0),
        span<const entry>(dict1),
        span<const entry>(dict2),
        span<const entry>(dict3)
    };

static uint32_t parse_digits(string_view sw) {
    uint32_t i = 0;
    while(i < sw.size() and isdigit(sw[i])) {
        i++;
    }

    return i;
}

public:
    optional<pair<TokenType, uint32_t>> try_match_keyword(string_view sw) {
        for(uint32_t i = 3; i; i--) {
            if(sw.size() < i) continue;

            auto it = lower_bound(
                dict[i].begin(), dict[i].end(), sw.substr(0, i),
                [](const entry &e, string_view val) {
                    return e.first < val;         
                }
            );

            if(it != dict[i].end() and it -> first == sw.substr(0, i)) {
                return make_pair(it -> second, i);
            }
        } 

        return nullopt;
    }
    
    optional<pair<TokenType, uint32_t>> try_match_value(string_view sw) {
        if(sw.empty()) return nullopt;

        // bool 
        if(sw.substr(0, 4) == "True") {
            return make_pair(TokenType::TOK_BOOL, 4);
        } else if(sw.substr(0, 5) == "False") {
            return make_pair(TokenType::TOK_BOOL, 5);
        }

        uint32_t n = parse_digits(sw);
        if(n and n < sw.size() and sw[n] == '.') {              // digits.digits or digits.
            uint32_t m = parse_digits(sw.substr(n + 1));
            return make_pair(TokenType::TOK_FLOAT, n + 1 + m);
        } else if(sw[0] == '.'){                                // .digits
            uint32_t m = parse_digits(sw.substr(n + 1));
            if(m) return make_pair(TokenType::TOK_FLOAT, 1 + m);
        } else if(n) {                                          // int
            return make_pair(TokenType::TOK_INT, n);
        }

        return nullopt;
    }

    optional<pair<TokenType, uint32_t>> try_match_ident(string_view sw) {
        if(sw.empty()) return nullopt; 
        if(!isalpha(sw[0]) and sw[0] != '_') return nullopt;

        uint32_t i = 1;
        while(i < sw.size() and (isalnum(sw[i]) or sw[i] == '_')) {
            i++;
        }

        return make_pair(TokenType::TOK_IDENT, i);
    }
};
