#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>; // <val, occ>

vector<pii> foo(vector<int> &v) {
    unordered_map<int, int> occ;
    for(auto u: v) occ[u]++;

    vector<pii> res;
    for(auto &[k, v]: occ) {
        if(res.empty() or v > res.front().second) {
            res.clear();
            res.push_back({k, v});
        } else if(v == res.front().second) {
            res.push_back({k, v});
        }
    }
    
    return res;
}

int main() {
    vector<int> v = {1, 1, 3, 5, 8, 9, 5, 8, 8, 5};
    for(auto &[val, occ]: foo(v)) 
        cout << "val: " << val  
             << " occ: " << occ 
             << endl;
}
