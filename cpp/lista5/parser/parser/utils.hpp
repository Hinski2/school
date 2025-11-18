#pragma once 
#include "../lexer/token.hpp"
using namespace std;

//* structs for parser
enum class Bop {
    BOP_ADD, 
    BOP_SUB,
    BOP_MULT,
    BOP_DIV,
    BOP_MOD,
    BOP_EQ,
    BOP_NEQ,
    BOP_GEQ,
    BOP_LEQ,
    BOP_GT,
    BOP_LT,
    BOP_LOG_AND,
    BOP_LOG_OR,
    BOP_BIT_AND,
    BOP_BIT_OR,
    BOP_XOR,
};

struct Ident {
    string id;
};

struct Expr {
    struct Int {
        int64_t value;
    };

    struct Float {
        double value;
    };

    struct Bool {
        bool value;
    };

    struct Binary {
       Bop bop;
       unique_ptr<Expr> expr1;
       unique_ptr<Expr> expr2;
    };

    struct Var {
        Ident name;
    };

    using Node = variant<
        Int, 
        Float, 
        Bool, 
        Binary, 
        Var
    >;

    Node node;

    friend ostream& operator<<(ostream& out, const Expr& e) {
        out << "{";
        if(auto *v = get_if<Int>(&e.node)) {    // get_if: wsjaźnik an pole prechowywane w wartości labo nullptr
            out << v -> value;
        } else if(auto *v = get_if<Float>(&e.node)) {
            out << v -> value;
        } else if(auto *v = get_if<Bool>(&e.node)) {
            out << (v -> value ? "True" : "False");
        } else if(auto *v = get_if<Var>(&e.node)) {
            out << v -> name.id;
        } else if(auto *v = get_if<Binary>(&e.node)) {
            out << *v -> expr1;
            out << ' ' << "BOP" << ' '; //TODO
            out << *v -> expr2;
        }

        out << "}";
        return out;
    }
};

struct Stmt { 
    struct Let {
        Ident name;
        Expr expr;
    };

    struct Assign {
        Ident name;
        Expr expr;
    };

    using Block = variant<
        Let,
        Assign,
        Expr
    >;

    Block block;



    friend ostream& operator<<(ostream& out, const Stmt &s) {
        if(auto *v = get_if<Let>(&s.block)) {
            out << "Let " << v -> name.id << " = " << v -> expr;  
        } else if(auto *v = get_if<Assign>(&s.block)) {
            out << v -> name.id << " = " << v -> expr;
        } else if(auto *v = get_if<Expr>(&s.block)) {
            out << *v;
        }

        return out;
    }
};

//* utils
optional<Token> peek(forward_list<Token> &tokens);
optional<Token> consume(forward_list<Token> &tokens);
