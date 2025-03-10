#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 1e5 + 5;

int p[MAX], mini[MAX], maxi[MAX], sajz[MAX], edges[MAX];

int find(int x){
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

void onion(int a, int b){
    a = find(a);
    b = find(b);

    if(sajz[a] < sajz[b])
        swap(a, b);

    if(a == b){
        edges[a]++;
        return;
    }
    
    edges[a] = edges[a] + edges[b] + 1;
    sajz[a] += sajz[b];
    maxi[a] = max(maxi[a], maxi[b]);
    mini[a] = min(mini[a], mini[b]);
    p[b] = a;
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m; cin >> n >> m;

    // preprocess
    for(int i = 0; i < MAX; i++)
        p[i] = i, mini[i] = i, maxi[i] = i, sajz[i] = 1;
        
    // answear querries
    while(m--){
        int a, b; cin >> a >> b;
        onion(a, b);

        int parr = find(a);
        cout << 1ll * edges[parr] * (maxi[parr] - mini[parr]) << endl;
    }
}