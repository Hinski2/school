#include <stdexcept>
#include <string>
#include <utility>
#include <iostream>

namespace obliczenia {

class Wyjątek_wymierny : public std::logic_error {
public:
    Wyjątek_wymierny(const std::string& msg) : std::logic_error(msg) {}
};

class przekroczenie_zakresu : public Wyjątek_wymierny {
public:
    przekroczenie_zakresu() : Wyjątek_wymierny("Przekroczenie zakresu typu int") {}
};

class dzielenie_przez_0 : public Wyjątek_wymierny {
public:
    dzielenie_przez_0() : Wyjątek_wymierny("Dzielenie przez zero") {}
};

class Wymierna {
    int licznik;
    int mianownik;
    void fix() noexcept;

public:
    Wymierna(int l, int m = 1) noexcept;
    Wymierna() noexcept;

    int getLicznik() const noexcept;
    int getMianownik() const noexcept;

    Wymierna& operator+=(const Wymierna& other);
    Wymierna& operator-=(const Wymierna& other);
    Wymierna& operator*=(const Wymierna& other);
    Wymierna& operator/=(const Wymierna& other);

    friend Wymierna operator+(Wymierna a, const Wymierna& b);
    friend Wymierna operator-(Wymierna a, const Wymierna& b);
    friend Wymierna operator*(Wymierna a, const Wymierna& b);
    friend Wymierna operator/(Wymierna a, const Wymierna& b);

    friend Wymierna operator-(const Wymierna& a) noexcept;
    friend Wymierna operator!(const Wymierna& a);

    operator double() const noexcept;
    explicit operator int() const noexcept;

    std::pair<std::string, std::string> rozwinięcie_dziesiętne() const;

    friend std::ostream& operator<<(std::ostream& out, const Wymierna& w);
    friend std::istream& operator>>(std::istream& in, Wymierna& w);
};

}