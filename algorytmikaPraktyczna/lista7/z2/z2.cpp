#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
constexpr int m_input = 2e5 + 5;
constexpr int m_log = 19;

int n, q;
int h[m_input];
int pre[m_input][m_log];
vector<int> G[m_input];

void dfs(int v, int hi = 0){
    h[v] = hi;
    for(auto u: G[v]){
        dfs(u, hi + 1);
    }
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    
    for(int i = 2, x; i <= n; i++){
        cin >> x;
        pre[i][0] = x;
        G[x].push_back(i);
    }

    // preprocess
    dfs(1);
    for(int i = 0; i < m_log; i++)
        pre[1][i] = 1;

    for(int i = 1; i < m_log; i++){
        for(int v = 1; v <= n; v++){
            pre[v][i] = pre[pre[v][i - 1]][i - 1];
        }
    }


    auto get_p = [](int a, int b){
        if(h[a] > h[b]) swap(a, b); // b is lower
        int k = h[b] - h[a];
        for(int i = 0; i < m_log; i++){
            if(k & (1 << i)) b = pre[b][i];
        }

        if(a == b) return a;
        for(int i = m_log - 1; i >= 0; i--){
            if(pre[a][i] != pre[b][i])
                a = pre[a][i], b = pre[b][i];
        }

        return pre[a][0];
    };

    // answer queries
    while(q--){
        int a, b; cin >> a >> b;
        cout << get_p(a, b) << endl;
    }
}