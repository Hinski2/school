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

unsigned n, m, out[M_INPUT], in[M_INPUT];
bool used[200'005];
vector<int> ans, G[M_INPUT];


void dfs(int v) {
    while(out[v]) {
        dfs(G[v][--out[v]]);
    }

    ans.push_back(v);
}

bool valid_data() {
    if(out[1] != in[1] + 1) return 0;
    if(in[n] != out[n] + 1) return 0;
    for(int i = 2; i < n - 2; i++)
        if(in[i] != out[i]) return 0;

    return 1;
}

int main() {
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;

    int idx = 0;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        out[a]++;
        in[b]++;
    }

    // validate data
    if(!valid_data()) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    // find ans
    ans.reserve(m + 2);
    dfs(1);

    if(ans.size() != m + 1) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    }
}
