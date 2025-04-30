#include<bits/stdc++.h>
using namespace std;

constexpr int m_input = 2e5 + 5;
constexpr int m_log = 19;

template<typename T> istream& operator >> (istream &in, vector<T> &v){
    for(auto &u: v)
        in >> u;
    return in;
}

int n, m;
int pre[m_input][m_log], h[m_input];
int tin[m_input], tout[m_input];

vector<int> G[m_input];

int get_p(int a, int b){
    if(h[a] > h[b]) swap(a, b); // b in lower
    for(int i = 0, k = h[b] - h[a]; i < m_log; i++){
        if(k & (1 << i)) b = pre[b][i];
    }

    if(a == b) return b;
    for(int i = m_log - 1; i >= 0; i--){
        if(pre[a][i] != pre[b][i])
            a = pre[a][i], b = pre[b][i];
    }

    return pre[a][0];
}

bool is_ancestor(int a, int b){
    return tin[a] < tin[b] and tout[b] < tout[a];
}

struct Path {
    int a, b;
    static int val[m_input];

    friend istream& operator >> (istream &in, Path &p){
        in >> p.a >> p.b;
        return in;
    }


    void add_path(){
        if(h[a] > h[b]) swap(a, b);
        int lca = get_p(a, b);

        val[b]++;
        if(!is_ancestor(a, b)){
            val[a]++;
            val[lca]--;
        }
        val[pre[lca][0]]--;
    }

    static void sum(int v, int p = 0){
        for(auto u: G[v]){
            if(u == p) continue;
            sum(u, v);
            val[v] += val[u];
        }
    }
};

int Path::val[m_input];

void dfs(int v, int p = 0, int hi = 0, int t = 0){
    h[v] = hi;
    pre[v][0] = p;
    for(int i = 1; i < m_log; i++)
        pre[v][i] = pre[pre[v][i - 1]][i - 1];

    tin[v] = t++;
    for(auto u: G[v]){
        if(u == p) continue;
        dfs(u, v, hi + 1);
    }
    tout[v] = t++;
}

int main(){
    // get input 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 1, a, b; i < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    vector<Path> paths(m); cin >> paths;

    // preprocess 
    dfs(1);
    for(auto p: paths)
        p.add_path();

    Path::sum(1);

    for(int i = 1; i <= n; i++)
        cout << Path::val[i] << ' ';
    cout << endl;
}