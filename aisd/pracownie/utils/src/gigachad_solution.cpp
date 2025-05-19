#include<bits/stdc++.h>
#include <cstdint>
using namespace std;

constexpr int M_INPUT = 1<<20;
#define endl '\n'

struct Querry{
    char type;
    int32_t val;
    int32_t p_0, p_1;

    friend istream& operator >> (istream &in, Querry &q){
        in >> q.type;
        if(q.type == 'I'){
            in >> q.p_0 >> q.val;
        } else if(q.type == 'D'){
            in >> q.p_0;
        } else{
            in >> q.p_0 >> q.p_1;
        }

        return in;
    }
};


struct Input{
    int32_t q;
    int32_t node[M_INPUT * 2];
    Querry querries[M_INPUT];

    void get_input(){
        cin >> q;
        for(int i = 0; i < q; i++){
            cin >> querries[i];

            if(querries[i].type == 'I'){
                node[M_INPUT + querries[i].p_0]++;
            }
        }
    }

    void build_tree(){
        for(int i = M_INPUT - 1; i; i--){
            node[i] = node[i * 2] + node[i * 2 + 1];
        }
    }

    int32_t get_extra_shift(int pos){
        
        pos += M_INPUT;
        int32_t sum = node[pos];

        int32_t start = pos;
        if(sum == 0) return 0;

        while(sum - 1 + node[pos + 1] > 0){
            pos++;
            sum = sum - 1 + node[pos];
        }

        return pos - start + 1;
    }


    int32_t get_leq_pos_sum(int pos){
        int r = pos + M_INPUT;
        int32_t sum = node[r];

        for(; r; r /= 2){
            if(r % 2 == 1) sum += node[r - 1];
        }

        return sum;
    }

    void decrement(int pos){
        pos += M_INPUT;
        node[pos]--;

        for(pos /= 2; pos; pos /= 2){
            node[pos] = node[pos * 2] + node[pos * 2 + 1];
        }
    }
}input;

struct Tss_node{
    int64_t sum;
    int32_t amm;
};

class Turbo_smart_struct{
private:
    Tss_node nodes[M_INPUT * 2];

    int32_t get_kth_idx(int k){
        int32_t pos = 1;
        while(pos < M_INPUT){ // while it's not a leaf
            if(nodes[pos * 2].amm >= k) {
                pos *= 2;
            } else {
                k -= nodes[pos * 2].amm;
                pos = pos * 2 + 1;
            }
        }

        return pos;
    }

    void querry_insert(Querry q){
        int32_t pos = get_kth_idx(q.p_0);

        int a = input.get_leq_pos_sum(q.p_0);
        input.decrement(q.p_0);
        int b = input.get_extra_shift(q.p_0); 

        pos += max(a, b);

        nodes[pos] = {q.val, 1};
        for(pos /= 2; pos; pos /= 2){
            nodes[pos] = {nodes[pos * 2].sum + nodes[pos * 2 + 1].sum, nodes[pos * 2].amm + nodes[pos * 2 + 1].amm};
        }
    }

    void querry_delete(Querry q){
        int32_t pos = get_kth_idx(q.p_0);
        nodes[pos] = {0, 0};
        for(pos /= 2; pos; pos /= 2){
            nodes[pos] = {nodes[pos * 2].sum + nodes[pos * 2 + 1].sum, nodes[pos * 2].amm + nodes[pos * 2 + 1].amm};
        }
    }

    int64_t querry_sum(Querry q){
        int32_t l = get_kth_idx(q.p_0);
        int32_t r = get_kth_idx(q.p_1);

        int64_t sum = nodes[l].sum;
        if(l != r) sum += nodes[r].sum;

        for(; l / 2 != r / 2; l /= 2, r /= 2){
            if(l % 2 == 0) sum += nodes[l + 1].sum;
            if(r % 2 == 1) sum += nodes[r - 1].sum;
        }

        return sum;
    }

public:
    void process_querry(Querry q){
        switch(q.type){
            case 'S':
                cout << querry_sum(q) << endl;
                break;
            case 'I':
                querry_insert(q);
                break;
            case 'D':
                querry_delete(q);
                break;
        }
    }
}tss;

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    input.get_input();
    input.build_tree();

    for(int i = 0; i < input.q; i++){
        tss.process_querry(input.querries[i]);
    }
}
