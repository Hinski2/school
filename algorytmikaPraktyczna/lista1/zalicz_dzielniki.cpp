#include <bits/stdc++.h>
using namespace std;

int solve(){
    int n; cin >> n;
    int ans = 0;
    for(int i = 1; i * i <= n; i++){
        if(n % i) continue;
        ans++;
        if(n / i != i) ans++;
    }

    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        cout << solve() << '\n';
}