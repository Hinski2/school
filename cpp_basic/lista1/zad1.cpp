#include <bits/stdc++.h>
using namespace std;

const std::vector<pair<int, std::string>> roman = {
    {1000, "M"},
    {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
    {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"},
    {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
};

string toRoman(int x) {
    string ans;

    while(x) {
        for(auto& [r_numb, r_str]: roman) {
            if(x >= r_numb) {
                x -= r_numb;
                ans += r_str;
                break;
            }
        }
    }     

    return ans;
}

int main(int argc, char *argv[]) {
    for(int i = 1; i < argc; i++) {
        try {
            const int x = stoi(argv[i], 0); 
            if(x < 1 or x > 3999)
                cerr << "out of range " << argv[i] << endl;
            else 
                cout << toRoman(x) << endl;
        } catch (invalid_argument const& e) {
            cerr << "invalid argument " << argv[i] << endl; 
        } catch(out_of_range const& e) {
            cerr << "out of range " << argv[i] << endl;
        }
    }    
}
