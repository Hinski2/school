#include<bits/stdc++.h>
using namespace std;

constexpr uint32_t n = 40, m = 20;

struct Counter { 
    uint64_t c;
    Counter() : c(1) {}

    ~Counter() {
        cerr << c << endl;
    }

    void add() {
        c++;
    }

    friend ostream& operator << (ostream &out, const Counter& counter) {
        out << counter.c << ' ';
        return out;
    }

};

mt19937 rng;
static unique_ptr<Counter[]> foo(uint32_t m, unique_ptr<Counter[]> arr) {
    if(m == 0) return arr;
    uint32_t k = 0.1 * n;
    auto vec = ranges::iota_view{0u, n}
        | ranges::to<vector>();

    shuffle(vec.begin(), vec.end(), rng);
    for(uint32_t i = 0; i < k; i++)
        arr[vec[i]].add();

    return foo(m - 1, move(arr));
}

int main() {
    auto arr = make_unique<Counter[]>(n);
    arr = foo(m, move(arr));

    for(uint32_t i = 0; i < n; i++)
        cout << arr[i];
    cout << endl;
}