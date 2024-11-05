#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return 6. * pow(x, -3) * (asin(x) - x);
}

double g(double x){
    return 6. * pow(x, -3) * (pow(x, 3)/6. + pow(x, 5)/120. + pow(x, 7)/5040.);
}

int main(){
    // problem sie pojawia dla dużych negatywnych x
    cout << setprecision(16) << fixed;

    for(double i = 0, x = 0; i <= 4; i++, x += 0.0001){
        cout << "f(x): " << f(x) << endl;
        cout << "g(x): " << g(x) << endl;
        cout << endl;
    }
}