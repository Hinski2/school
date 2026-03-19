#pragma once 
#include "Point.hpp"

class Segment {
    Point a, b;

public:
    Segment(Point a, Point b) : a(a), b(b) {}
    Segment(const Segment& other) : a(other.a), b(other.b) {}
    Segment& operator=(const Segment& other);

    double len();
    bool containsPoint(const Point& p);
    Vector toVector() const;


    static bool pParallel(const Segment& a, const Segment& b);
    static bool pPerpendicular(const Segment& a, const Segment& b);
};

