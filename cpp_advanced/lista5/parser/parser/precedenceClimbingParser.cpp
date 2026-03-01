// https://en.wikipedia.org/wiki/Operator-precedence_parser

#include "precedenceClimbingParser.hpp"

// precedence climbing parsers
optional<Expr> parse_expr(forward_list<Token> &tokens) {
    auto lhs_opt = parse_primary(tokens);
    if(!lhs_opt) {
        throw invalid_argument("expected primary value");
    }

    auto res = parse_expr_1(tokens, move(lhs_opt.value()), 0);
    if(!res) {
        throw invalid_argument("couldnt parse expression");
    }

    return res;
}

optional<Expr> parse_expr_1(forward_list<Token> &tokens, Expr lhs, int min_precedence) {
    while(true) {
        auto lookahead_token = peek(tokens);
        if(!lookahead_token)
            break; // no more tokens
        
        auto op_info_opt = get_op_info(lookahead_token.value());
        if(!op_info_opt) 
            break; // it's not binop

        if(op_info_opt.value().precedence < min_precedence) 
            break; // the operator is too weak

        consume(tokens); 
        auto rhs_opt = parse_primary(tokens);
        if(!rhs_opt) 
            return nullopt; // innapropriate tokens sequence

        while(true) {
            auto next_look_opt = peek(tokens);
            if(!next_look_opt) 
                break; // no more tokens
            
            auto next_op_info_opt = get_op_info(next_look_opt.value());
            if(!next_op_info_opt) break; 

            bool higher_precedence = next_op_info_opt.value().precedence > op_info_opt.value().precedence;
            bool right_assoc_and_equal = next_op_info_opt.value().precedence == op_info_opt.value().precedence and next_op_info_opt.value().assoc == Assoc::Right;
            
            if(!higher_precedence and !right_assoc_and_equal) 
                break;

            int new_min_prcedance = op_info_opt.value().precedence + (higher_precedence ? 1 : 0);
            rhs_opt = parse_expr_1(tokens, move(rhs_opt.value()), new_min_prcedance);
            if(!rhs_opt) 
                return nullopt; // error while parsing
        }

        Expr new_lhs;
        new_lhs.node = Expr::Binary{
            op_info_opt.value().bop,
            make_unique<Expr>(move(lhs)),
            make_unique<Expr>(move(rhs_opt.value())),
        };

        lhs = move(new_lhs);
    }

    return lhs;
}

// utils
optional<Expr> parse_atom(Token &token) {
    string s(token.view.data(), token.view.size());
    switch(token.type) {
        case TokenType::TOK_INT:    return Expr{ Expr::Int{stoll(s)} };
        case TokenType::TOK_FLOAT:  return Expr{ Expr::Float{stod(s)} };
        case TokenType::TOK_BOOL:   return Expr{ Expr::Bool{(s == "True")} };

        case TokenType::TOK_IDENT:  return Expr{ Expr::Var{s} }; 
        default:                    return nullopt;
    }
}

optional<Expr> parse_primary(forward_list<Token> &tokens) {
    auto token_opt = consume(tokens);
    if(!token_opt) return nullopt;
    auto token = token_opt.value();

    string s(token.view.data(), token.view.size());
    optional<Expr> expr_opt = nullopt;

    switch(token.type) {
        case TokenType::TOK_INT:
        case TokenType::TOK_FLOAT: 
        case TokenType::TOK_BOOL:
            return parse_atom(token);
        
        case TokenType::TOK_L_ROUND_PAREN:
            expr_opt = parse_expr(tokens);
            if(!expr_opt) return nullopt;
            token_opt = consume(tokens); 
            if(!token_opt or token_opt.value().type != TokenType::TOK_R_ROUND_PAREN) 
                return nullopt;

            return expr_opt;
        
        default:
            return nullopt;
    }
}

// like in c++
optional<OpInfo> get_op_info(Token &token) {
    switch(token.type) {
        case TokenType::TOK_LOG_OR:     return OpInfo{1,  Assoc::Left,  Bop::BOP_LOG_OR};
        case TokenType::TOK_LOG_AND:    return OpInfo{2,  Assoc::Left,  Bop::BOP_LOG_AND};
        case TokenType::TOK_BIT_OR:     return OpInfo{3,  Assoc::Left,  Bop::BOP_BIT_OR};
        case TokenType::TOK_XOR:        return OpInfo{4,  Assoc::Left,  Bop::BOP_XOR};
        case TokenType::TOK_BIT_AND:    return OpInfo{5,  Assoc::Left,  Bop::BOP_BIT_AND};

        case TokenType::TOK_EQ:         return OpInfo{6,  Assoc::Left,  Bop::BOP_EQ};
        case TokenType::TOK_NEQ:        return OpInfo{6,  Assoc::Left,  Bop::BOP_NEQ};

        case TokenType::TOK_LT:         return OpInfo{7,  Assoc::Left,  Bop::BOP_LT};
        case TokenType::TOK_LEQ:        return OpInfo{7,  Assoc::Left,  Bop::BOP_LEQ};
        case TokenType::TOK_GT:         return OpInfo{7,  Assoc::Left,  Bop::BOP_GT};
        case TokenType::TOK_GEQ:        return OpInfo{7,  Assoc::Left,  Bop::BOP_GEQ};

        case TokenType::TOK_ADD:        return OpInfo{8,  Assoc::Left,  Bop::BOP_ADD};
        case TokenType::TOK_SUB:        return OpInfo{8,  Assoc::Left,  Bop::BOP_SUB};

        case TokenType::TOP_MULT:       return OpInfo{9,  Assoc::Left,  Bop::BOP_MULT};
        case TokenType::TOK_DIV:        return OpInfo{9,  Assoc::Left,  Bop::BOP_DIV};
        case TokenType::TOK_MOD:        return OpInfo{9,  Assoc::Left,  Bop::BOP_MOD};

        default:                        return nullopt;
    }
}