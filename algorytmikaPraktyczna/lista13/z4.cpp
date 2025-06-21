#include<bits/stdc++.h>
using namespace std;

constexpr int m_input = 5005;

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

int grundy[m_input];

inline void solve() {
    int n; cin >> n;
    int ans = grundy[n];

    if(ans) cout << "first" << endl;
    else cout << "second" << endl;
}

void preproces() {
    for(int i = 1; i < m_input; i++) {
        unordered_set<int> us;
        for(int j = 1; j <= i; j++) {
            int x = 0;
            if(j - 2 >= 1) x ^= grundy[j - 2];
            if(j + 2 < m_input) x ^= grundy[i - j - 1];
            if(j - 2 < 1 and j - 2 >= m_input) x = 1;
            us.insert(x);
        }

        int m = 0;
        while(us.contains(m)) m++;
        grundy[i] = m;
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    preproces();

    int t; cin >> t;
    while(t--)
        solve();
}