#include <bits/stdc++.h>
#include "lexer/token.hpp"
#include "parser/recursiveDescentParser.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream file;
    istream* in = &cin;

    if(argc > 1) {
        file.open(argv[1]);
        if(!file) {
            cerr << "Error: invalid file " << argv[1] << endl;
            return 1;
        }

        in = &file;
    }

    // lex
    string line;
    deque<string> lines;
    vector<Token> tokens;

    while(getline(*in, line)) {
        lines.push_back(line);
        auto res = lexer(lines.back());
        tokens.insert(tokens.end(), res.begin(), res.end());
    }

    // parse
    forward_list<Token> fl(tokens.begin(), tokens.end());

    vector<Stmt> program = parse_program(fl);
    for(auto &stmt: program) {
        cout << stmt << endl;
    }
}
