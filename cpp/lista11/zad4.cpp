#include <bits/stdc++.h>
#include <print>
using namespace std;

template<size_t N, typename T = double> 
T inner(T *x, T *y) {
    if constexpr (N == 1) {
        return *x * *y;
    } else {
        return *x * *y + inner<N - 1, T>(x + 1, y + 1);
    }
}

int main() {
    // double
    double a[] = {4.4, 3., 1.};
    double b[] = {4.4, 3., 1.};
    println("{}", inner<3>(a, b));
    
    // int
    int c[] = {1, 2, 3};
    int d[] = {1, 2, 3};
    println("{}", inner<3, int>(c, d));

    // cpmplex
    complex<double> e[] = {{1, 1}, {1, 1}};
    complex<double> f[] = {{1, 1}, {1, 1}};
    // (1 + i) * (1 + i) = 1 + 2i + i^2 = 2i
    
    cout << inner<2, complex<double>>(e, f) << endl;
}
