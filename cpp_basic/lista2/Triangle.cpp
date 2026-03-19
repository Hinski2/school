#include "Triangle.hpp"
#include "Segment.hpp"

double Triangle::area() const {
    const Vector ab = a.toVector(a, b);
    const Vector ac = a.toVector(a, c);

    return std::abs(ab.cross(ac)) / 2.;
}

double Triangle::perimeter() const {
   return Segment(a, b).len() + 
            Segment(b, c).len() + 
            Segment(c, a).len();
}

bool Triangle::containsPoint(const Point& p) const {
    const double a1 = Triangle(a, b, p).area();
    const double a2 = Triangle(a, c, p).area();
    const double a3 = Triangle(c, b, p).area();

    return std::abs(a1 + a2 + a3 - area()) < 1e-18;
}

bool Triangle::pDisjoint(const Triangle& a, const Triangle &b) {
    if(a.containsPoint(b.a) or a.containsPoint(b.b) or a.containsPoint(b.c)) return false;
    if(b.containsPoint(a.a) or b.containsPoint(a.b) or b.containsPoint(a.c)) return false;
    return true;
}

bool Triangle::isInsedeOf(const Triangle& a, const Triangle &b) {
    return a.containsPoint(b.a) and 
            a.containsPoint(b.b) and 
            a.containsPoint(b.c);
}
