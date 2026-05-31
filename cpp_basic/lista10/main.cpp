#include "lib.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

void test_a(string file) {
    ifstream ifs(file);
    if(!ifs) {
        cerr << "cannot open file: " << file << endl;
        return;
    }

    vector<pair<string, int>> lines;
    for(string line; getline(ifs, line);)
        lines.emplace_back(line, lines.size() + 1);

    sort(lines.begin(), lines.end());

    for(const auto& [text, nr] : lines)
        cout << index(nr, 1) << " " << text << "\n";
}

void etap_1() {
    cout << "etap 1" << endl;
    
    {
        ofsbin out("test1.bin");
        for(int i = 0; i < 10; ++i) {
            int x = rand() % 10;
            out << x;
            cout << x << ' ';
        }
        cout << endl;
    }

    {
        ifsbin in("test1.bin");
        for(int i = 0; i < 10; ++i) {
            int x;
            in >> x;
            cout << x << ' ';
        }
        cout << endl;
    }
}

void etap_2() {
    cout << "etap 2" << endl;
    
    {
        ofsbin out("test2.bin");
        out << 'N' << 51 << 6 << 39.4 << 'E' << 17 << 3 << 12.1;
    }

    {
        ifsbin in("test2.bin");
        char dir1, dir2;
        int deg1, min1, deg2, min2;
        double sec1, sec2;
        in >> dir1 >> deg1 >> min1 >> sec1 >> dir2 >> deg2 >> min2 >> sec2;
        cout << dir1 << " " << deg1 << " " << min1 << " " << sec1 
             << " " << dir2 << " " << deg2 << " " << min2 << " " << sec2 << endl;
    }
}

void etap_3() {
    cout << "etap 3" << endl;
    ifsbin in("test3.bin");
    unsigned char byte;

    while(true) {
        try {
            in >> byte;
            cout << std::hex << (int) byte << " ";
            cout << std::dec << (int) byte << " ";
            if(byte >= 32 && byte <= 126) {
                cout << (char) byte;
            } else {
                cout << '.';
            }
            cout << endl;
        } catch(const std::ios_base::failure&) {
            break;
        }
    }
}

void test_b() {
    std::srand(std::time(nullptr));

    {
        ofsbin out("test3.bin");
        for(int i = 0; i < 256; ++i) {
            out << (unsigned char)i;
        }
    }

    etap_1();
    etap_2();
    etap_3();
}

int main() {
    test_a("a.txt");
    test_b();
}
