#include<bits/stdc++.h>
using namespace std;

constexpr int m_input = 1e6 + 5;

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

int win[m_input];

void solve() {
    int n; cin >> n;
    vector<int> v(n); cin >> v;

    int ans = 0;
    for(auto u: v)
        ans ^= win[u];

    if(ans) cout << "first" << endl;
    else cout << "second" << endl;
}

void preproces() {
    win[1] = win[3] = 1;
    win[4] = 2;
    
    for(int i = 5; i < m_input; i++) {
        int nums[5] = {0};
        nums[win[i - 1]] = 1;
        nums[win[i - 3]] = 1;
        nums[win[i - 4]] = 1;

        int m = 0;
        while(m < 5 and nums[m]) m++;
        win[i] = m;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    preproces();

    int t; cin >> t;
    while(t--)
        solve();
}