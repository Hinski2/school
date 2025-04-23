#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 18;
int n, q;

struct Node{
    int max;
};

struct Tree{
    Node node[BASE * 2];
    void update_node(int v){
        node[v].max = max(node[v * 2].max, node[v * 2 + 1].max);
    }

    void update_tree(int idx){
        while(idx){
            update_node(idx);
            idx /= 2;
        }
    }

    void build(){
        for(int i = 1; i <= n; i++)
            cin >> node[BASE + i].max;

        for(int i = BASE - 1; i; i--)
            update_node(i);
    }

    int find_and_decrese(int val){
        int idx = 1;
        if(node[idx].max < val) return 0;
        
        while(idx < BASE){
            if(node[idx * 2].max >= val) idx *= 2;
            else idx = idx * 2 + 1;
        }

        node[idx].max -= val;
        update_tree(idx / 2);

        return idx - BASE;
    }
} tree;

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    tree.build();

    // answear querries
    while(q--){
        int x; cin >> x;
        cout << tree.find_and_decrese(x) << ' ';
    }

}