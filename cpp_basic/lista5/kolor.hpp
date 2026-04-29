#pragma once 
#include <cstdint>
#include <ostream>
#include <string>

typedef uint8_t u8;

class Kolor {
    u8 r, g, b;

public:
    Kolor();
    Kolor(int r, int g, int b);

    u8 getR() const;
    u8 getG() const;
    u8 getB() const;

    void setR(int c);
    void setB(int c);
    void setG(int c);

    Kolor& operator++();
    Kolor& operator--();

    static Kolor combine(const Kolor& k1, const Kolor& k2);

    friend std::ostream& operator<<(std::ostream& os, const Kolor& k);
};

class KolorTransparentny : virtual public Kolor {
    u8 alfa;

public:
    KolorTransparentny();
    KolorTransparentny(int r, int g, int b, int alfa);

    u8 getAlfa() const;
    void setAlfa(int a);

    friend std::ostream& operator<<(std::ostream& os, const KolorTransparentny& k);
};

class KolorNazwany : virtual public Kolor {
    std::string nazwa;

public:
    KolorNazwany();
    KolorNazwany(int r, int g, int b, const std::string& nazwa = "");

    std::string getNazwa() const;
    void setNazwa(const std::string& nazwa);

    friend std::ostream& operator<<(std::ostream& os, const KolorNazwany& k);
};

class KolorTN : public KolorNazwany, public KolorTransparentny {
public:
    KolorTN();
    KolorTN(int r, int g, int b, int alfa, const std::string& nazwa = "");

    friend std::ostream& operator<<(std::ostream& os, const KolorTN& k);
};
