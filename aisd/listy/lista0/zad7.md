# zad 7 

---

brut:
``` c++
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
```

binary lifting:
``` c++
int n, m;
int deep[max_n], up[max_n][max_log_n];
vector<int> G[max_n];

void preprocess(int v, int d, int p = 1){
    deep[v] = d;
    up[v][0] = p;

    for(int i = 1; i <= l; i++){
        up[v][i] = up[ up[v][i - 1] ][i - 1];
    }

    for(auto u: G[v]){
        preprocess(u, d + 1, v);
    }
}

int ancestor(int v, int d){
    for(int i = 0; i < max_log_n; i++){
        if(k & (1 << i)){
            v = up[v][i];
        }
    }

    return v;
}

bool check(){
    int v, u; cin >> v >> u;
    if(deep[v] - deep[u] < 0) return 0;

    return ancestor(v, deep[v] - deep[u]) == u;
}

int main(){
    // get input
    cin >> n >> m;
    for(int i = 0, parr, a; i + 1 < n; i++){
        cin >> parr >> a;
        p[a] = parr;
        G[parr].pb(a);
    }

    // preprocess (assume root = 1)
    preprocess(1, 1);

    // answer querries
    while(m--)
        cout << (check() ? "tak" : "nie") << endl;
}
```

optimal:
``` c++

int time;
int tin[max_n], tout[max_n];
void preprocess(int v){
    tin[v] = time++;
    for(auto u: v)
        preprocess(u);
    
    tout[v] = time++;
}

bool check(){
    int v, u; cin >> v >> u;
    return tin[v] < tin[u] and tout[u] < tout[v];
}

int main(){
    // get input
    cin >> n >> m;
    for(int i = 0, parr, a; i + 1 < n; i++){
        cin >> parr >> a;
        p[a] = parr;
        G[parr].pb(a);
    }

    // preprocess (assume root = 1)
    preprocess(1);

    // answer querries
    while(m--)
        cout << (check() ? "tak" : "nie") << endl;
}
```