#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 16;

int n, m, q_num;
struct Node{
    int max;
    int lazy;
};

struct Querry{
    int l, r;
    int amm;

    friend istream& operator >> (istream &in, Querry &q){
        cin >> q.l >> q.r >> q.amm;
        q.l++;
        return in;
    }
};

struct Tree{
    Node node[BASE * 2];

    void propagate_lazy(int idx){
        node[idx * 2].lazy += node[idx].lazy;
        node[idx * 2 + 1].lazy += node[idx].lazy;

        node[idx * 2].max += node[idx].lazy;
        node[idx * 2 + 1].max += node[idx].lazy;

        node[idx].lazy = 0;
    }

    int interval_max(Querry q, int idx = 1, int i_l = 0, int i_r = BASE - 1){
        if(q.r < i_l or i_r < q.l) return 0;
        else if(q.l <= i_l and i_r <= q.r) return node[idx].max;
        else{
            int mid = (i_l + i_r) / 2;

            propagate_lazy(idx);
            return max(interval_max(q, idx * 2, i_l, mid), interval_max(q, idx * 2 + 1, mid + 1, i_r));
        }
    }

    void interval_add(Querry q, int idx = 1, int i_l = 0, int i_r = BASE - 1){
        if(q.r < i_l or i_r < q.l) return;
        else if(q.l <= i_l and i_r <= q.r){
            node[idx].lazy += q.amm;
            node[idx].max += q.amm;
        } 
        else{
            int mid = (i_l + i_r) / 2;
            propagate_lazy(idx);

            interval_add(q, idx * 2, i_l, mid);
            interval_add(q, idx * 2 + 1, mid + 1, i_r);

            node[idx].max = max(node[idx * 2].max, node[idx * 2 + 1].max);
        }
    }

    bool try_book(Querry q){
        if(interval_max(q) + q.amm > m) return 0;
        interval_add(q);
        return 1;
    }
} tree;

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> m >> q_num;

    // answear querries
    while(q_num--){
        Querry q; cin >> q;
        cout << (tree.try_book(q) ? "T\n" : "N\n");
    }

}