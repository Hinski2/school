#include <bits/stdc++.h>
using namespace std;

void foo(double a, double b, double c) {
    if(auto delta = b * b - 4 * a * c; delta < 0) {
        println("delta < 0");
    } else if(delta == 0) {
        println("x1: {}, x2: {}", -b / 2 * a, -b / 2 * a);
    } else {
        double x1 = (-b - sqrt(delta)) / 2 * a;
        double x2 = (-b + sqrt(delta)) / 2 * a;
        println("x1: {}, x2: {}", x1, x2);
    }
}

int main() {
    foo(2.0, 5.0, 2.0);
}
