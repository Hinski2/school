#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    vector<double> x(2*n + 1);

    double I1 = x[2*n];
    double I2 = x[2*n-1];
    for(int k = n - 1; k > 0; k--){
        I1 *= x[2*k];
        I2 *= x[2*k - 1];
    }

    cout << I1 * I2 << endl;
}