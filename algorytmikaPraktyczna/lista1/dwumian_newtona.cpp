#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr ll maks = 1e6 + 5;
constexpr ll mod = 1e9 + 7;


ll fact[maks];
ll inv(ll x){
    ll res = 1, exp = mod - 2;
    while(exp){
        if(exp & 1) res = res * x % mod;
        x = x * x % mod;
        exp /= 2;
    }

    return res;
}

ll solve(){
    ll a, b; cin >> a >> b;
    return (((fact[a] * inv(fact[a - b])) % mod ) * inv(fact[b])) % mod;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    fact[0] = 1;
    fact[1] = 1;
    for(int i = 2; i < maks; i++){
        fact[i] = fact[i - 1] * i;
        if(fact[i] >= mod) fact[i] %= mod;
    }

    int t; cin >> t;
    while(t--)
        cout << solve() << endl;
}