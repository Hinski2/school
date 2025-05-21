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

unsigned n, m, in[M_INPUT];
bool used[200'005];
vector<int> ans;
vector<pair<int, int>> G[M_INPUT]; // <u, idx>

bool valid_data(){
    for(int i = 1; i <= n; i++) {
        if(in[i] % 2) return 0;
    }

    return 1;
}

void dfs(int v) {
    while(in[v]) {
        auto [u, idx] = G[v][--in[v]];
        if(used[idx]) continue;
        used[idx] = true;
        dfs(u);
    }

    ans.push_back(v);
}

int main() {
    // gat input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;

    int idx = 0;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[a].push_back({b, idx});
        G[b].push_back({a, idx++});
        in[a]++;
        in[b]++;
    }

    if(!valid_data()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    ans.reserve(m + 2);
    dfs(1);

    if(ans.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}