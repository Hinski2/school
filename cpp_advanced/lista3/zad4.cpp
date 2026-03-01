#include <bits/stdc++.h>
#include <type_traits>
using namespace std;

// ptr
template<class Src, class Dst>
void transfer_impl(Src &&src, Dst &dst, true_type) {
    static_assert(is_convertible_v<remove_pointer_t<Src>, Dst>);
    if(src) dst = std::move(*src);
}

// val
template<class Src, class Dst>
void transfer_impl(Src &&src, Dst &dst, false_type) {
    static_assert(is_convertible_v<Src, Dst>);
    dst = std::move(src);
}

template<class Src, class Dst> 
void transfer(Src &&src, Dst &dst) {
    transfer_impl(std::forward<Src>(src), dst, is_pointer<Src>{});
}

int main() {
    string s, d;

    // wartość 
    s = "ab", d = "";
    transfer(s, d);
    println("s: {}\t d: {}", s, d);

    // wskaźnik 
    s = "ab", d = "";
    transfer(&s, d);
    println("s: {}\t d: {}", s, d);
}
