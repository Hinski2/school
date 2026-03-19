#include "Segment.hpp"
#include "Point.hpp"
#include "Vector.hpp"
#include <cstdlib>

double Segment::len() {
    return Point::distance(a, b); 
}

bool Segment::containsPoint(const Point& p) {
    Vector ab = Point::toVector(a, b);
    Vector ap = Point::toVector(a, p);

    if(std::abs(ab.cross(ap)) > 1e-18) return false;

    double d = ab.dot(ap);
    return 0 < d && d < ab.len();
}


Vector Segment::toVector() const {
    return Point::toVector(a, b);
}

bool Segment::pParallel(const Segment& a, const Segment& b) {
    const Vector va = a.toVector();
    const Vector vb = b.toVector();

    return va.isParallel(vb);
}

bool Segment::pPerpendicular(const Segment& a, const Segment& b) {
    const Vector va = a.toVector();
    const Vector vb = b.toVector();

    return va.isPerpendicular(vb);
}
