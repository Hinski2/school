#include <bits/stdc++.h>
using namespace std;

int main(){
    double I = log((double) 2025 / 2024);
    double ans[21] = {I};

    cout << 0 << ' ' << I << endl;
    for(int i = 1; i <= 20; i++){
        I = (double) 1 / i - I;
        ans[i] = I;
        cout << i << ' ' << I << endl;
    }
}