#include "utils.hpp"

optional<Token> peek(forward_list<Token> &tokens) {
    if(tokens.empty()) return nullopt;
    return tokens.front();
}

optional<Token> consume(forward_list<Token> &tokens) {
    if(tokens.empty()) return nullopt;
    auto first = tokens.front();
    tokens.pop_front();
    return first; 
}