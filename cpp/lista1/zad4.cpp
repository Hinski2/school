#include<bits/stdc++.h>
#include <cstdint>
using namespace std;

int main() {
    auto lucas = [](auto self, uint64_t n) {
        if(n == 0) return 2;
        else if(n == 1) return 1;
        return self(self, n - 1) + self(self, n - 2);
    };

    cout << lucas(lucas, 0) << endl;
    cout << lucas(lucas, 1) << endl;
    cout << lucas(lucas, 40) << endl;
}
