#include <bits/stdc++.h>
using namespace std;

int main() {
    auto m = [](int m) {
       switch(m) {
            case 1: return "styczeń";
            case 2: return "luty";
            case 3: return "marzec";
            case 4: return "kwiecień";
            case 5: return "maj";
            case 6: return "czerwiec";
            case 7: return "lipiec";
            case 8: return "sierpień";
            case 9: return "wrzesień";
            case 10: return "październik";
            case 11: return "listopad";
            case 12: return "grudzień";
            default: return "nie miesiąc";
       } 
    };
    
    string s = "1/5/2020";
    auto tokens = views::split(s, '/')
        | views::transform([](auto substr) {
            return string(substr.begin(), substr.end());
        })
        | ranges::to<vector>();
    
    println("{} {} {}", tokens[0], m(stoi(tokens[1])), tokens[2]);
}
