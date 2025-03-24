#include <bits/stdc++.h>
using namespace std;

constexpr int mak = 2e5 + 5;

struct struct_querry{
    int l;
    int r;
    int idx;
};

bool cmp(const struct_querry &a, const struct_querry &b){
    if(a.r != b.r) return a.r < b.r;
    return a.idx < b.idx;
}

int n;
int arr[mak], ans[mak], p[mak];

int find(int v){
    if(p[v] == v) return v;
    return p[v] = find(p[v]);
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int q; cin >> n >> q;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        p[i] = i;
    }

    vector<struct_querry> querries(q);
    for(int i = 0; i < q; i++){
        cin >> querries[i].l >> querries[i].r;
        querries[i].idx = i;
    }

    // sort querries
    sort(querries.begin(), querries.end(), cmp);

    // compute ans
    int querry_idx = 0;
    stack<int> s;
    for(int i = 1; i <= n; i++){
        while(!s.empty() and arr[s.top()] > arr[i]){
            // union 
            p[s.top()] = i;
            s.pop();
        }
        s.push(i);

        // answer all queries ending before i
        while(querry_idx < q and querries[querry_idx].r <= i){
            int rep = find(querries[querry_idx].l);
            ans[querries[querry_idx].idx] = arr[rep];
            querry_idx++;
        }
    }

    // print ans
    for(int i = 0; i < q; i++)
        cout << ans[i] << endl;
}