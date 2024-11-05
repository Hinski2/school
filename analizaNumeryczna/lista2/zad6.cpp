#include <bits/stdc++.h>
using namespace std;

double len(double x, double y){
    double m = max(abs(x), abs(y));
    if(m == 0)  // jeśli m to dokładnie 0 (nie chodzi o to że m < eps)
        return 0.0;

    x /= m;
    y /= m;
    // teraz x i y <= 1

    return m * sqrt(x * x + y * y);
}

int main(){
    double x, y; cin >> x >> y;

    cout << setprecision(10) << fixed;
    cout << len(x, y) << endl;
}