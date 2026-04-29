#include "piksel.hpp"
#include <stdexcept>

PikselKolorowy::PikselKolorowy()
    : Piksel(), Kolor()
{}

PikselKolorowy::PikselKolorowy(int x, int y, int r, int g, int b)
    : Piksel(x, y), Kolor(r, g, b)
{}

void PikselKolorowy::move(int dx, int dy) {
    int nx = getX() + dx;
    int ny = getY() + dy;
    if(nx < 0 or nx >= 1024) throw std::invalid_argument("Error: x out of screen bounds after move");
    if(ny < 0 or ny >= 768)  throw std::invalid_argument("Error: y out of screen bounds after move");
    setX(nx);
    setY(ny);
}

std::ostream& operator<<(std::ostream& os, const PikselKolorowy& p) {
    return os << "PikselKolorowy:" << p.getX() << ", " << p.getY()
              << ", r:" << static_cast<int>(p.getR())
              << ", g:" << static_cast<int>(p.getG())
              << ", b:" << static_cast<int>(p.getB());
}
