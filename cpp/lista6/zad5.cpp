#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "abcd";

    do {
        cout << s << endl;
    } while(next_permutation(s.begin(), s.end()));
}
