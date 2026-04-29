#include "lit.hpp"

namespace expression_tree {

const Lit Lit::ZERO{false};
const Lit Lit::ONE{true};

std::unique_ptr<Lit> Lit::make(bool value) {
    return std::unique_ptr<Lit>(new Lit(value));
}

bool Lit::calc() const { return value; }
std::string Lit::print() const { return value ? "1" : "0"; }
int Lit::priority() const { return 10; }
Lit::Lit(bool v) : value(v) {}

}
