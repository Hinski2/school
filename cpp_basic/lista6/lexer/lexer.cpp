#include "lexer.hpp"
#include <array>

namespace expression_tree {

static constexpr std::array<std::pair<std::string_view, TokenType>, 8> FIXED_TOKENS{{
    {"<=>", TokenType::EQV},
    {"=>",  TokenType::IMP},
    {"!",   TokenType::NOT},
    {"&",   TokenType::AND},
    {"^",   TokenType::XOR},
    {"|",   TokenType::OR},
    {"(",   TokenType::LPAREN},
    {")",   TokenType::RPAREN},
}};

namespace {

void try_match_whitespace(int& i, const std::string& input) {
    while(i < static_cast<int>(input.size()) and std::isspace(input[i])) {
        i++;
    }
}

bool try_match_lit(std::vector<Token>& tokens, int& i, const std::string& input) {
    if(input[i] == '0' or input[i] == '1') {
        tokens.push_back({TokenType::LIT, std::string(1, input[i])});
        i++;
        return true;
    }
    return false;
}

bool try_match_token_type(std::vector<Token>& tokens, int& i, const std::string& input) {
    for (auto& [token_sv, token_type] : FIXED_TOKENS) {
        if (input.compare(i, token_sv.size(), token_sv) == 0) {
            tokens.push_back({token_type, std::string(token_sv)});
            i += token_sv.size();
            return true;
        }
    }
    return false;
}

bool try_match_var(std::vector<Token>& tokens, int& i, const std::string& input) {
    std::string var_name;

    while(i < static_cast<int>(input.size()) and std::islower(input[i])) {
        var_name += input[i++];
    }

    if(not var_name.empty()) {
        tokens.push_back({TokenType::VAR, var_name});
        return true;
    } else {
        return false;
    }
}

}

std::vector<Token> Lexer::tokenize(const std::string& input) {
    std::vector<Token> tokens;

    for(int i = 0; try_match_whitespace(i, input), i < static_cast<int>(input.size());) {
        if(try_match_lit(tokens, i, input)) {
            continue;
        } else if(try_match_token_type(tokens, i, input)) {
            continue;
        } else if(try_match_var(tokens, i, input)) {
            continue;
        } else {
            throw std::runtime_error("Error: invalid token " + std::string(1, input[i]) + " at position " + std::to_string(i));
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}

}