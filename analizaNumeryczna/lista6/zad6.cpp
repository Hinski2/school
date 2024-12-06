#include<bits/stdc++.h>
using namespace std;

long long f(long long x){
    return 2024*pow(x, 8) - 1977*pow(x, 6) + 1945*pow(x, 3) + 1989*pow(x, 2) + 1410 * x;
}

int main(){
    long long x = -2024;
    cout << f(0) << endl;
}
