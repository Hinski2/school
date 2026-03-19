#include "Point.hpp"
#include <cstdlib>

double Point::distance(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y + b.y);
}

Vector Point::toVector(const Point& a, const Point& b) {
    return { b.x - a.x, b.y - a.y };
}
