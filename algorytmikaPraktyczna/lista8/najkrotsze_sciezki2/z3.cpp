#include<bits/stdc++.h>
using namespace std;

constexpr int M_INPUT = 505;
constexpr int64_t INF = 1LL * (1e9 + 7) * (1e9 + 7);
typedef int64_t i64;

int n, m, q;
i64 dist[M_INPUT][M_INPUT];

void compute_dist(){
    // minimal dist i -> j using first k nodes
    for(int k = 1; k <= n; k++)
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            dist[i][j] = INF;

    for(int i = 1; i <= n; i++)
        dist[i][i] = 0;

    for(i64 i = 0, a, b, w; i < m; i++){
        cin >> a >> b >> w;
        dist[a][b] = min(w, dist[a][b]);
        dist[b][a] = min(w, dist[b][a]);
    }

    compute_dist();

    while(q--){
        int a, b; cin >> a >> b;
        cout << (dist[a][b] == INF ? -1 : dist[a][b]) << '\n';
    }
}
