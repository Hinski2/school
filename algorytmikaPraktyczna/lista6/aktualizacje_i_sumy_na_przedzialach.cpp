#include <bits/stdc++.h>
using namespace std;

#define int long long 
constexpr int BASE = 1 << 18;

int n, q_num;
struct Node{
    int sum;
    int lazy_set;
    int lazy_add;
};

struct Querry{
    int type;
    int l, r;
    int val;

    friend istream& operator >> (istream &in, Querry &q){
        cin >> q.type;
        if(q.type == 3){
            cin >> q.l >> q.r;
        } else {
            cin >> q.l >> q.r >> q.val;
        }
        return in;
    }
};

struct Tree{
    Node node[BASE * 2];

    void propagate_lazy(int idx, int i_l, int i_r){
        int mid = (i_l + i_r) / 2;

        if(node[idx].lazy_set){
            node[idx * 2].lazy_set = node[idx].lazy_set;
            node[idx * 2].lazy_add = 0;
            node[idx * 2 + 1].lazy_set = node[idx].lazy_set;
            node[idx * 2 + 1].lazy_add = 0;

            node[idx * 2].sum = node[idx].lazy_set * (mid - i_l + 1);
            node[idx * 2 + 1].sum = node[idx].lazy_set * (i_r - (mid + 1) + 1);
        }
        if(node[idx].lazy_add) {
           node[idx * 2].lazy_add += node[idx].lazy_add;
           node[idx * 2 + 1].lazy_add += node[idx].lazy_add;
           
           node[idx * 2].sum += node[idx].lazy_add * (mid - i_l + 1);
           node[idx * 2 + 1].sum += node[idx].lazy_add * (i_r - (mid + 1) + 1);
        }

        node[idx].lazy_add = 0;
        node[idx].lazy_set = 0;
    }

    int interval_sum(Querry q, int idx = 1, int i_l = 0, int i_r = BASE - 1){
        if(q.r < i_l or i_r < q.l) return 0;
        else if(q.l <= i_l and i_r <= q.r) return node[idx].sum;
        else{
            int mid = (i_l + i_r) / 2;
            propagate_lazy(idx, i_l, i_r);
            return interval_sum(q, idx * 2, i_l, mid) + interval_sum(q, idx * 2 + 1, mid + 1, i_r);
        }
    }

    void interval_add(Querry q, int idx = 1, int i_l = 0, int i_r = BASE - 1){
        if(q.r < i_l or i_r < q.l) return;
        else if(q.l <= i_l and i_r <= q.r){
            node[idx].lazy_add += q.val; 
            node[idx].sum += (i_r - i_l + 1) * q.val;
        } 
        else{
            int mid = (i_l + i_r) / 2;
            propagate_lazy(idx, i_l, i_r);

            interval_add(q, idx * 2, i_l, mid);
            interval_add(q, idx * 2 + 1, mid + 1, i_r);

            node[idx].sum = node[idx * 2].sum + node[idx * 2 + 1].sum;
        }
    }

    void interval_set(Querry q, int idx = 1, int i_l = 0, int i_r = BASE - 1){
        if(q.r < i_l or i_r < q.l) return;
        else if(q.l <= i_l and i_r <= q.r){
            node[idx].lazy_set = q.val;
            node[idx].lazy_add = 0;
            node[idx].sum = (i_r - i_l + 1) * q.val;
        } 
        else{
            int mid = (i_l + i_r) / 2;
            propagate_lazy(idx, i_l, i_r);

            interval_set(q, idx * 2, i_l, mid);
            interval_set(q, idx * 2 + 1, mid + 1, i_r);

            node[idx].sum = node[idx * 2].sum + node[idx * 2 + 1].sum;
        }
    }

    void build(){
        for(int i = 1; i <= n; i++)
            cin >> node[i + BASE].sum;
        
        for(int i = BASE - 1; i; i--)
            node[i].sum = node[i * 2].sum + node[i * 2 + 1].sum;
    }
} tree;

signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q_num;
    tree.build();

    // answear querries
    while(q_num--){
        Querry q; cin >> q;
        
        switch(q.type){
            case 1:
                tree.interval_add(q);
                break;
            case 2:
                tree.interval_set(q);
                break;
            case 3:
                cout << tree.interval_sum(q) << endl;
                break;
        }
    }

}