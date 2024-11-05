#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;

double sqrt_inv(double a){
    double x = 1./a;
    for(int i = 1; i <= 5; i++){
        x = x*(3. - a * x * x) * 0.5;
    }
    return x;
}


int main(){
    double a; cin >> a;
    cout << setprecision(10) << fixed;
    cout << "z dzieleniem:  " << 1. / sqrt(a) << endl;
    cout << "bez dzielenia: " << sqrt_inv(a) << endl;
}