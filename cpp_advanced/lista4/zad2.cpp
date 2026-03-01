#include <bits/stdc++.h>
using namespace std;

template<class A, class B>
struct Po_kolei{
    A a;
    B b;

    Po_kolei(A a, B b) : a(a), b(b) {}

    template<typename T>
    T operator () (T x) {
        return b(a(x));
    }
    
};

int main() {
    auto add2 = [](int x) {
        return x + 2;
    };    

    auto mult2 = [](int x) {
        return x * 2;
    };

    println("{}", Po_kolei(add2, mult2)(0));
    println("{}", Po_kolei(mult2, add2)(0));
    println("{}", Po_kolei(Po_kolei(mult2, add2), add2)(0));
    println("{}", Po_kolei(Po_kolei(add2, mult2), add2)(0));
    println("{}", Po_kolei(Po_kolei(add2, mult2), Po_kolei(add2, mult2))(0));
}
