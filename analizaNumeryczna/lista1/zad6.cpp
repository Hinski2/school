/*
    mamy szereg naprzemienny:
        S = pi = 4 * sum_k^inf (-1)^k / (2k + 1)
        a_k = 4 / (2k + 1)

    wiemy że jak przybliżamy szereg to:
        |S - S_n| <= a_{n+1}
    
    zależy nam na przybliżeniu 1e-6
    więc szukamy n dla którego: a_{n+1} <= 1e-6
        4 / (2n + 3) <= 1e-6
        n >= 1999999.5
        więc n = 2`000`00
*/

#include <bits/stdc++.h>
using namespace std;

double a(int k){
    double ans = (double) 4 / (2 * k + 1);
    if(k % 2) return -ans;
    return ans;
}

int main(){
    const double eps = 1e-6;
    double sum = 0;
    int i = 0;
    cout << setprecision(16);
    while(abs(sum - M_PI) > eps){
        sum += a(i++);
        cout << sum << endl;
    }
    cout << i << endl;
}