#pragma once
#include <cmath>
#include <ostream>
#include "kolor.hpp"

class Piksel {
    int x, y;

    static constexpr int WIDTH  = 1024; // XGA
    static constexpr int HEIGHT = 768;

    static void validateCoords(int x, int y);

public:
    Piksel();
    Piksel(int x, int y);

    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);

    int distLeft()   const;
    int distRight()  const;
    int distTop()    const;
    int distBottom() const;

    static double distance(const Piksel& p1, const Piksel& p2);
    static double distance(const Piksel* p1, const Piksel* p2);

    friend std::ostream& operator<<(std::ostream& os, const Piksel& p);
};

class PikselKolorowy final : public Piksel, private Kolor {
public:
    PikselKolorowy();
    PikselKolorowy(int x, int y, int r, int g, int b);

    using Kolor::getR;
    using Kolor::getG;
    using Kolor::getB;
    using Kolor::setR;
    using Kolor::setG;
    using Kolor::setB;

    void move(int dx, int dy);

    friend std::ostream& operator<<(std::ostream& os, const PikselKolorowy& p);
};
