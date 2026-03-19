#include <bits/stdc++.h>
using namespace std;

bool isPrime(int64_t numb) {
    for(int64_t i = 2; i * i <= numb; i++) {
        if(numb % i == 0) return 0;
    }

    return numb > 1;
}

int main(int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        try {
            const long long x = stoll(argv[i]); 
            if(isPrime(x)) cout << x << endl;
        } catch (invalid_argument const& e) {
            cerr << "invalid argument " << argv[i] << endl; 
        } catch(out_of_range const& e) {
            cerr << "out of range " << argv[i] << endl;
        }
    } 
}
