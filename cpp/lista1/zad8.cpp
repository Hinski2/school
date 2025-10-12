#include<bits/stdc++.h>
using namespace std;

auto bound(vector<int>::iterator begin, vector<int>::iterator end, int n) {
    // get l_bound
    auto l = begin, r = end - 1;
    while(l < r) {
        auto mid = l + (r - l) / 2;
        auto cmp = (*mid <=> n);
        if(cmp < 0) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }
    auto l_bound = l;

    // get r_bound
    l = begin, r = end - 1;
    while(l < r) {
        auto mid = l + (r - l + 1) / 2;
        auto cmp = (*mid <=> n);
        if(cmp > 0) {
            r = mid - 1;
        } else {
            l = mid;
        }
    }
    auto r_bound = r;
    if(*r_bound != n or *l_bound != n) {
        return pair{end, end};
    } else {
        return pair{l_bound, r_bound};
    }
}

int main() {
    vector<int> v = {1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 7, 7, 7, 8, 9};

    println("test 6:");
    auto [l, r] = bound(v.begin(), v.end(), 6);
    for(; l <= r and l != v.end(); l++) {
        println("number: {}, pos: {}", *l, l - v.begin());
    }

    println("test 5:");
    tie(l, r) = bound(v.begin(), v.end(), 5);
    for(; l <= r and l != v.end(); l++) {
        println("number: {}, pos: {}", *l, l - v.begin());
    }

    println("test 10:");
    tie(l, r) = bound(v.begin(), v.end(), 10);
    for(; l <= r and l != v.end(); l++) {
        println("number: {}, pos: {}", *l, l - v.begin());
    }
}