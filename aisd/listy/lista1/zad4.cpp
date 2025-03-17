/*
    zakładam że krawędzie się nie powtarzają (jeśli się powtarzają 
    to wystarczy użyć seta podczas wczytywania)
*/

#include<bits/stdc++.h>
using namespace std;

constexpr int max_n = 7;

int n, m;
int in[max_n], out[max_n];
int idx[max_n];

vector<int> G[max_n];
vector<int> ans;

int max_color;
bool vis[max_n];
vector<int> G_nieskierowany[max_n];
vector<int> color[max_n];
vector<int> A;

void get_input(){
    cin >> n >> m;
    for(int i = 0, a, b; i < m; i++){
        cin >> a >> b;
        G[a].push_back(b);
        in[b]++;
        out[a]++;

        G_nieskierowany[a].push_back(b);
        G_nieskierowany[b].push_back(a);
    }
}

void update_graph(){
    for(int c = 1; c < max_color; c++){
        vector<int> more_in, more_out;
        for(auto u: color[c]){
            if(in[u] > out[u]) more_in.push_back(u);
            else if(in[u] < out[u]) more_out.push_back(u);
        }

        while(!(more_in.size() <= 1 and more_out.size() <= 1)){
            auto i = more_in.back(), o = more_out.back();
            G[i].push_back(o);
            out[i]++;
            in[o]++;

            if(in[i] == out[i]) more_in.pop_back();
            if(in[o] == out[o]) more_out.pop_back();
        }

        if(more_out.size()) A.push_back(more_out.back());
        else A.push_back(color[c][0]);
    }
}

void find_path(int v){
    for(; idx[v] < G[v].size();){
        idx[v]++;
        find_path(G[v][idx[v] - 1]);
    }

    ans.push_back(v);
}

void dfs_color(int v, int c){
    color[c].push_back(v);
    vis[v] = true;

    for(auto u: G_nieskierowany[v])
        if(!vis[u]) dfs_color(u, c);
}

void color_graph(){
    max_color = 1;
    for(int i = 1; i <= n; i++)
        if(!vis[i]){
            dfs_color(i, max_color);
            max_color++;
        }
}

int main(){
    get_input();
    color_graph();
    update_graph();

    // find ans
    for(auto a: A)
        find_path(a);

    // output
    reverse(ans.begin(), ans.end());
    for(auto u: ans)
        cout << u << ' ';
    cout << endl;
}