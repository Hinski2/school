#include <bits/stdc++.h>
#include <cstdint>
#include <print>
#include <utility>
using namespace std;

template<uint64_t N>
constexpr uint64_t lucas() {
    return lucas<N - 1>() + lucas<N - 2>();
}

template<>
constexpr uint64_t lucas<1>() {
    return 1;
}

template<>
constexpr uint64_t lucas<0>() {
    return 2;
}

template<size_t... IDXS> 
void print_lucas(index_sequence<IDXS...>) {
    (println("{}: {}", IDXS, lucas<IDXS>()), ...);
}

int main() {
    print_lucas(make_index_sequence<5>{});
}
