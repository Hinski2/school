#include<bits/stdc++.h>
using namespace std;

constexpr int M_INPUT = 2e5 + 5;
constexpr int64_t INF = (1e9 + 7) * (1e9 + 7);
typedef int64_t i64;

int n, m;
i64 dist[M_INPUT];
vector<pair<int, int>> G[M_INPUT]; // <to, weight>

void dijkstra() {
    auto cmp = [](const pair<int, i64> &a, const pair<int, i64> &b) {
        if(a.second != b.second) return a.second > b.second;
        return a.first > b.first;
    };

    priority_queue<pair<int, i64>, vector<pair<int, i64>>, decltype(cmp)> pq(cmp); // <v, weight>
    pq.push({1, 0});

    while(!pq.empty()){
        auto [v, weight] = pq.top(); pq.pop();
        if(dist[v] != INF) continue;

        dist[v] = weight;
        for(auto [u, d]: G[v]) {
            if(dist[u] != INF) continue;
            pq.push({u, d + weight});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, w; cin >> a >> b >> w;
        G[a].push_back({b, w});
    }

    for(int i = 1; i <= n; i++)
        dist[i] = INF;

    dijkstra();
    for(int i = 1; i <= n; i++)
        cout << dist[i] << ' ';
    cout << endl;
}
