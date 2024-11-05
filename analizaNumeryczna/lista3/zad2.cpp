#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-12;

pair<double, double> fun1(double a, double b, double c){
    double delta = sqrt(b * b - 4 * a * c);
    return {(-b - delta) / 2 * a, (-b + delta) / 2 * a};
}

inline double f(double a, double b, double c, double x){
    return a*x*x + b*x + c;
}

// wyszukiwaniem terrarnym
double find_zero(double a, double b, double c, double l, double r){
    double mid_1 = l + (r - l) / 3;
    double mid_2 = l + 2 * (r - l) / 3;

    if(abs(f(a, b, c, mid_1)) < abs(f(a, b, c, mid_2))){
        if(abs(f(a, b, c, mid_1)) < eps) return mid_1;
        return find_zero(a, b, c, l, l + (r - l) / 2);
    }
    else{
        if(abs(f(a, b, c, mid_2)) < eps) return mid_2;
        return find_zero(a, b, c, l + (r - l) / 2, r);    
    }
}

pair<double, double> fun2(double a, double b, double c){
    // zakładam że dostaliśmy f które ma miejsca zerowe
    double p = -b / (2 * a); // wzory vieta p = (x_1 + x_2) / 2
    double l, r, dist = 1.0;

    // szukamy odległości większej niż pomiędzy p a miejscem zerowym
    if(f(a, b, c, p) > 0)
        while(f(a, b, c, p + dist) >= 0) dist *= 2;
    else
        while(f(a, b, c, p + dist) <= 0) dist *= 2;

    r = p + dist;
    l = p - dist;

    return {find_zero(a, b, c, l, p), find_zero(a, b, c, p, r)};
}

int main(){
    // 0.001 2 0.001 przykład
    double a, b, c; cin >> a >> b >> c;
    cout << setprecision(12) << fixed;

    auto [x1, x2] = fun1(a, b, c);
    cout << "miejsca zerowe f(x): " << x1 << ' ' << x2 << endl;

    auto [y1, y2] = fun2(a, b, c);
    cout << "miejsca zerowe g(x): " << y1 << ' ' << y2 << endl;

}