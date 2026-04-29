#pragma once
#include "expr.hpp"
#include <string>
#include <unordered_map>
#include <memory>

namespace expression_tree {

class Var final : public Expr {
    std::string name;

public:
    static std::unordered_map<std::string, bool> table;
    explicit Var(std::string name);
    bool calc() const override;
    std::string print() const override;
    int priority() const override;
    static void set(const std::string& name, bool value);
    static void clear();
};

}
