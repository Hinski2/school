#include <bits/stdc++.h>
using namespace std;

#define int long long 

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

void solve(){
    int a, b; cin >> a >> b;
    int x, y;
    int g = ext_gcd(a, b, x, y);
    cout << x << ' ' << y << ' ' << g << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        solve();
}