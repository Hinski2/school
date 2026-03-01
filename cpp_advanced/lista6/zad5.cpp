#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "test";
    sort(s.begin(), s.end());

    do {
        cout << s << endl;
    } while(next_permutation(s.begin(), s.end()));
}
