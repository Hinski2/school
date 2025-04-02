#include<bits/stdc++.h>
using namespace std;

#define int long long 
constexpr int mod = 1e9 + 7;

int n, m;
int dp[1 << 20][20];
vector<int> G[405];

signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0, a, b; i < m; i++){
        cin >> a >> b; a--, b--;
        G[a].push_back(b);
    }

    // get ans
    dp[1][0] = 1;

    for(int mask = 0; mask < (1 << n); mask++){
        for(int last = 0; last < n; last++){
            if(!(mask & (1 << last))) continue;
            for(auto u: G[last]){
                if(mask & (1 << u)) continue;
                dp[mask | (1 << u)][u] = (dp[mask | (1 << u)][u] + dp[mask][last]) % mod;
            }
        }
    }

    // print ans
    cout << dp[(1 << n) - 1][n - 1] << endl;
}