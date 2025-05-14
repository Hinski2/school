#include<bits/stdc++.h>
using namespace std;

constexpr int M_INPUT = 2e5 + 5;
constexpr int64_t INF = (1e9 + 7) * (1e9 + 7);
typedef int64_t i64;

int n, m;
bool vis[M_INPUT][2];
vector<pair<int, int>> G[M_INPUT]; // <to, weight>

struct State{
    bool used;
    int v;
    i64 dist;

    bool operator < (const State &other) const {
        if(dist != other.dist) return dist > other.dist;
        if(used != other.used) return used > other.used;
        return v > other.v;
    }
};

pair<i64, i64> dijkstra(){
    priority_queue<State> pq;  // <used, v, dist>
    pq.push({0, 1, 0});

    i64 ans[2];
    while(!pq.empty()){
        auto [used, v, dist] = pq.top(); pq.pop();
        if(vis[v][used]) continue;

        vis[v][used] = true;
        if(v == n) ans[used] = dist;

        for(auto [u, w]: G[v]) {
            if(!vis[u][used]) pq.push({used, u, dist + w});
            if(!vis[u][1] and !used) pq.push({1, u, dist + w / 2});
        }
    }

    return make_pair(ans[0], ans[1]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        G[a].push_back({b, w});
    }

    pair<i64, i64> ans = dijkstra();
    cout << min(ans.first, ans.second) << endl;
}