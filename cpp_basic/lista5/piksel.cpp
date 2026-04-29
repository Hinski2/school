#include "piksel.hpp"
#include <stdexcept>

void Piksel::validateCoords(int x, int y) {
    if(x < 0 or x >= WIDTH)  throw std::invalid_argument("Error: x out of screen bounds");
    if(y < 0 or y >= HEIGHT) throw std::invalid_argument("Error: y out of screen bounds");
}

Piksel::Piksel()
    : x(0), y(0)
{}

Piksel::Piksel(int x, int y)
    : x(x), y(y)
{
    validateCoords(x, y);
}

int Piksel::getX() const { return x; }
int Piksel::getY() const { return y; }

void Piksel::setX(int x) {
    if(x < 0 or x >= WIDTH) throw std::invalid_argument("Error: x out of screen bounds");
    this->x = x;
}

void Piksel::setY(int y) {
    if(y < 0 or y >= HEIGHT) throw std::invalid_argument("Error: y out of screen bounds");
    this->y = y;
}

int Piksel::distLeft() const { 
    return x;
}
int Piksel::distRight() const { 
    return WIDTH - 1 - x;
}
int Piksel::distTop() const { 
    return y;
}
int Piksel::distBottom() const { 
    return HEIGHT - 1 - y;
}

double Piksel::distance(const Piksel& p1, const Piksel& p2) {
    int dx = p1.x - p2.x;
    int dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

double Piksel::distance(const Piksel* p1, const Piksel* p2) {
    return distance(*p1, *p2);
}

std::ostream& operator<<(std::ostream& os, const Piksel& p) {
    return os << "Piksel:" << p.x << ", " << p.y;
}