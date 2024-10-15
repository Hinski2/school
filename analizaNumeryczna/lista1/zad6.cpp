/*
    mamy szereg naprzemienny:
        S = pi = 4 * sum_k^inf (-1)^k / (2k + 1)
        a_k = 4 / (2k + 1)

    wiemy że jak przybliżamy szereg to:
        |S - S_n| <= a_{n+1}
    
    zależy nam na przybliżeniu 1e-6
    więc szukamy n dla którego: a_{n+1} <= 1e-6
        4 / (2n + 3) <= 1e-6
        n >= 1999998.5
        więc n = 1999999
*/

#include <bits/stdc++.h>
using namespace std;

double a(int k){
    return (double) 4 / 2 * k + 1;
}

int n = 1999999;
int main(){
    double sum = 0;
    for(int i = 0; i <= n; i++){
        sum += a(i);
    }

    cout << sum << endl;
    cout << M_PI << endl;
}