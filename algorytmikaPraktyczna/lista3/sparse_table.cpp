#include <bits/stdc++.h>
using namespace std;

constexpr int mak = 2e5 + 5;

int n, q;
int sparse_table[mak][19];
int LOG[mak];

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    for(int i = 1; i <= n; i++)
        cin >> sparse_table[i][0]; 

    // preprocess
    for(int i = 1; i < 19; i++){
        for(int j = 1; j + (1 << i) - 1 <= n; j++){
            sparse_table[j][i] = min(sparse_table[j][i - 1], sparse_table[j + (1 << (i - 1))][i - 1]);
        }
    }

    LOG[1] = 0;
    for(int i = 2; i < mak; i++){
        LOG[i] = LOG[i / 2] + 1;
    }

    // answear querries
    while(q--){
        int a, b; cin >> a >> b;
        if(a == b){ // edge case
            cout << sparse_table[a][0] << endl;
        } else {
            int table = LOG[b - a + 1];
            cout << min(sparse_table[a][table], sparse_table[b - (1 << table) + 1][table]) << endl;
        }
    }
}