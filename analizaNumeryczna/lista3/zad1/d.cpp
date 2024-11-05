#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return 4. * cos(x) * cos(x) - 1;
}

double g(double x){
    return -2.*sqrt(3.)*pow(x - M_PI/3., 1) + 2.*pow(x - M_PI/3., 2) + 4.*sqrt(3.)/3.*pow(x-M_PI/3., 3);
}

int main(){
    // problem sie pojawia dla dużych negatywnych x
    cout << setprecision(16) << fixed;

    double x = M_PI / 3;
    cout << "f(x): " << f(x) << endl;
    cout << "g(x): " << g(x) << endl;

    cout << endl;
    x = .2;
    cout << "f(x): " << f(x) << endl;
    cout << "g(x): " << g(x) << endl;
    cout << endl;
}