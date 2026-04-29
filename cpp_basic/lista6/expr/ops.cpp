#include "ops.hpp"

namespace expression_tree {

// Neg
Neg::Neg(std::unique_ptr<Expr> child) : child(std::move(child)) {}

bool Neg::calc() const {
    return !child->calc();
}

std::string Neg::print() const {
    if (child->priority() >= priority())
        return "!" + child->print();
    return "!(" + child->print() + ")";
}

int Neg::priority() const { return 9; }

// Binop
Binop::Binop(std::unique_ptr<Expr> l, std::unique_ptr<Expr> r)
    : left(std::move(l)), right(std::move(r)) {}

std::string Binop::print() const {
    auto wrap = [&](const std::unique_ptr<Expr>& e) -> std::string {
        if (e->priority() > priority())
            return e->print();
        return "(" + e->print() + ")";
    };

    return wrap(left) + " " + symbol() + " " + wrap(right);
}

// AndExpr
bool AndExpr::calc() const { return left->calc() && right->calc(); }
int AndExpr::priority() const { return 5; }
std::string AndExpr::symbol() const { return "&"; }

// XorExpr
bool XorExpr::calc() const { return left->calc() != right->calc(); }
int XorExpr::priority() const { return 4; }
std::string XorExpr::symbol() const { return "^"; }

// OrExpr
bool OrExpr::calc() const { return left->calc() || right->calc(); }
int OrExpr::priority() const { return 3; }
std::string OrExpr::symbol() const { return "|"; }

// ImpExpr
bool ImpExpr::calc() const { return !left->calc() || right->calc(); }
int ImpExpr::priority() const { return 2; }
std::string ImpExpr::symbol() const { return "=>"; }

// EqvExpr
bool EqvExpr::calc() const { return left->calc() == right->calc(); }
int EqvExpr::priority() const { return 1; }
std::string EqvExpr::symbol() const { return "<=>"; }

}