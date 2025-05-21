#include<bits/stdc++.h>
using namespace std;

template<typename T>
istream& operator >> (istream& in, vector<T>& v) {
    for(int i = 1; i < v.size(); i++)
        in >> v[i];
    return in;
}

template<typename T>
ostream& operator << (ostream& out, vector<T>& v) {
    for(auto &u: v)
        out << u << ' ';
    return out;
}

constexpr int M_INPUT = 1e5 + 10;

int col[M_INPUT], in[M_INPUT];
long long dp[M_INPUT], sum[M_INPUT];
vector<int> G[M_INPUT], GT[M_INPUT], SCCG[M_INPUT];
vector<int> q;

void dfs(int v) {
    col[v] = 1;
    for(auto u: G[v]) {
        if(col[u]) continue;
        dfs(u);
    }

    q.push_back(v);
}

void dfs(int v, int c) {
    col[v] = c;
    for(auto u: GT[v]) {
        if(col[u]) continue;
        dfs(u, c);
    }
}

void make_dp(int scc, int p = 0) {
    for(auto u: SCCG[scc]) {
        if(u == p) continue;
        if(dp[u] == 0) make_dp(u, p);
        dp[scc] = max(dp[scc], dp[u]);
    }

    dp[scc] += sum[scc];
}

int main() {
    // gat input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    vector<int> coin(n + 1); cin >> coin;

    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        GT[b].push_back(a);
    }

    // make scc
    for(int i = 1; i <= n; i++)
        if(!col[i]) dfs(i);

    memset(col, 0, sizeof(col));
    reverse(q.begin(), q.end());

    int c = 1;
    for(auto v: q) {
        if(!col[v]) {
            dfs(v, c);
            c++;
        }
    }

    // make gscc
    for(int i = 1; i <= n; i++) {
        sum[col[i]] += coin[i];
        for(auto u: G[i]) {
            if(col[u] != col[i]) {
                SCCG[col[i]].push_back(col[u]);
                in[col[u]]++;
            }
        }
    }

    // find leafs
    vector<int> q;
    for(int i = 1; i < c; i++)
        if(!in[i]) q.push_back(i);

    // make dp
    long long ans = 0;
    for(auto scc: q) {
        make_dp(scc);
        ans = max(ans, dp[scc]);
    }

    cout << ans << endl;
}
