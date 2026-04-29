#include "wymierna.hpp"
#include <limits.h>
using namespace obliczenia;
using namespace std;

int main() {
    cout << "\tpodstawy" << endl;
    Wymierna a(1, 4), b(1, 2);
    cout << a << std::endl;
    
    cout << "+" << a + b << std::endl;
    cout << "-" << a - b << std::endl;
    cout << "*" << a * b << std::endl;
    cout << "/" << a / b << std::endl;

    cout << "\ttestowanie wyjątków" << endl;
    try {
        Wymierna c; c / Wymierna(0);
    } catch (const dzielenie_przez_0& e) {
        cout << e.what() << endl;
    }

    try {
        Wymierna c(INT_MAX, 1); c + Wymierna(1, 1);
    } catch (const przekroczenie_zakresu& e) {
        cout << e.what() << endl;
    }

    try {
        Wymierna c(0); !c;
    } catch (const dzielenie_przez_0& e) {
        cout << e.what() << endl;
    }

    cout << "\twypisywanie" << endl;
    cout << !Wymierna(1, 3) << endl;
    cout << Wymierna(-1, 3) << endl;
    cout << Wymierna(2359348, 99900) << endl;
    cout << static_cast<int>(Wymierna(2359348, 99900)) << endl;
}