#include <bits/stdc++.h>
using namespace std;

void foo(locale loc) {
    wcout.imbue(loc);
     
    // liczby 
    wcout << "liczby\n";
    wcout << 1000 << endl;
    wcout << 1000.1 << endl;
    wcout << 424242424.0 << endl;
    wcout << endl;

    // pieniądze
    wcout << "pieniadze\n";
    wcout << showbase;

    wcout << put_money(1000.43434) << endl;     // false -> symbol lokalny
    wcout << put_money(10.22, true) << endl;    // true -> symbol międzynarodowy
    wcout << endl;

    // datagodzina
    wcout << "datagodzina\n";
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    wcout << put_time(now, L"%c") << endl;
    wcout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);

    foo(locale("pl_PL.UTF-8"));
    foo(locale("ar_KW.UTF-8")); // arabski kuwejt
    foo(locale("ja_JP.UTF-8")); // japoński
    foo(locale("yo_NG")); // yoruby nigeria
}

