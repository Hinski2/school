#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return 1.0 / (pow(x, 5) + sqrt(pow(x, 10) + 2024));
}

double g(double x){
    if(x < 0) return f(x);
    return (pow(x, 5) - sqrt(pow(x, 10) + 2024.)) / -2024.; //rozwiazanie problemu dla negatywnych x
}

int main(){
    // problem sie pojawia dla dużych negatywnych x
    cout << setprecision(16) << fixed;
    double x = -2.;

    for(int i = 1; i <= 10; i++){
        cout << "f(x): " << f(x) << endl;
        cout << "g(x): " << g(x) << endl;
        cout << endl;
        x *= 2.;
    }
}