#include "zmienna.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << "test1" << endl;
    Zmienna a("a", 10.); 
    cout << a << endl;

    cout << "test2" << endl;
    cout << Zmienna() << endl;

    cout << "test3" << endl;
    Zmienna b(a);
    cout << b << endl;
    cout << a << endl;

    cout << "test4" << endl;
    Zmienna c(std::move(a));
    cout << c << endl;
    cout << a << endl;

    cout << "test5" << endl;
    Zmienna z("z", 5);
    z = 6;
    z = 7;
    cout << z << endl;
    z = 8;
    cout << z << endl;
    z.invert();
    cout << z << endl;
    z.negate();
    cout << z << endl;

    cout << "test" << endl;
    z.undo();
    z.undo();
    z.undo();
    cout << z << endl;
    z.undo();
    cout << z << endl;
    cout << z.get_val() << endl;
}
