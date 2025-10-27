#include<bits/stdc++.h>
#include <print>
using namespace std;

template<int n> struct harmonic_sum {
    using t = ratio_add<typename harmonic_sum<n - 1>::t, ratio<1, n>>;
};

template<> struct harmonic_sum<1> {
    using t = ratio<1, 1>;
};

int main() {
    using hs = harmonic_sum<46>::t;
    println("{}, {}", hs::num, hs::den);
}
