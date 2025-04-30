#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define int long long
constexpr int m_input = 1 << 19;

int n, q, t = 1;
int tin[m_input], tout[m_input];
int vals[m_input];
vector<int> G[m_input];


struct Tree{
    int sum[m_input * 2];

    void build(){
        for(int i = m_input - 1; i; i--)
            sum[i] = sum[i * 2] + sum[i * 2 + 1];
    }

    int get_sum(int v){
        int l = tin[v] + m_input, r = tout[v] + m_input, ans = sum[l];

        for(; l / 2 != r / 2; l /= 2, r /= 2){
            if(l % 2 == 0) ans += sum[l + 1];
            if(r % 2 == 1) ans += sum[r - 1];
        }

        return ans;
    }

    void update(int v, int x){
        v = tin[v] + m_input;
        sum[v] = x;

        for(v /= 2; v; v /= 2){
            sum[v] = sum[v * 2] + sum[v * 2 + 1];
        }
    }
    
} tree;

void dfs(int v, int p = 0){
    tree.sum[t + m_input] = vals[v];    
    tin[v] = t++;

    for(auto u: G[v]){
        if(u == p) continue;
        dfs(u, v);
    }

    tout[v] = t++;    
}

signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); 
    cin >> n >> q;

    for(int i = 1; i <= n; i++)
        cin >> vals[i];

    for(int i = 1, a, b; i < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    dfs(1);    
    tree.build();

    // answer queries
    while(q--){
        cin >> t;
        if(t == 1){
            int v, x; cin >> v >> x;
            tree.update(v, x);
        } else{
            int v; cin >> v;
            cout << tree.get_sum(v) << endl;
        }
    }
}