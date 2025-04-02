#include<bits/stdc++.h>
using namespace std;

constexpr int MAX_N = 2e5 + 5;

int n, dp[MAX_N];
vector<int> G[MAX_N];

void dfs_dp(int v, int p = -1){
    dp[v] = 1;
    for(auto u: G[v]){
        if(u == p) continue;
        dfs_dp(u, v);

        dp[v] = max(dp[u] + 1, dp[v]);
    }
}

int ans = 0
void dfs_diameter(int v, int p = -1){
    int a = 0, b = 0;
    for(auto u: G[v]){
        if(u == p) continue;
        if(dp[u] >= a){
            b = a;
            a = dp[u];
        }
        else if(dp[u] > b){
            b = dp[u];
        }

        dfs_diameter(u, v);
    }

    ans = max(ans, a + b);
}


int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1, a, b; i < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    // make dp
    dfs_dp(1);

    // find diameter
    dfs_diameter(1);

    cout << ans << endl;
}