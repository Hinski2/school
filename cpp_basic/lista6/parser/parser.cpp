#include "parser.hpp"
#include "../expr/lit.hpp"
#include "../expr/var.hpp"
#include "../expr/ops.hpp"
#include <stdexcept>

namespace expression_tree {

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

Token Parser::peek() const {
    return tokens[pos];
}

Token Parser::consume() {
    return tokens[pos++];
}

Token Parser::expect(TokenType type) {
    Token t = consume();
    if (t.type != type)
        throw std::runtime_error("Unexpected token: " + t.value);
    return t;
}

std::unique_ptr<Expr> Parser::parse_eqv() {
    auto left = parse_imp();
    while (peek().type == TokenType::EQV) {
        consume();
        auto right = parse_imp();
        left = std::make_unique<EqvExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_imp() {
    auto left = parse_or();
    while (peek().type == TokenType::IMP) {
        consume();
        auto right = parse_or();
        left = std::make_unique<ImpExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_or() {
    auto left = parse_xor();
    while (peek().type == TokenType::OR) {
        consume();
        auto right = parse_xor();
        left = std::make_unique<OrExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_xor() {
    auto left = parse_and();
    while (peek().type == TokenType::XOR) {
        consume();
        auto right = parse_and();
        left = std::make_unique<XorExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_and() {
    auto left = parse_neg();
    while (peek().type == TokenType::AND) {
        consume();
        auto right = parse_neg();
        left = std::make_unique<AndExpr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<Expr> Parser::parse_neg() {
    if (peek().type == TokenType::NOT) {
        consume();
        auto child = parse_neg();
        return std::make_unique<Neg>(std::move(child));
    }
    return parse_atom();
}

std::unique_ptr<Expr> Parser::parse_atom() {
    Token t = peek();
    if (t.type == TokenType::LIT) {
        consume();
        return Lit::make(t.value == "1");
    }
    if (t.type == TokenType::VAR) {
        consume();
        return std::make_unique<Var>(t.value);
    }
    if (t.type == TokenType::LPAREN) {
        consume();
        auto e = parse_eqv();
        expect(TokenType::RPAREN);
        return e;
    }
    throw std::runtime_error("Unexpected token in atom: " + t.value);
}

std::unique_ptr<Expr> Parser::parse(const std::vector<Token>& tokens) {
    Parser p(tokens);
    auto result = p.parse_eqv();
    p.expect(TokenType::END);
    return result;
}

}
