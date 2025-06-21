#include<bits/stdc++.h>
using namespace std;

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

void solve() {
    int n; cin >> n;
    vector<int> v(n); cin >> v;
    int ans = 0;
    for(auto u: v)
        ans ^= u;
    
    if(ans) cout << "first" << endl;
    else cout << "second" << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}