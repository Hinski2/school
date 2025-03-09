#include <bits/stdc++.h>
using namespace std;

constexpr int max_k = 5;
vector<int> v[max_k];

int upper_bound(int vec_idx, int target){
    int l = 0, r = v[vec_idx].size() - 1;
    while(l < r){
        int mid = (l + r) / 2;
        if(v[vec_idx][mid] < target) l = mid + 1;
        else r = mid;
    } 

    return v[vec_idx][l];
}

int main(){
    // get_input
    int k; cin >> k;
    for(int i = 0; i < k; i++){
        int vector_sajz; cin >> vector_sajz;
        v[i].resize(vector_sajz);
        for(auto &u: v[i])
            cin >> u;
    }

    int a; cin >> a;
    // sprawdzenie czy szukanie ma sens
    for(int i = 0; i < k; i++)
        if(v[i].back() < a) return 1;
    

    // szukanie ma sens, robimy uppor bound 
    int r = a;
    for(int i = 0; i < k; i++){
        r = max(upper_bound(i, a), r);
    }

    // print ans
    cout << r - a << endl;
}