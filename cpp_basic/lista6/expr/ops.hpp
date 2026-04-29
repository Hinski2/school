#pragma once
#include "expr.hpp"
#include <memory>
#include <string>

namespace expression_tree {

// Neg
class Neg final : public Expr {
    std::unique_ptr<Expr> child;
public:
    explicit Neg(std::unique_ptr<Expr> child);
    bool calc() const override;
    std::string print() const override;
    int priority() const override;
};

// Binop
class Binop : public Expr {
    virtual std::string symbol() const = 0;
protected:
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;
public:
    Binop(std::unique_ptr<Expr> left, std::unique_ptr<Expr> right);
    std::string print() const override;
};

// AndExpr
class AndExpr final : public Binop {
    std::string symbol() const override;
public:
    using Binop::Binop;
    bool calc() const override;
    int priority() const override;
};

// XorExpr
class XorExpr final : public Binop {
    std::string symbol() const override;
public:
    using Binop::Binop;
    bool calc() const override;
    int priority() const override;
};

// OrExpr
class OrExpr final : public Binop {
    std::string symbol() const override;
public:
    using Binop::Binop;
    bool calc() const override;
    int priority() const override;
};

// ImpExpr
class ImpExpr final : public Binop {
    std::string symbol() const override;
public:
    using Binop::Binop;
    bool calc() const override;
    int priority() const override;
};

// EqvExpr
class EqvExpr final : public Binop {
    std::string symbol() const override;
public:
    using Binop::Binop;
    bool calc() const override;
    int priority() const override;
};

}
