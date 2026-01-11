#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

static constexpr double GAMMA = 0.5772156649;

complex<double> gamma_f(uint32_t max_itr, complex<double> z) {
    complex<double> ans = exp(-GAMMA * z) / z;

    for(uint32_t i = 1; i <= max_itr; i++) {
        double n = static_cast<double>(i);
        ans *= (n / (n + z)) * exp(z / n);
    }

    return ans;
}

complex<double> rev_gamma_f(uint32_t max_itr, complex<double> z) {
    complex<double> ans = z;
    for(uint32_t i = 1; i <= max_itr; i++) {
        double n = static_cast<double>(i);
        ans *= (1. + z / n) / pow(1 + 1 / n, z);
    }

    return ans;
}

int main() {
    auto a = gamma_f(50000, 0.5);
    auto b = rev_gamma_f(50000, 0.5);
    cout << a * b << endl;

    cout << gamma_f(50000, 0.5) << endl;        // \sqrt(\pi)
    cout << rev_gamma_f(50000, 0.5) << endl;    // \frac{1}{\sqrt(\pi)}
}
