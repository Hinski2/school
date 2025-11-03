#include <bits/stdc++.h>
using namespace std;

int main() {
    auto try_get_first = []<typename T>(vector<T> &v, T default_v) -> T {
        return v.empty() ? default_v : v.front();
    };

    vector<int> v = {1, 2, 3};
    println("{}", try_get_first(v, 0));
    
    v.clear();
    println("{}", try_get_first(v, 0));
}
