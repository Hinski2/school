#include <bits/stdc++.h>
using namespace std;

const double EPSILON = 1e-8;

// x - x^3/3! + x^5/5! - x^7/7! + ... 
double mysin(double x){
    double i = 2;
    double a = x, ans = x;
    while(abs(a) > EPSILON){
        a *= -x * x / (i * (i + 1));
        ans += a;
        i += 2;
    }

    return ans;
}


int main(){
    for(double i = 0; i < 2 * M_PI; i += 0.2)
        cout << i << ' ' << mysin(i) << ' ' << sin(i) << endl;
}