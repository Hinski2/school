#pragma once 
#include "utils.hpp"
using namespace std;

//* structs for parser
enum class Assoc {
    Left,
    Right,
}; // assoc for binop

struct OpInfo {
    int precedence; // priority for biniop
    Assoc assoc;
    Bop bop;
};

// utils 
optional<OpInfo> get_op_info(Token &token);
optional<Expr> parse_primary(forward_list<Token> &tokens);
optional<Expr> parse_atom(Token &token);

// recursive descent parsers
optional<Expr> parse_expr(forward_list<Token> &tokens);
optional<Expr> parse_expr_1(forward_list<Token> &tokens, Expr lhs, int min_presedence);