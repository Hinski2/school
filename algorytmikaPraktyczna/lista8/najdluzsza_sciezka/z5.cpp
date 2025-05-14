#include<bits/stdc++.h>
using namespace std;

constexpr int M_INPUT = 2505;
constexpr int64_t INF = 1LL * (1e9 + 7) * (1e9 + 7);
typedef int64_t i64;

vector<int> G[M_INPUT], GT[M_INPUT];
struct Edge {
    int v, u;
    i64 w;

    friend istream& operator >> (istream &in, Edge &e) {
        in >> e.v >> e.u >> e.w;
        G[e.v].push_back(e.u);
        GT[e.u].push_back(e.v);
        return in;
    }
};

template<typename T>
istream& operator >> (istream &in, vector<T> &v) {
    for(auto &u: v)
        cin >> u;

    return in;
}

int n, m;
i64 dist[M_INPUT];
bool rf1[M_INPUT], cgn[M_INPUT];
int vis[M_INPUT];

i64 belman_ford(vector<Edge> &edges) {
    dist[1] = 0; 

    for(int k = 0; k < n - 1; k++)
        for(auto [a, b, w]: edges) 
            if(dist[b] < dist[a] + w){
                dist[b] = dist[a] + w;
            }

    for(auto [a, b, w]: edges)
        if(dist[b] < dist[a] + w and rf1[b] and cgn[b]) return -1;

    return dist[n]; 
}

void check1(int v) {
    vis[v] = 1;
    rf1[v] = 1;

    for(auto u: G[v]) 
        if(vis[u] != 1) check1(u);
}

void checkn(int v) {
    vis[v] = 2;
    cgn[v] = 1;

    for(auto u: GT[v])
        if(vis[u] != 2) checkn(u);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    vector<Edge> edges(m); cin >> edges;

    check1(1);
    checkn(n);

    for(int i = 0; i <= n; i++)
        dist[i] = -INF;

    cout << belman_ford(edges) << endl;
}