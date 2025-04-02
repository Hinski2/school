#include<bits/stdc++.h>
using namespace std;

int n;
int worker[20][20];
int dp[1 << 20];

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            cin >> worker[i][j];
    }

    // find ans
    for(int mask = 0; mask < (1 << n); mask++){
        int w_idx = __popcount(mask);
        for(int i = 0; i < n; i++){
            if(mask & (1 << i)) continue;
            dp[mask | (1 << i)] = max(dp[mask | (1 << i)], dp[mask] + worker[w_idx][i]);
        }
    }

    cout << dp[(1 << n) - 1] << endl;
}