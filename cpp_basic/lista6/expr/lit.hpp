#pragma once
#include "expr.hpp"

namespace expression_tree {

class Lit final : public Expr {
    bool value;
    explicit Lit(bool v);

public:
    static const Lit ZERO;
    static const Lit ONE;
    static std::unique_ptr<Lit> make(bool value);

    bool calc() const override;
    std::string print() const override;
    int priority() const override;
};

}
