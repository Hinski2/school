#include <bits/stdc++.h>
using namespace std;

struct Osoba {
    string nazwisko;
    string imie;
    int wiek;

    friend bool operator < (const Osoba &a, const Osoba &b) {
        return  tie(a.nazwisko, a.imie, a.wiek) <
                tie(b.nazwisko, b.imie, b.wiek);
    }

    friend ostream& operator << (ostream& out, const Osoba &o) {
        out << "{ " << o.nazwisko << ' ' << o.imie << ' ' << o.wiek << " }";

        return out;
    }

};

int main() {
    vector<Osoba> osoby = {
        {"Mączyński", "Jan", 21},
        {"Iliński", "Jakub", 20},
        {"Stodułka", "Łukasz", 21},
        {"Pawliczek", "Dawid", 21},
        {"Pawliczek", "Dawid", 20},
    };

    sort(osoby.begin(), osoby.end());
    for(auto o: osoby) 
        cout << o << endl;
}