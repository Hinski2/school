#include <bits/stdc++.h>
#include "token.hpp"

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

    string line;
    while(getline(*in, line)) {
        auto res = lexer(line);
        for(auto token: res) {
            cout << token;
        }
        cout << endl;
    }
}
