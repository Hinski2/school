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

int in[M_INPUT];
vector<int> G[M_INPUT];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        G[a].push_back(b);
        in[b]++;
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= n; i++)
        if(in[i] == 0) pq.push(i);

    vector<int> ans;
    ans.reserve(n + 1);

    while(!pq.empty()) {
        auto v = pq.top(); pq.pop();
        ans.push_back(v);
        for(auto u: G[v]) {
            in[u]--;
            if(!in[u]) pq.push(u);
        }
    }

    if(ans.size() < n) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        cout << ans << endl;
    }
}
