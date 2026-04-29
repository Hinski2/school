#include <iostream>
#include <stdexcept>
#include "kolor.hpp"
#include "piksel.hpp"

using namespace std;

int main() {
    KolorTN k(1, 1, 1, 1, "djdkfjdk");
    cout << k << endl;

    cout << "Kolor" << endl;
    Kolor k1(100, 150, 200);
    cout << k1 << 
    ++k1; cout << k1 << endl;
    --k1; cout << k1 << endl;

    cout << "combine: " << endl;
    cout <<Kolor::combine(k1, Kolor(50, 50, 50)) << endl;
    cout << Kolor::combine(Kolor(200, 200, 200), Kolor(200, 200, 200));

    cout << "KolorTransparentny" << endl;
    KolorTransparentny kt(255, 128, 0, 200); cout << kt << endl;
    kt.setAlfa(0); cout << kt << endl;

    cout << "KolorNazwany" << endl;
    KolorNazwany kn(80, 160, 240, "niebieski"); cout << kn << endl;
    kn.setNazwa("zielony"); cout << kn << endl;

    cout << "KolorTN" << endl;
    KolorTN ktn(10, 20, 30, 128, "czerwony"); cout << ktn << endl;

    cout << "Piksel" << endl;
    Piksel p1(100, 200), p2(400, 500); cout << p1 << " " << p2 << endl;
    cout << "dist(ref): " << Piksel::distance(p1, p2) << endl;
    cout << "dist(ptr): " << Piksel::distance(&p1, &p2) << endl;

    cout << "distLeft:" << p1.distLeft() << endl;
    cout << " distTop:" << p1.distTop() << endl;

    cout << "PikselKolorowy" << endl;
    PikselKolorowy pk(300, 400, 255, 100, 50); cout << pk << endl;
    pk.move(50, -100); cout << pk << endl;

    try { 
        Kolor bad(300, 0, 0);
     } catch(const invalid_argument& e) { 
        cout << e.what() << endl; 
    }

    try { 
        pk.move(10000, 0);
     } catch(const invalid_argument& e) {
         cout << e.what() << endl; 
    }

    return 0;
}
