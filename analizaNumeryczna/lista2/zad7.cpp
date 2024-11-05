#include <bits/stdc++.h>
using namespace std;

double f(double x){
    return 8096.0 * (sqrt(pow(x, 13) + 4.0) - 2) / pow(x, 14);
}

double g(double x){
    return 8096.0 / (x * (sqrt(pow(x, 13) + 4.0) + 2.0));
}

int main(){
    double x = 1;
    cout << setprecision(16) << fixed;
    
    for(int i = 0; i < 10; i++, x /= 10){
        cout << "f(" << x << ") = " << f(x) << endl; 
        cout << "g(" << x << ") = " << g(x) << endl; 
        cout << endl;
    }
}