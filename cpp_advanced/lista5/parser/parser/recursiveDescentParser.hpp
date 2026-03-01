#pragma once 
#include "utils.hpp"
#include "../lexer/token.hpp"
#include "precedenceClimbingParser.hpp"
using namespace std;

vector<Stmt> parse_program(forward_list<Token> &tokens);
optional<Stmt> parse_stmt(forward_list<Token> &tokens);