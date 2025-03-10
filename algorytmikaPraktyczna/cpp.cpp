#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct congruence {
    int a;
    int m;
};

int ext_gcd(int a, int b, int &x2, int &y2){
    if(b == 0){
        x2 = 1;
        y2 = 0;
        return a;
    } 

    int x1, y1;
    int g = ext_gcd(b, a % b, x1, y1);

    x2 = y1;
    y2 = x1 - y1 * (a / b);
    return g;
}

int inv(int numb, int mod){
    int x, y;
    int g = ext_gcd(numb, mod, x, y);
    x = (x % mod + mod) % mod; // bo x moze być mniejszy niż 0
    return x;
}


int solve(){
    int n; cin >> n;
    vector<congruence> v(n);
    int solution = 0, mod = 1;

    for(auto &u: v){
        cin >> u.m >> u.a;
        mod *= u.m;
    }

    for(auto u: v){
        int m_i = mod / u.m; 
        int a_i = u.a;
        int m_inv_i = inv(m_i, u.m);

        solution = (solution + (a_i * m_i % mod) * m_inv_i) % mod;
    }

    return solution;
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        cout << solve() << endl;
}