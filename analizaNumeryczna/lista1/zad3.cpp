#include <bits/stdc++.h>
using namespace std;

double fd(double x){
    return (double) 1518 * (2 * x - sin(2 * x)) / (x * x * x);
} 

float fs(float x){
    return  1518 * (2 * x - sin(2 * x)) / (x * x * x);
} 

double pow(int x){
    double ans = 1;
    while(x--)
        ans /= 10;
    
    return ans;
}

int main(){
    for(int i = 11; i <= 20; i++){
        double x = pow(i);
        cout << i << ' ' << fs(x) << ' ' << fd(x) << endl;
    }
}

/*
    f(x)        = 1518 * (2 * x - sin(2 * x)) / (x * x * x)
    f(1e-11)    = 1518 * (2 * 1e-11 - sin(2 * 1e-11)) / (1e-11 * 1e-11 * 1e-11)
                = 1518 * (2e-11 - sin(2e-11)) / (1e-33)
                = 1518 * (2e-11 - sin(2e-11)) * 1e33

                ~ 1518 * (2e-11 - 0) * 1e33
                = 1518 * 2e-11 * 1e33 
                = 1518 * 2e22
                != 0  = fs(x) = fd(x)
*/