#include <bits/stdc++.h>
using namespace std;

constexpr int max_input = 1e5 + 14;

int n, m, p[max_input], sajz[max_input], cc, max_size;

int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}

void onion(int a, int b){
    a = find(a);
    b = find(b);

    if(a == b) 
        return;

    if(sajz[a] < sajz[b])
        swap(a, b);
    
    sajz[a] += sajz[b];
    p[b] = a;

    cc--;
    max_size = max(max_size, sajz[a]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    cin >> n >> m;
    for(int i = 0; i < max_input; i++)
        p[i] = i, sajz[i] = 1;
    
    cc = n;
    max_size = 1;
    while(m--){
        int a, b; cin >> a >> b;
        onion(a, b);
        cout << cc << ' ' << max_size << endl; 
    }
}