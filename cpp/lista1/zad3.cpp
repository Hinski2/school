#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

enum class Name: uint16_t {Kuba, Ania, Janek, Monika, Adam};

void foo(string s, Name name) {
    switch (name) {
        case Name::Kuba:
            cout << s << " Kuba";
            break;

        case Name::Ania:
            cout << s << " Ania";
            break;

        case Name::Janek:
            cout << s << " Janek";
            break;

        case Name::Monika:
            cout << s << " Monika";
            break;

        case Name::Adam:
            cout << s << " Adam";
            break;
    }

    cout << endl;
}

int main() {
    foo("witaj", Name::Kuba);
}
