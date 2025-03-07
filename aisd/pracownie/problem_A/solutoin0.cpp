/*
    autor: Jakub Iliński 346796
*/

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

// const 
constexpr int mak = 10'005;

// data
int n, vis[mak];
vector<pair<int, int>> G[mak]; // a -> {b, id}

struct conn{
    int a;
    int id;
    int b;
};
vector<conn> road_now, road_best;

// program
inline static void get_input(){
    cin >> n;
    for(int i = 0, a, id, b; i < n; i++){
        cin >> a >> id >> b;
        G[a].push_back({b, id});
    }
}

static void dfs(int v){
    if(vis[v]){
        if(v == 0 and road_best.size() == 0){
            road_best = road_now;
        }

        return;
    }
    
    vis[v] = 1;
    for(auto &u: G[v]){
        road_now.push_back({v, u.second, u.first});
        dfs(u.first);
        road_now.pop_back();
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    get_input();

    // make ans
    dfs(0);

    // print ans
    if(road_best.size() == 0){
        cout << "BRAK" << endl; 
    } else {
        cout << road_best.size() << endl;
        for(auto u: road_best)
            cout << u.a << ' ' << u.id << ' ' << u.b << endl;
    }
}