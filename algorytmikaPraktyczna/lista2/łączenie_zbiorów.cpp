#include <bits/stdc++.h>
using namespace std;

constexpr int max_n = 2e5 + 15;

int n, ans[max_n], p[max_n];
set<int> colors[max_n];
vector<int> G[max_n];

int find(int x){
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

void onion(int a, int b){
    a = find(a);
    b = find(b);

    if(a == b) return;
    if(colors[a].size() < colors[b].size())
        swap(a, b);

    p[b] = a;
    for(auto u: colors[b]){
        colors[a].insert(u);
    }
}

void dfs(int v, int parent = -1){
    for(auto u: G[v]){
        if(u == parent) continue;
        dfs(u, v);
        onion(v, u);
    }

    ans[v] = colors[find(v)].size();
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n;
    for(int i = 1, x; i <= n; i++){
        cin >> x;
        colors[i].insert(x);
        p[i] = i;
    }

    for(int i = 1, a, b; i < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << ' ';
    cout << endl;
}