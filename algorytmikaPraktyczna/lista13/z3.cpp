#include<bits/stdc++.h>
using namespace std;

constexpr int m_input = 1e6 + 5;
constexpr int board = 1001;

istream& operator >> (istream& in, vector<int> &v) {
    for(auto &u: v) 
        in >> u;
    return in;
}

int grundy[board][board];

void solve() {
    int n; cin >> n;

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ans ^= grundy[x][y];
    }

    if(ans) cout << "first" << endl;
    else cout << "second" << endl;
}



void preproces() {
    auto ok_pos = [](int x, int y) {
        return 1 <= x and x <= 1000 and 1 <= y and y <= 1000;
    };

    auto mex = [](int* tab) {
        int m = 0;
        while(m < 5 and tab[m]) m++;
        return m;
    };

    auto compute = [&](int i, int j) {
        if(!ok_pos(i, j)) return;

        int tab[5] = {0};
        if(ok_pos(i - 2, j - 1)) tab[grundy[i - 2][j - 1]] = 1;
        if(ok_pos(i - 2, j + 1)) tab[grundy[i - 2][j + 1]] = 1;
        if(ok_pos(i - 1, j - 2)) tab[grundy[i - 1][j - 2]] = 1;
        if(ok_pos(i + 1, j - 2)) tab[grundy[i + 1][j - 2]] = 1;

        grundy[i][j] = mex(tab);
    };

    for(int k = 2; k <= 2000; k++) {
        for(int i = 1; i <= 1000; i++) {
            compute(i, k - i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    preproces();

    int t; cin >> t;
    while(t--)
        solve();
}