#pragma once
#include <string>
#include <memory>

namespace expression_tree {

struct Expr {
    virtual bool calc() const = 0;
    virtual std::string print() const = 0;
    virtual int priority() const = 0;

    Expr() = default;
    virtual ~Expr() = default;

    Expr(const Expr&) = delete;
    Expr& operator=(const Expr&) = delete;
    Expr(Expr&&) = delete;
    Expr& operator=(Expr&&) = delete;
};

}
