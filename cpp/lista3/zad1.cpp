#include<bits/stdc++.h>
using namespace std;
using lli = long long int;

int main() {
    println("min: {}, max: {}", numeric_limits<lli>::min(), numeric_limits<lli>::max());
    println("czy jest ze znakiem: {}", numeric_limits<lli>::is_signed);
    println("liczba bitów {}", numeric_limits<lli>::digits);
    println("liczba cyfr {}", numeric_limits<lli>::digits10);
}
