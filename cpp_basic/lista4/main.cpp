#include "tabbit.hpp"
#include <cstdint>
#include <exception>
using namespace std;

int main() {
    cout << "konstruktory" << endl;
    Tabbit a(23); cout << "a:\n" << a << endl;
    Tabbit b(uint64_t(2)); cout << "b: " << b << endl;
    Tabbit c(b); cout << "c: " << c << endl;

    cout << "zmiany wartości" << endl;
    b[0] = 1; cout << b << endl;
    b[1] = false; cout << b << endl;
    b[0] = b[1] = b[2] = b[3] = true; cout << b << endl;

    try {
        cout << b[10000] << endl;
    } catch(const exception& e) {
        cout << "git" << endl;
    }

    cout << "operatory" << endl;
    a = !a; cout << a << endl;
    b |= Tabbit(uint64_t(0b10000)); cout << b << endl; 

    cin >> b;
    cout << b << endl;
}
