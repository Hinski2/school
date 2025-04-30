#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
constexpr int m_input = 1 << 19;

template<typename T> istream& operator >> (istream &in, vector<T> &v){
    for(auto &u: v)
        in >> u;
    return in;
}

int n, q;
int tin[m_input], t;
vector<int> G[m_input];

struct Node{
    int hi;
    int v;

    bool operator < (const Node &other) const {
        if(hi != other.hi)
            return hi < other.hi; 
        return v < other.v;
    }
};

struct Tree{
    Node node[m_input * 2]; 

    void build_leafs(int v, int p = 0, int h = 0){
        tin[v] = t;
        node[m_input + t++] = {h, v};

        for(auto u: G[v]){
            if(u == p) continue;
            build_leafs(u, v, h + 1);
            node[m_input + t++] = {h, v};
        }
    }

    void build(){
        for(int i = m_input - 1; i; i--)
            node[i] = min(node[i * 2], node[i * 2 + 1]);
    }

    Node find_lca(int a, int b) const {
        int l = tin[a] + m_input;
        int r = tin[b] + m_input;

        Node ans = min(node[l], node[r]);
        for(; l / 2 != r / 2; l /= 2, r /= 2){
            if(l % 2 == 0) ans = min(ans, node[l + 1]);
            if(r % 2 == 1) ans = min(ans, node[r - 1]);
        }

        return ans;
    }

    int dist(int a, int b) const {
        if(tin[a] > tin[b]) swap(a, b);

        Node lca = find_lca(a, b);
        const Node &n_a = node[tin[a] + m_input];
        const Node &n_b = node[tin[b] + m_input];

        return n_a.hi - lca.hi + n_b.hi - lca.hi;
    }

} tree;

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1, a, b; i < n; i++){
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    tree.build_leafs(1);
    tree.build();

    // answer queries
    while(q--){
        int a, b; cin >> a >> b;
        cout << tree.dist(a, b) << endl;
    }
}