#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "expr/var.hpp"
#include <iostream>
#include <string>

using namespace expression_tree;

int main() {
    auto test = [](const std::string& input) {
        auto tokens = Lexer::tokenize(input);
        auto tree = Parser::parse(tokens);
        std::cout << tree->print() << " = " << tree->calc() << "\n";
    };

    // test1
    test("1 & 0");

    // test2
    Var::set("a", true);
    Var::set("b", false);
    test("a & !b");

    // test 3
    test("!(a & b)) <=> !a | !b");

    // test 4
    test("!!a <=> a");

    // test 5
    test("!a => a => a");
}
