/*
    Jakub Iliński
    rozwiazanie: brut
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> v;

void solve(){
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            v.push_back(1ll * i * j);
}

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    // compute vals
    solve();

    // sort vals
    sort(v.begin(), v.end(), greater<long long>());

    // print ans
    long long last_val = v.front() + 1, idx = 0;
    for(int i = 0; i < k; i++){
        while(v[idx] == last_val){
            idx++;
        }
        last_val = v[idx];
        cout << v[idx++] << endl;
    }

}