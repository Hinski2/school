#include <bits/stdc++.h>
using namespace std;
constexpr double sqrt2 = 1.4142135623730950488;

double mysqrt(double a){
    int c;                      // nasz wykładnik
    double m = frexp(a, &c);    // m to mantysa, frexp(double, referencja na wykładnik który zostanie nadpisany)
    // nasze m będzie z przedziału [0.5, 1), a c będzie bez biasu 

    // obliczanie sqrt(m)
    double x = 0.7;
    for(int i = 0; i < 4; i++)
        x = 0.5 * (x + m / x);
    
    // wynik to sqrt(m) * 2
    x *= (1 << c / 2);
    if(c & 1) x *= sqrt2;
    return x;
}

int main(){
    double a; cin >> a;
    cout << setprecision(12) << fixed;
    cout << sqrt(a) << endl;
    cout << mysqrt(a) << endl;
}