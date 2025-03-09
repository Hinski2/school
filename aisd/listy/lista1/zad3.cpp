#include <bits/stdc++.h>
using namespace std;

constexpr int max_n = 6;

int n, m, in[max_n];
vector<int> G[max_n];

int main(){
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        G[a].push_back(b);
        in[b]++;
    }

    vector<int> v[2], ans;
    for(int i = 1; i <= n; i++){
        if(in[i] == 0) v[0].push_back(i);
    }

    for(int now = 0; v[now].size(); now ^= 1){
        sort(v[now].begin(), v[now].end());

        for(auto node: v[now]){
            for(auto u: G[node]){
                in[u]--;
                if(in[u] == 0) v[now^1].push_back(u);
            }

            ans.push_back(node);
        }

        v[now].clear();
    } 

    for(auto u: ans)
        cout << u << ' ';
    cout << endl;
}