#include <bits/stdc++.h>
using namespace std;

static complex<double> zeta_reiman_f(uint32_t max_itr, complex<double> z) {
    complex<double> ans = 1. / (1. - pow(2, 1. - z));
    complex<double> sum = 0.;

    for(uint32_t i = 1; i <= max_itr; i++) {
        double n = static_cast<double>(i);
        sum += (i % 2 ? 1. : -1.) / pow(n, z);
    }

    return ans * sum;
}

static valarray<complex<double>> zeta_reiman_f(uint32_t max_itr, const valarray<complex<double>> &arr) {
    uint32_t n = arr.size();
    valarray<complex<double>> ans(n);
    
    for(uint32_t i = 0; i < n; i++) {
        ans[i] = zeta_reiman_f(max_itr, arr[i]);
    }

    return ans;
}

static valarray<complex<double>> linespace(double start, double end, double jump) {
    assert(start <= end && "error: start >= end");
    uint32_t no = (end - start) / jump;

    valarray<complex<double>> arr(no);
    for(uint32_t i = 0; i < no; i++) {
        arr[i] = complex<double>(0.5, start + i * jump);
    }

    return arr;
}

int main() {
    auto arr = linespace(-30, 30, 0.02);
    auto zetas = zeta_reiman_f(1000, arr);

    ofstream file("zeta.csv");
    for(uint32_t i = 0; i < arr.size(); i++) {
        file << arr[i].imag() << ';' << zetas[i].real() << ';' << zetas[i].imag() << endl;
    }
}
