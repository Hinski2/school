#include <bits/stdc++.h>
using namespace std;

constexpr int maks = 1e6 + 9;

int phi[maks];
void preprocess(){
    for(int i = 1; i < maks; i++){
        phi[i] = i;
    }

    for(int i = 2; i < maks; i++){
        if(phi[i] != i) continue; // nie liczba pierwsza skipp
        for(int j = i; j < maks; j += i)
            phi[j] -= phi[j] / i;
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    preprocess();

    int t; cin >> t;
    while(t--){
        int x; cin >> x;
        cout << phi[x] << '\n';
    }
}