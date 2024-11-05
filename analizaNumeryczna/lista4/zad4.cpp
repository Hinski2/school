#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
inline double f(double x){
    return x * x - atan(x + 2);
}

double find(double l, double r){
    double mid;
    int i = 0;
    while(r - l > EPS){
        mid = (l + r) / 2;
        if(f(l) * f(mid) > 0) l = mid;  // takie same znaki
        else r = mid;                   // inne znaki 
        i++;
    }

    cout << i << "kroków" << endl;
    return (l + r) / 2;
}

int main(){
    cout << setprecision(7) << fixed;
    cout << "pierwsze miejsce zerowe: " << find(-2, 0) << endl;
    cout << "drugie miejsce zerowe: " << find(0, 2) << endl;
}