#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return (16. * pow(x, 8)) / (2024 + pow(x, 8)); 
}


int main(){
    // problem sie pojawia dla dużych negatywnych x
    cout << setprecision(5) << fixed;
    for(double i = 0.; i <= 5; i += 0.5)
        cout << i << ' ' << f(i) << endl;
}