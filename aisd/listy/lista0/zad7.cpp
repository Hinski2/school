#include<bits/stdc++.h>
using namespace std;

constexpr int mak = 1e6 + 5;

int n, m; 
int p[mak];

// czy v leży na ścieżce z u do korzenia
bool check(){
    int v, u; cin >> v >> u; 
    while(u != 0){
        if(u == v) return 1;
        u = p[u];
    }

    return 0;
}

int main(){
    cin >> n >> m;
    for(int i = 0, parr, a; i + 1 < n; i++){
        cin >> parr >> a;
        p[a] = parr;
    }

    while(m--)
        cout << (check() ? "tak" : "nie") << endl;
}
