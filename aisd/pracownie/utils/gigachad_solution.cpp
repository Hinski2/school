/*
    autor: Jakub Iliński 346796
*/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

// const 
constexpr int mak = 10'005;

// data
int n, vis[mak], dist;
bool ok[mak];
vector<pair<int, int>> G[mak]; // a -> {b, id}

// program
inline static void get_input(){
    cin >> n;
    for(int i = 0, a, id, b; i < n; i++){
        cin >> a >> id >> b;
        G[a].push_back({b, id});
    }
}

static bool dfs(int v){
    if(vis[v]){
        if(v == 0){
            ok[v] = 1;
            return 1;
        }

        return 0;
    }
    
    vis[v] = 1;
    for(auto &u: G[v]){
        dist++;
        ok[v] = dfs(u.first);
        if(ok[v]) return 1;
        dist--;
    }

    return 0;
}

static void retrive_path(int v){
    if(vis[v] == 2){ // it must be 0 (end of the cycle)
        return;
    }

    vis[v] = 2;
    for(auto &u: G[v]){
        if(u.first == 0 or (ok[u.first] and vis[u.first] != 2)){
            cout << v << ' ' << u.second << ' ' << u.first << endl;
            retrive_path(u.first);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    get_input();

    // make ans
    dfs(0);

    // print ans
    if(!ok[0]){
        cout << "BRAK" << endl; 
    } else {
        cout << dist << endl;
        retrive_path(0);
    }
}