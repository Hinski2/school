#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return pow(10, 8) * (exp(x) - exp(2*x));
}

double g(double x){
    return pow(10, 8) * exp(x) * (-x - pow(x, 2) / 2. - pow(x, 3) / 6. - pow(x, 4) / 24. - pow(x, 5) / 120.);
}

int main(){
    // problem sie pojawia dla dużych negatywnych x
    cout << setprecision(16) << fixed;

    for(double i = 0; i <= 4; i++){
        cout << "f(x): " << f(i) << endl;
        cout << "g(x): " << g(i) << endl;
        cout << endl;
    }
}