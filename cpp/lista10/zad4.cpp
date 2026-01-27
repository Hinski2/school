#include <bits/stdc++.h>
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    locale loc("pl_PL.UTF-8"); // /etc/locale.gen
    wcout.imbue(loc);

    vector<wstring> v = {
        L"żułtodziób",
        L"żubr",
        L"zebra",
        L"mlecz",
        L"łabądź",
        L"ćma",
    };

    for(auto &w: v) {
        wcout << w << endl;
    }
    wcout << endl;

    sort(v.begin(), v.end(), loc);

    for(auto &w: v) {
        wcout << w << endl;
    }
}
