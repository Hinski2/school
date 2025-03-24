#include <bits/stdc++.h>
using namespace std;

constexpr int mak = 2e5 + 5;

struct struct_querry{
    int l;
    int r;
    int idx;
};

int n;
int arr[mak], ans[mak];
int sufix[mak], prefix[mak];

void conquer(int l, int r, vector<struct_querry> &querries){
    if(l == r){
        for(auto q: querries){
            ans[q.idx] = arr[q.l];
        }
    } 

    // divide querries into left_querries, querries, right_querries
    int mid = (r + l) / 2;
    vector<struct_querry> left_querries, right_querries;
    for(int i = 0; i < querries.size(); i++){
        if(querries[i].r < mid){
            left_querries.push_back(querries[i]);
            swap(querries[i--], querries.back());
            querries.pop_back();
        } else if(mid < querries[i].l) {
            right_querries.push_back(querries[i]);
            swap(querries[i--], querries.back());
            querries.pop_back();
        }
    }

    // compute prefix[], sufix[]
    prefix[mid] = sufix[mid] = arr[mid];
    for(int i = mid - 1; i >= l; i--)
        prefix[i] = min(prefix[i + 1], arr[i]);
    for(int i = mid + 1; i <= r; i++)
        sufix[i] = min(sufix[i - 1], arr[i]);

    // answear querries
    for(auto q: querries){
        ans[q.idx] = min(prefix[q.l], sufix[q.r]);
    }

    if(left_querries.size()) conquer(l, mid, left_querries);
    if(right_querries.size()) conquer(mid + 1, r, right_querries);
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int q; cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];

    vector<struct_querry> querries(q);
    for(int i = 0; i < q; i++){
        cin >> querries[i].l >> querries[i].r;
        querries[i].idx = i;
    }

    // conpute ans
    conquer(1, n, querries);

    // print
    for(int i = 0; i < q; i++)
        cout << ans[i] << endl;
}