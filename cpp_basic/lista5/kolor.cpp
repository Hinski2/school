#include "kolor.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

Kolor::Kolor() {
    r = g = b = 0;
}

Kolor::Kolor(int r, int g, int b)
    : r(r), g(g), b(b)
{
    for(auto &c: {r, g, b}) {
        if(c < 0 or c > 255) throw std::invalid_argument("Error: color out of range");
    }
}


u8 Kolor::getR() const {
    return r;
}
u8 Kolor::getG() const {
    return g;
}
u8 Kolor::getB() const {
    return b;
}

void Kolor::setR(int c) {
    if(c < 0 or c > 255) throw std::invalid_argument("Error: color out of range");
    r = c;
}
void Kolor::setB(int c) {

    if(c < 0 or c > 255) throw std::invalid_argument("Error: color out of range");
    b = c;
}
void Kolor::setG(int c) {
    if(c < 0 or c > 255) throw std::invalid_argument("Error: color out of range");
    g = c;
}


Kolor& Kolor::operator++() {
    int max_val = static_cast<int>(std::numeric_limits<decltype(r)>::max());
    r = std::min(max_val, r + r / 10 + 10); 
    g = std::min(max_val, g + g / 10 + 10); 
    b = std::min(max_val, b + b / 10 + 10); 

    return *this;
}
Kolor& Kolor::operator--() {
    int min_val = static_cast<int>(std::numeric_limits<decltype(r)>::min());
    r = std::max(min_val, r - r / 10 - 10); 
    g = std::max(min_val, g - g / 10 - 10); 
    b = std::max(min_val, b - b / 10 - 10); 

    return *this;
}

Kolor Kolor::combine(const Kolor& k1, const Kolor& k2) {
    int r = (static_cast<int>(k1.r) + k2.r) / 2;
    int g = (static_cast<int>(k1.g) + k2.g) / 2;
    int b = (static_cast<int>(k1.b) + k2.b) / 2;

    return Kolor(r, g, b);
}

KolorTransparentny::KolorTransparentny()
    : Kolor(), alfa(255)
{}

KolorTransparentny::KolorTransparentny(int r, int g, int b, int alfa)
    : Kolor(r, g, b), alfa(alfa)
{
    if(alfa < 0 or alfa > 255) throw std::invalid_argument("Error: alfa out of range");
}

u8 KolorTransparentny::getAlfa() const {
    return alfa;
}

void KolorTransparentny::setAlfa(int a) {
    if(a < 0 or a > 255) throw std::invalid_argument("Error: alfa out of range");
    alfa = a;
}

static void validateNazwa(const std::string& nazwa) {
    for(char c: nazwa)
        if(c < 'a' or c > 'z') throw std::invalid_argument("Error: wrong name");
}

KolorNazwany::KolorNazwany()
    : Kolor(), nazwa("")
{}

KolorNazwany::KolorNazwany(int r, int g, int b, const std::string& nazwa)
    : Kolor(r, g, b), nazwa(nazwa)
{
    validateNazwa(nazwa);
}

std::string KolorNazwany::getNazwa() const {
    return nazwa;
}

void KolorNazwany::setNazwa(const std::string& nazwa) {
    validateNazwa(nazwa);
    this->nazwa = nazwa;
}

KolorTN::KolorTN()
    : Kolor(), KolorNazwany(), KolorTransparentny()
{}

KolorTN::KolorTN(int r, int g, int b, int alfa, const std::string& nazwa)
    : Kolor(r, g, b), KolorNazwany(-1, g, b, nazwa), KolorTransparentny(-2, g, b, alfa)
{}

std::ostream& operator<<(std::ostream& os, const Kolor& k) {
    return os << "Kolor r:" << static_cast<int>(k.r)
              << ", g:" << static_cast<int>(k.g)
              << ", b:" << static_cast<int>(k.b);
}

std::ostream& operator<<(std::ostream& os, const KolorTransparentny& k) {
    return os << "KolorTransparentny r:" << static_cast<int>(k.getR())
              << ", g:" << static_cast<int>(k.getG())
              << ", b:" << static_cast<int>(k.getB())
              << ", alfa:" << static_cast<int>(k.alfa);
}

std::ostream& operator<<(std::ostream& os, const KolorNazwany& k) {
    return os << "KolorNazwany r:" << static_cast<int>(k.getR())
              << ", g:" << static_cast<int>(k.getG())
              << ", b:" << static_cast<int>(k.getB())
              << k.nazwa;
}

std::ostream& operator<<(std::ostream& os, const KolorTN& k) {
    return os << "KolorTN r:" << static_cast<int>(k.getR())
              << ", g:" << static_cast<int>(k.getG())
              << ", b:" << static_cast<int>(k.getB())
              << ", alfa:" << static_cast<int>(k.getAlfa())
              << k.getNazwa();
}
