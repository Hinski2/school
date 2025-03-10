#include <bits/stdc++.h>
using namespace std;

constexpr int max_input = 1e6 + 15;
int n, m;
int sajz[max_input], p[max_input], parity[max_input];

int find(int x){
    if(p[x] == x) return x;

    int root = find(p[x]);
    parity[x] = (parity[x] + parity[p[x]]) % 2;
    return p[x] = root;
}

void onion(int a, int b, int dist){
    auto pa = find(a);
    auto pb = find(b);

    if(sajz[a] < sajz[b])
        swap(a, b);

    parity[pb] = (parity[a] + parity[b] + dist) % 2;
    sajz[pa] += sajz[pb];
    p[pb] = pa;
}

int main(){
    cin >> n >> m;

    for(int i = 0; i < max_input; i++)
        p[i] = i, sajz[i] = 1;

    int ans = m;
    for(int i = 1; i <= m; i++){
        int a, b, dist; cin >> a >> b >> dist;
        auto pa = find(a);
        auto pb = find(b);

        if(pa == pb and (parity[a] + parity[b]) % 2 != dist){
            ans = min(ans, i - 1);
        } else if(pa != pb){
            onion(a, b, dist);
        }
    }

    cout << ans << endl;
}