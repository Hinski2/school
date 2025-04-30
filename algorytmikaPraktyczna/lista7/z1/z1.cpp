#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
constexpr int m_input = 2e5 + 5;
constexpr int m_log = 19;

int n, q;
int pre[m_input][m_log];

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> q;
    
    for(int i = 2, x; i <= n; i++){
        cin >> x;
        pre[i][0] = x;
    }

    // preprocess
    for(int i = 1; i < m_log; i++){
        for(int v = 1; v <= n; v++){
            pre[v][i] = pre[pre[v][i - 1]][i - 1];
        }
    }

    auto get_p = [](int v, int k){
        for(int i = 0; i < m_log; i++){
            if(k & (1 << i)) v = pre[v][i];
        }

        return v ? v : -1;
    };

    // answer queries
    while(q--){
        int v, k; cin >> v >> k;
        cout << get_p(v, k) << endl;
    }
}