#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()
#define endl '\n'
#define alf 'z' + 1
#define io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define yn (solve() ? "YES" : "NO")

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
const int mak = 2e5 + 7;

int n, k, ans;
bool ban[mak];
vector<pii> G[mak]; // {to, dist}


void wczytaj(){
    cin >> n >> k;
    for(int i = 1, a, b, c; i < n; i++){
        cin >> a >> b >> c;
        G[a].pb({b, c});
        G[b].pb({a, c});
    }     
}

void oblicz_odl_poddrzewo(int v, int p, map<int, int> &odl_poddrzewo, int odl){
    odl_poddrzewo[odl]++;

    for(auto [u, uc]: G[v]){
        if(!ban[u] && u != p) 
            oblicz_odl_poddrzewo(u, v, odl_poddrzewo, odl + uc);
    }
}

void polacz_odl(map<int, int> &odl, map<int, int> &odl_poddrzewo){
    for(auto [dystans, ile]: odl_poddrzewo){
        ans += odl[k - dystans] * ile;
    }

    for(auto [dystans, ile]: odl_poddrzewo){
        odl[dystans] += ile;
    }
}

void oblicz_przechodzace(int v){
    map<int, int> odl;
    odl[0]++;

    for(auto [u, uc]: G[v]){
        if(ban[u]) continue;

        map<int, int> odl_poddrzewo;
        oblicz_odl_poddrzewo(u, v, odl_poddrzewo, uc);
        polacz_odl(odl, odl_poddrzewo);
    }
}

void solve(int v){
    oblicz_przechodzace(v);
    ban[v] = true;

    for(auto [u, uc]: G[v]){
        if(ban[u]) continue;
        solve(u);
    }
}

int main(){
    // get input
    wczytaj();

    // compute ans
    solve(1);

    // print_ans
    cout << ans << endl;
}