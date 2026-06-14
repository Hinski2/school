#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

struct Trojkat {
    double a, b, c;
    string nazwa;

    Trojkat(double a = 1, double b = 1, double c = 1, string nazwa = "")
        : a(a), b(b), c(c), nazwa(nazwa)
    {
        if(a <= 0 or b <= 0 or c <= 0 or a + b <= c or a + c <= b or b + c <= a) {
            throw logic_error("Error: invalid triangle");
        }
    }

    double obwod() const {
        return a + b + c;
    }

    double pole() const {
        double p = obwod() / 2.0;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    }

    friend bool operator<(const Trojkat &x, const Trojkat &y) {
        if(x.nazwa != y.nazwa) return x.nazwa < y.nazwa;
        if(x.a != y.a) return x.a < y.a;
        if(x.b != y.b) return x.b < y.b;
        return x.c < y.c;
    }

    Trojkat(const Trojkat &x) = default;

    friend ostream &operator<<(ostream &out, const Trojkat &t) {
        out << '['
            << t.nazwa << "; "
            << t.obwod() << "; "
            << t.pole() << ']';

        return out;
    }
};



void zadanie_a() {
    vector<int> v = {1, 2, 3, 4, 5};

    auto f = bind(
        plus<int>{},
        bind(multiplies<int>{}, 3, std::placeholders::_1),
        1
    );

    transform(v.begin(), v.end(), v.begin(), f);

    cout << "a: " << endl;
    for (int x : v)
        cout << x << ' ';
    cout << '\n';
}

template <typename T>
struct Sum {
    T sum{};
    size_t no = 0;

    void operator()(const T &x) {
        sum += x;
        no++;
    }

    T get_sum() const {
        return sum;
    }

    size_t get_no() const {
        return no;
    }

    double avg() const {
        if(no == 0){
            throw logic_error("Error: no data");
        }

        return static_cast<double>(sum) / static_cast<double>(no);
    }

    void reset() {
        sum = T{};
        no = 0;
    }
};

void zadanie_b() {
    deque<int> i_vals = {1, 2, 3, 4, 5, 1};
    list<double> d_vals = {1.5, 2.5, 3.5, 4.5};
    Sum<int> i = for_each(i_vals.begin(), i_vals.end(), Sum<int>{});

    cout << "\nb: " << endl;
    cout << "sum: " << i.get_sum() << endl;
    cout << "no: " << i.get_no() << endl;
    cout << "avg: " << i.avg() << endl;

    i.reset();
    // i.avg();

    Sum<double> d = for_each(d_vals.begin(), d_vals.end(), Sum<double>{});
    cout << "sum: " << d.get_sum() << endl;
    cout << "no: " << d.get_no() << endl;
    cout << "avg: " << d.avg() << endl;
}

template <int l, int r>
auto my_rand() {
    static_assert(l <= r, "Error: invalid range");

    random_device rd;
    mt19937 X(rd());
    uniform_int_distribution<int> U(l, r);

    return [eng = std::move(X), U]() mutable {
        return U(eng);
    };
}

void zadanie_c() {
    int a[10];
    array<int, 10> b;

    auto g = my_rand<10, 99>();

    generate_n(a, 10, g);
    generate_n(b.begin(), 10, g);

    cout << "\nc: " << endl;
    for_each(a, a + 10, [](int x) { cout << x << ' '; });
    cout << endl;

    for_each(b.begin(), b.end(), [](int x) { cout << x << ' '; });
    cout << endl;
}

void zadanie_d() {
    auto X = my_rand<1, 100>();
    vector<int> tmp(25);
    generate_n(tmp.begin(), 25, X);
    unordered_multiset<int> src(tmp.begin(), tmp.end());

    auto is_prime = [](int x) {
        if(x < 2) {
            return false;
        }

        for (int i = 2; i * i <= x; i++) {
            if(x % i == 0) return false;
        }

        return true;
    };

    size_t n = count_if(src.begin(), src.end(), is_prime);
    vector<int> v(n);
    copy_if(src.begin(), src.end(), v.begin(), is_prime);
    set<int> dst(v.begin(), v.end());

    cout << "\nd: " << endl;

    cout << "src: ";
    for_each(src.begin(), src.end(), [](int x) { cout << x << ' '; });
    cout << endl;

    cout << "prime: ";
    for_each(dst.begin(), dst.end(), [](int x) { cout << x << ' '; });
    cout << endl;
}

void zadanie_e() {
    cout << "\ne: " << endl;

    multiset<Trojkat> s = {
        {3, 4, 5, "t1"},
        {5, 5, 6, "t2"},
        {6, 8, 10, "t3"},
        {7, 7, 7, "t4"},
        {4, 4, 5, "t5"},
        {8, 9, 10, "t6"},
        {10, 10, 12, "t7"},
    };

    vector<Trojkat> v(s.begin(), s.end());
    sort(v.begin(), v.end(), [](const Trojkat &x, const Trojkat &y) {
        return x.obwod() < y.obwod();
    });
    for_each(v.begin(), v.end(), [](const Trojkat &t) { cout << t << endl; });

    auto [mn, mx] = minmax_element(s.begin(), s.end(), [](const Trojkat &x, const Trojkat &y) {
        return x.pole() < y.pole();
    });
    cout << "min area: " << *mn << endl;
    cout << "max area: " << *mx << endl;

    auto jest_ostrokatny = [](const Trojkat &t) {
        double x = t.a;
        double y = t.b;
        double z = t.c;

        if(x > y) swap(x, y); // x <= y
        if(y > z) swap(y, z); // y <= z
        if(x > y) swap(x, y); // x <= y <= z

        return x * x + y * y > z * z;
    };

    for_each(s.begin(), s.end(), [&](const Trojkat &t) {
        if(jest_ostrokatny(t)) cout << t << endl;
    });
}

int main() {
    zadanie_a();
    zadanie_b();
    zadanie_c();
    zadanie_d();
    zadanie_e();
}
