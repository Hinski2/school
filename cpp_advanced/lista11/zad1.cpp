#include <bits/stdc++.h>
#include <cstdint>
#include <print>
using namespace std;

// template<int64_t A, int64_t B>
// struct Nwd {
//     enum {
//         val = Nwd<B, A % B>::val
//     };
// };
//
// template<int64_t A>
// struct Nwd<A, 0> {
//     enum {
//         val = A
//     };
// };

template<int64_t A, int64_t B> 
struct Nwd {
    static constexpr int64_t val = Nwd<B, A % B>::val;
};

template<int64_t A> 
struct Nwd<A, 0> {
    static constexpr int64_t val = A;
};

int main() {
    // uint64_t val = Nwd<5, 4>::val;
    // println("{}", val);
    
    println("{}", Nwd<5, 4>::val);
}
