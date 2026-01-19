#include <bits/stdc++.h>
#include <ios>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);

    locale loc("pl_PL.UTF-8"); // /etc/locale.gen
    wcout.imbue(loc);
    
    wstring ws = L"żółtość jaźń ąę";
    wcout << ws << endl;
}

