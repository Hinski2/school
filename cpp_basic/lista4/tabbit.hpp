#pragma once 
#include <cstdint>
#include <iostream>

class Tabbit {
    typedef uint64_t slowo; // komórka w tablicy
    static const int jednostka; // ile bitów w słowie
    friend std::istream& operator >> (std::istream &we, Tabbit &tb);
    friend std::ostream& operator << (std::ostream &wy, const Tabbit &tb);
    class Ref; // klasa pomocnicza do adresowania bitów

protected:
    int dl; // liczba bitów
    slowo *tab; // tablica bitów

public:
    // wyzerowana tablica bitow [0...rozm]
    explicit Tabbit(int rozm);
    // tablica 64 bitów zainicjalizowana wzorcem
    explicit Tabbit(slowo tb);
    // destruktor
    ~Tabbit();
    // konstruktor kopiujący
    Tabbit(const Tabbit &tb);
    // konstruktor przenoszący
    Tabbit(Tabbit &&tb);
    // przypisanie kopiujące
    Tabbit& operator = (const Tabbit &tb);
    // przypisanie przenoszące
    Tabbit& operator = (Tabbit &&tb);

private:
    bool czytaj(int i) const; // odczyt bitu
    void pisz(int i, bool b); // zapis bitu

public:
    // indeksowanie dla stałych tablic bitowych
    bool operator [] (int i) const;
    // indeksowanie dla zwykłych tablic bitowych
    Ref operator [] (int i);
    // ile bitów w tablicy
    inline int rozmiar() const;
public:
    Tabbit& operator|=(const Tabbit& b);
    Tabbit& operator&=(const Tabbit& b);
    Tabbit& operator^=(const Tabbit& b);

    Tabbit operator!() const; 

    friend Tabbit operator|(const Tabbit& a, const Tabbit& b);
    friend Tabbit operator&(const Tabbit& a, const Tabbit& b);
    friend Tabbit operator^(const Tabbit& a, const Tabbit& b);
};

class Tabbit::Ref {
    Tabbit& tb;
    int idx;     

public:
    Ref(Tabbit& t, int i) : tb(t), idx(i) {}

    Ref& operator=(bool b);
    Ref& operator=(const Ref& inna);
    operator bool() const;
};
