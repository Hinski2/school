#include <bits/stdc++.h>
using namespace std;

int main() {
    auto newton = [](int n, int k) {
        map<pair<int, int>, int> mem;

        auto foo = [&](auto self, int n, int k) -> int {
            if(k == 0 or k == n) return 1;

            int x = mem.contains({n - 1, k - 1}) ? mem[{n - 1, k - 1}] : self(self, n - 1, k - 1);
            int y = mem.contains({n - 1, k}) ? mem[{n - 1, k}] : self(self, n - 1, k);

            return mem[{n, k}] = x + y;
        };

        return foo(foo, n, k);
    };
    
    println("{}", newton(1, 1));
    println("{}", newton(3, 2));
    println("{}", newton(2, 1));
    println("{}", newton(2, -1));
}
