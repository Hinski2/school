#include <bits/stdc++.h>
#include <cstdint>
#include <fstream>
#include <random>
using namespace std;

static string generate_word(uint32_t len) {
    static random_device rd;
    static mt19937 gen(rd());
    static vector<double> w = {
        8.37, 
        1.93, 
        3.89, 
        3.35, 
        8.68, 
        0.26, 
        1.46, 
        1.25, 
        8.83, 
        2.28, 
        3.01, 
        2.24, 
        2.81, 
        5.69, 
        7.53, 
        2.87, 
        0.00, // q
        4.15, 
        4.13, 
        3.85, 
        2.06, 
        0.00, // v
        4.11, 
        0.00, // x
        4.03, 
        5.33
        
    };
    static discrete_distribution<int> d(w.begin(), w.end());


    string s(len, ' ');
    for(int i = 0; i < len; i++) {
        s[i] = 'a' + d(gen);
    }

    return s;
}

static void generate_txt(ofstream &file, uint32_t len) {
    static random_device rd;
    static mt19937 gen(rd());
    static binomial_distribution<> d(11, 0.5);

    uint32_t generated = 0;

    while(len - generated > 12) {
        uint32_t word_len = d(gen) + 1;
        string word = generate_word(word_len);

        file << word << ' ';
        generated += word_len + 1;
    }

    string word = generate_word(len - generated);
    file << word << endl;
}

int main() {
    ofstream file("tekst.txt");
    generate_txt(file, 1000);
}
