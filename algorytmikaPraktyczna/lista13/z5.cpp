#include<bits/stdc++.h>
using namespace std;

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

inline void solve() {
    int n; cin >> n;
    vector<int> v(n); cin >> v;

    bool odd = false;
    for(auto u: v) 
        if(u % 2) {
            cout << "first" << endl;
            return;
        }
    cout << "second" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}