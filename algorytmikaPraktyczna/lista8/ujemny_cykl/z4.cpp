#include<bits/stdc++.h>
using namespace std;

constexpr int M_INPUT = 2505;
constexpr int64_t INF = 1LL * (1e9 + 7) * (1e9 + 7);
typedef int64_t i64;

struct Edge {
    int v, u;
    i64 w;

    friend istream& operator >> (istream &in, Edge &e) {
        in >> e.v >> e.u >> e.w;
        return in;
    }
};

template<typename T>
istream& operator >> (istream &in, vector<T> &v) {
    for(auto &u: v)
        cin >> u;

    return in;
}

int n, m, p[M_INPUT];
i64 dist[M_INPUT];

void bellman_ford(vector<Edge> &edges) {
    for(int k = 0; k < n - 1; k++){
        for(auto [a, b, w]: edges) {
            if(dist[b] > dist[a] + w) {
                dist[b] = dist[a] + w;
                p[b] = a;
            }
        }
    }

    int start = 0;
    for(auto [a, b, w]: edges) {
        if(dist[b] > dist[a] + w) {
            start = b;
            p[b] = a;
            break;
        }
    }

    if(!start) {
        cout << "NO" << endl;
        return;
    }

    cout << "YES" << endl;
    for(int i = 0; i < n; i++)
        start = p[start];

    vector<int> ans;
    ans.push_back(start);

    int curr = p[start];
    while(curr != start and curr) {
        ans.push_back(curr);
        curr = p[curr];
    }

    ans.push_back(start);
    reverse(ans.begin(), ans.end());
    for(auto u: ans) {
        cout << u << ' ';
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    vector<Edge> edges(m); cin >> edges;

    bellman_ford(edges); 
}