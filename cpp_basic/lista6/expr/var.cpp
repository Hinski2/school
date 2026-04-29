#include "var.hpp"
#include <stdexcept>

namespace expression_tree {

std::unordered_map<std::string, bool> Var::table;

Var::Var(std::string name) : name(std::move(name)) {}

bool Var::calc() const {
    auto it = table.find(name);
    if (it == table.end()) {
        throw std::runtime_error("Error: " + name + " not set");
    }
    return it->second;
}
std::string Var::print() const {
    return name;
}

int Var::priority() const {
    return 10;
}

void Var::set(const std::string& name, bool value) {
    table[name] = value;
}

void Var::clear() {
    table.clear();
}

}
