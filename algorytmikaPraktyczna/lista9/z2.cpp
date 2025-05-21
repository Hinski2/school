#include<bits/stdc++.h>
using namespace std;

template<typename T>
istream& operator >> (istream& in, vector<T>& v) {
    for(auto &u: v)
        in >> u;
    return in;
}

template<typename T>
ostream& operator << (ostream& out, vector<T>& v) {
    for(auto &u: v)
        out << u << ' ';
    return out;
}

constexpr int M_INPUT = 1e5 + 10;

int col[M_INPUT];
vector<int> G[M_INPUT], GT[M_INPUT];
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


int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        GT[b].push_back(a);
    }

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

    c = 1;
    map<int, int> dict;
    for(int i = 1; i <= n; i++) {
        if(!dict.count(col[i])) {
            dict[col[i]] = c++;
        } 

        col[i] = dict[col[i]];
    }

    cout << c - 1 << endl;
    for(int i = 1; i <= n; i++)
        cout << col[i] << ' ';
    cout << endl;
}
