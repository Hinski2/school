#include "recursiveDescentParser.hpp"

// recursive descent parsers
vector<Stmt> parse_program(forward_list<Token> &tokens) {
    vector<Stmt> program;

    while(peek(tokens)){
        auto stmt_opt = parse_stmt(tokens);
        if(!stmt_opt)
            throw invalid_argument("couldnt parse line");

        program.push_back(move(stmt_opt.value()));
    }

    return program;
}

optional<Stmt> parse_stmt(forward_list<Token> &tokens) {
    auto token_opt = peek(tokens);
    if(!token_opt)
        return nullopt; // it won't happen 

    optional<Token> next_token_opt = nullopt;
    optional<Expr> expr_opt = nullopt;
    Ident name;

    switch(token_opt.value().type) {
        // let IDENT = expr EOL
        case TokenType::TOK_LET:
            consume(tokens); // consume let

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_IDENT) return nullopt;
            name = Ident { string(next_token_opt.value().view.data(), next_token_opt.value().view.size()) };

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_ASSIGN) return nullopt;

            expr_opt = parse_expr(tokens);
            if(!expr_opt) return nullopt;

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_EOL) return nullopt;

            return Stmt { Stmt::Let{name, move(expr_opt.value())} };

        // IDENT = expr
        case TokenType::TOK_IDENT:
            next_token_opt = consume(tokens); // consume ident
            if (!next_token_opt || next_token_opt.value().type != TokenType::TOK_IDENT) return nullopt;

            name = Ident { string(next_token_opt.value().view.data(), next_token_opt.value().view.size()) };

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_ASSIGN) return nullopt;

            expr_opt = parse_expr(tokens);
            if(!expr_opt) return nullopt;

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_EOL) return nullopt;

            return Stmt { Stmt::Assign{name, move(expr_opt.value())} };
        
        // expr
        default:
            expr_opt = parse_expr(tokens);
            if(!expr_opt) return nullopt;

            next_token_opt = consume(tokens);
            if(!next_token_opt or next_token_opt.value().type != TokenType::TOK_EOL) return nullopt;

            return Stmt { move(expr_opt.value()) };
    }
}