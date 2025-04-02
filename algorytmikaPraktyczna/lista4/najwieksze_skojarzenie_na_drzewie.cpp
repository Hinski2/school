#include<bits/stdc++.h>
using namespace std;

constexpr int mak = 2e5 + 5;

int n, dpt[mak], dpn[mak];
vector<int> G[mak];

void dfs(int v, int p = -1){
    for(auto u: G[v]){
        if(u == p) continue;
        dfs(u, v);
        dpn[v] += max(dpn[u], dpt[u]);
    }

    for(auto u: G[v]){
        if(u == p) continue;
        dpt[v] = max(dpt[v], dpn[v] - max(dpt[u], dpn[u]) + dpn[u] + 1);
    }
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 0, a, b; i + 1 < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1);
    cout << max(dpt[1], dpn[1]) << endl;
}