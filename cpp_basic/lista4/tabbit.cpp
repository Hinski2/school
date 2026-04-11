#include "tabbit.hpp"
#include <stdexcept>

// Ref --------------------------------------
Tabbit::Ref& Tabbit::Ref::operator=(bool b) {
    tb.pisz(idx, b);
    return *this;
}

Tabbit::Ref& Tabbit::Ref::operator=(const Ref& inna) {
    tb.pisz(idx, inna.tb.czytaj(inna.idx)); 
    return *this;
}

Tabbit::Ref::operator bool() const {
    return tb.czytaj(idx);
}

// Tabbit ---------------------------------
const int Tabbit::jednostka = sizeof(slowo) * 8;

bool Tabbit::czytaj(int i) const {
    if (i < 0 || i >= dl)
        throw std::out_of_range("Error: Indeks bitu poza zakresem");

    int nr_slowa = i / jednostka;
    int nr_bitu = i % jednostka;
    
    return (tab[nr_slowa] >> nr_bitu) & 1ULL;
}

void Tabbit::pisz(int i, bool b) {
    if (i < 0 || i >= dl)
        throw std::out_of_range("Error: Indeks bitu poza zakresem");
    
    int nr_slowa = i / jednostka;
    int nr_bitu = i % jednostka;
    
    
    if (b) {
        tab[nr_slowa] |= 1ULL << nr_bitu;
    } else {
        tab[nr_slowa] &= ~(1ULL << nr_bitu);
    }
}

bool Tabbit::operator[](int i) const {
    return czytaj(i);
}

Tabbit::Ref Tabbit::operator[](int i) {
    return Ref(*this, i);
}

int Tabbit::rozmiar() const {
    return dl;
}

Tabbit::Tabbit(int rozm) {
    if (rozm < 0)
        throw std::invalid_argument("Error: Ujemny rozmiar tabicy");
    
    dl = rozm;
    int ile_slow = (dl + jednostka - 1) / jednostka;
    tab = new slowo[ile_slow]{};
}

Tabbit::Tabbit(slowo wzorzec) {
    dl = jednostka;
    tab = new slowo[1];
    tab[0] = wzorzec;
}

Tabbit::~Tabbit() {
    delete[] tab;
}

Tabbit::Tabbit(const Tabbit &tb) : dl(tb.dl) {
    int ile_slow = (dl + jednostka - 1) / jednostka;
    tab = new slowo[ile_slow];
    
    for (int i = 0; i < ile_slow; ++i) {
        tab[i] = tb.tab[i];
    }
}

Tabbit::Tabbit(Tabbit &&tb) : dl(tb.dl), tab(tb.tab) {
    tb.dl = 0;
    tb.tab = nullptr;
}

Tabbit& Tabbit::operator=(const Tabbit &tb) {
    if (this == &tb) 
        return *this;

    delete[] tab;
    
    dl = tb.dl;
    int ile_slow = (dl + jednostka - 1) / jednostka;
    tab = new slowo[ile_slow];
    
    for (int i = 0; i < ile_slow; ++i) {
        tab[i] = tb.tab[i];
    }

    return *this;
}

Tabbit& Tabbit::operator=(Tabbit &&tb) {
    if (this == &tb)
        return *this;
    delete[] tab;
    
    dl = tb.dl;
    tab = tb.tab;
    
    tb.dl = 0;
    tb.tab = nullptr;
    return *this;
}

Tabbit& Tabbit::operator|=(const Tabbit& rhs) {
    if (dl != rhs.dl) throw std::invalid_argument("Error: Rozne rozmiary tablic");
    int ile_slow = (dl + jednostka - 1) / jednostka;

    for (int i = 0; i < ile_slow; ++i)
        tab[i] |= rhs.tab[i];

    return *this;
}

Tabbit& Tabbit::operator&=(const Tabbit& rhs) {
    if (dl != rhs.dl) throw std::invalid_argument("Error: Rozne rozmiary tablic");
    int ile_slow = (dl + jednostka - 1) / jednostka;

    for (int i = 0; i < ile_slow; ++i)
        tab[i] &= rhs.tab[i];

    return *this;
}

Tabbit& Tabbit::operator^=(const Tabbit& rhs) {
    if (dl != rhs.dl) throw std::invalid_argument("Error: Rozne rozmiary tablic");
    int ile_slow = (dl + jednostka - 1) / jednostka;

    for (int i = 0; i < ile_slow; ++i)
        tab[i] ^= rhs.tab[i];
    
    return *this;
}

Tabbit Tabbit::operator!() const {
    Tabbit wynik(*this);
    int ile_slow = (dl + jednostka - 1) / jednostka;
    
    for (int i = 0; i < ile_slow; ++i)
        wynik.tab[i] = ~wynik.tab[i];
    
    int reszta = dl % jednostka;
    if (reszta != 0)
        wynik.tab[ile_slow - 1] &= ((1Ull << reszta)- 1);
    
    return wynik;
}

Tabbit operator|(const Tabbit& a, const Tabbit& b) {
    Tabbit wynik(a);
    wynik |= b;
    return wynik;
}

Tabbit operator&(const Tabbit& a, const Tabbit& b) {
    Tabbit wynik(a);
    wynik &= b;
    return wynik;
}

Tabbit operator^(const Tabbit& a, const Tabbit& b) {
    Tabbit wynik(a);
    wynik ^= b;
    return wynik;
}

// we / wy
std::ostream& operator<<(std::ostream &out, const Tabbit &tb) {
    if(tb.tab == nullptr) {
        throw std::invalid_argument("error: tablica jest usunięta");
    }
    for(int i = tb.rozmiar() - 1; i >= 0; i--) {
        out << tb.czytaj(i);
        if(i % 8 == 0) out << " ";
        if(i % Tabbit::jednostka == 0 && i) out << std::endl;
    }

    return out;
}

std::istream& operator>>(std::istream &in, Tabbit &tb) {
    std::string input; in >> input; 
    if(static_cast<int>(input.length()) > tb.rozmiar()) {
        throw std::out_of_range("error: za dlugi input");
    }
    
    int ile_slow = (tb.rozmiar() + Tabbit::jednostka - 1) / Tabbit::jednostka;
    for (int i = 0; i < ile_slow; ++i) {
        tb.tab[i] = 0;
    }

    const int len = input.length();
    for (int i = 0; i < len; ++i) {
        char znak = input[len - 1 - i];
        
        if (znak == '1') {
            tb.pisz(i, true);
        } 
        else if (znak != '0') {
            throw std::invalid_argument("Error: to nie bit");
        }
    }

    return in;
}
