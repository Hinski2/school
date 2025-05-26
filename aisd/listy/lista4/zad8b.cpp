#include <bits/stdc++.h>
using namespace std;

struct Segment{
    int u, d;

    bool operator < (const Segment &other) const { 
        if(d != other.d) return d < other.d;
        return u < other.u;
    }
};

struct node{
    int max_lis; //longest increateg subsequence
    int amm;
};

constexpr int BASE = 1 << 20;
struct Tree{
    node tree[BASE * 2]; 

    void update_node(int idx){
        tree[idx].max_lis = max(tree[idx * 2].max_lis, tree[idx * 2 + 1].max_lis);
        tree[idx].amm = 0;
        if(tree[idx * 2].max_lis == tree[idx].max_lis) tree[idx].max_lis += tree[idx * 2].max_lis;
        if(tree[idx * 2 + 1].max_lis == tree[idx].max_lis) tree[idx].max_lis += tree[idx * 2 + 1].max_lis;
    }

    void update_tree(int k, int lis){
        k += BASE;
        tree[k].amm = 1;
        tree[k].max_lis = lis;

        for(k /= 2; k; k /= 2){
            update_node(k);
        }
    }

    int find_lis(int r){
        r += BASE;
        int lis = tree[r].max_lis;

        for(; r; r /= 2){
            if(r % 2 == 1) lis = max(lis, tree[r - 1].max_lis);
        }

        return lis;
    }

} tree;

int main(){
    // get input 
    int n; cin >> n;
    vector<Segment> segments(n); 
    for(int i = 0; i < n; i++){
        cin >> segments[i].u >> segments[i].d;
    }

    // preprocess
    sort(segments.begin(), segments.end());
    int idx = 1;
    for(auto &u: segments)
        u.u = idx++;

    // find ans
    for(auto s: segments){
        int lis = tree.find_lis(s.u - 1); 
        tree.update_tree(s.u, lis + 1);
    }

    // ans w tree[1]
}