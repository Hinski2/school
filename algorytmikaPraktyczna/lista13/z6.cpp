#include<bits/stdc++.h>
using namespace std;
#define int long long

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

inline void solve() {
    int n; cin >> n;
    vector<int> v(n); cin >> v;

    int ans = 0;
    for(int i = 1; i < n; i += 2) {
        ans ^= v[i];
    }

    if(ans) cout << "first" << endl;
    else cout << "second" << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}