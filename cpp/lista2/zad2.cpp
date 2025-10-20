#include<bits/stdc++.h>
using namespace std;

struct LineWriter {
    ofstream file;

    LineWriter(const string& path)
        : file(path) {
        if(!file.is_open())
            throw runtime_error("Error: can't open file " + path);
    }

    ~LineWriter() {
        file.flush();
        file.close();
    }

    template<class T>
    LineWriter& operator << (const T& val) {
        file << val;
        return *this;
    }
};

int main() {
    auto w = make_shared<LineWriter>("a.txt");

    shared_ptr<LineWriter> w1 = w;
    shared_ptr<LineWriter> w2 = w;
    shared_ptr<LineWriter> w3 = w;

    *w1 << "jeden\n";
    *w2 << "dwa\n";
    *w3 << "trzy\n";
}