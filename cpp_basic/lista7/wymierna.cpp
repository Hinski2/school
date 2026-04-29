#include "wymierna.hpp"
#include <numeric>
#include <cstdlib>
#include <cmath>
#include <climits>
#include <unordered_map>

namespace obliczenia {

Wymierna::Wymierna(int l, int m) noexcept
	: licznik(l), mianownik(m == 0 ? 1 : m) {
    fix();
}

Wymierna::Wymierna() noexcept
	: Wymierna(0, 1) {
}

int Wymierna::getLicznik() const noexcept {
    return licznik;
}

int Wymierna::getMianownik() const noexcept {
    return mianownik;
}

void Wymierna::fix() noexcept {
    auto gcd = std::gcd(std::abs(licznik), std::abs(mianownik));
    licznik /= gcd;
    mianownik /= gcd;

    if (mianownik < 0) {
        licznik = -licznik;
        mianownik = -mianownik;
    }
}

Wymierna& Wymierna::operator+=(const Wymierna& other) {
    auto l = 1LL * mianownik * other.licznik + 1LL * licznik * other.mianownik;
    auto m = 1LL * mianownik * other.mianownik;
    auto gcd = std::gcd(std::abs(l), std::abs(m));

    if (l < INT_MIN or l > INT_MAX or m < INT_MIN or m > INT_MAX) {
        throw przekroczenie_zakresu();
    }

    licznik = l / gcd;
    mianownik = m / gcd;

    return *this;
}

Wymierna& Wymierna::operator-=(const Wymierna& other) {
    auto l = 1LL * licznik * other.mianownik - 1LL * mianownik * other.licznik;
    auto m = 1LL * mianownik * other.mianownik;

    if (l < INT_MIN or l > INT_MAX or m < INT_MIN or m > INT_MAX) {
        throw przekroczenie_zakresu();
    }

    auto gcd = std::gcd(std::abs(l), std::abs(m));

    licznik = l / gcd;
    mianownik = m / gcd;

    return *this;
}

Wymierna& Wymierna::operator*=(const Wymierna& other) {
    auto l = 1LL * licznik * other.licznik;
    auto m = 1LL * mianownik * other.mianownik;

    if (l < INT_MIN or l > INT_MAX or m < INT_MIN or m > INT_MAX) {
        throw przekroczenie_zakresu();
    }

    auto gcd = std::gcd(std::abs(l), std::abs(m));

    licznik = l / gcd;
    mianownik = m / gcd;


    return *this;
}

Wymierna& Wymierna::operator/=(const Wymierna& other) {
    if (other.getLicznik() == 0) {
        throw dzielenie_przez_0();
    }

    *this *= !other;
    return *this;
}

Wymierna operator+(Wymierna a, const Wymierna& b) {
    return a += b;
}

Wymierna operator-(Wymierna a, const Wymierna& b) {
    return a -= b;
}

Wymierna operator*(Wymierna a, const Wymierna& b) {
    return a *= b;
}

Wymierna operator/(Wymierna a, const Wymierna& b) {
    return a /= b;
}

Wymierna operator-(const Wymierna& a) noexcept {
    return Wymierna(-a.getLicznik(), a.getMianownik());
}

Wymierna operator!(const Wymierna& a) {
    if (a.getLicznik() == 0) {
        throw dzielenie_przez_0();
    }
    return Wymierna(a.getMianownik(), a.getLicznik());
}

Wymierna::operator double() const noexcept {
    return static_cast<double>(licznik) / mianownik;
}

Wymierna::operator int() const noexcept {
    return static_cast<int>(std::round(static_cast<double>(licznik) / mianownik));
}

std::ostream& operator<<(std::ostream& out, const Wymierna& w) {
    if(static_cast<double>(w.getLicznik()) / w.getMianownik() < 0)
        out << '-';
    out << std::abs(w.getLicznik() / w.getMianownik());

    if(w.getLicznik() % w.getMianownik() != 0) {
        auto [a, b] = w.rozwinięcie_dziesiętne();
        out << '.' << a;
        if(!b.empty()) {
            out << '(' << b << ')';
        }
    }

    return out;
}

std::istream& operator>>(std::istream& in, Wymierna& w) {
    int l, m;
    char c;
    in >> l >> c >> m;

    if(c != '/') {
        return in;
    } else if (m == 0) {
        throw dzielenie_przez_0();
    }

    w = Wymierna(l, m);
    return in;
}

std::pair<std::string, std::string> Wymierna::rozwinięcie_dziesiętne() const {
    std::unordered_map<int, int> um;
    std::string s;

    int rem = std::abs(licznik % mianownik);
    int x = std::abs(mianownik);
    for(int pos = 0; rem != 0 and !um.contains(rem); pos++) {
        um[rem] = pos;
        rem *= 10;

        int num = rem / x;
        s += (char)('0' + num);
        rem %= x;
    }
    
    if (rem == 0) {
        return {s, ""};
    } else {
        return {s.substr(0, um[rem]) , s.substr(um[rem])};
    }
}

}