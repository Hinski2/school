/*
    Jakub Iliński
    rozwiązanie: optymalne z użyciem max-heap
*/

#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define endl '\n'

struct heap{
    vector<pair<int, int>> vals;

    heap(int n){
        vals.resize(n + 1);
        for(int i = 1; i <= n; i++)
            vals[i] = {n + 1 - i, n + 1 - i};
    }

    void shift_down(int idx){
        int l = idx * 2, r = idx * 2 + 1;
        while((l < vals.size() and 1ll * vals[idx].fi * vals[idx].se < 1ll * vals[l].fi * vals[l].se) or 
              (r < vals.size() and 1ll * vals[idx].fi * vals[idx].se < 1ll * vals[r].fi * vals[r].se)){
            
            int s;
            if(r >= vals.size()) s = l;
            else s = 1ll * vals[l].fi * vals[l].se > 1ll * vals[r].fi * vals[r].se ? l : r;
            
            swap(vals[idx], vals[s]);
            idx = s;
            l = s * 2;
            r = s * 2 + 1;
        }
    }

    void print_top_k_vals(int k){
        long long last_printed_val = 1ll * vals[1].fi * vals[1].se + 1;
        for(int no_printed_vals = 0; no_printed_vals < k; no_printed_vals++){
            while(1ll * vals[1].fi * vals[1].se >= last_printed_val){
                vals[1].se--;
                shift_down(1);
            }

            last_printed_val = 1ll * vals[1].fi * vals[1].se;
            cout << last_printed_val << endl;
        }
    }
};

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;

    // compute ans
    heap h(n);
    h.print_top_k_vals(k);
}