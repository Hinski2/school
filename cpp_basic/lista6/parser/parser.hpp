#pragma once
#include "../lexer/lexer.hpp"
#include "../expr/expr.hpp"
#include <vector>
#include <memory>

namespace expression_tree {

class Parser {
    const std::vector<Token>& tokens;
    int pos;

    Token peek() const;
    Token consume();
    Token expect(TokenType type);

    std::unique_ptr<Expr> parse_eqv();
    std::unique_ptr<Expr> parse_imp();
    std::unique_ptr<Expr> parse_or();
    std::unique_ptr<Expr> parse_xor();
    std::unique_ptr<Expr> parse_and();
    std::unique_ptr<Expr> parse_neg();
    std::unique_ptr<Expr> parse_atom();

    explicit Parser(const std::vector<Token>& tokens);

public:
    static std::unique_ptr<Expr> parse(const std::vector<Token>& tokens);
};

}
