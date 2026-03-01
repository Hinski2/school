#include <bits/stdc++.h>
#include <print>
using namespace std;

template<uint64_t N, uint64_t K>
struct BinCoef {
    static constexpr uint64_t value = BinCoef<N, K - 1>::value * (N - K + 1) / K;
};

template<uint64_t N>
struct BinCoef<N, 0> {
    static constexpr uint64_t value = 1;
};

int main() {
    println("{}", BinCoef<3, 2>::value);
}
