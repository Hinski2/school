#pragma once 
#include "Point.hpp"

class Triangle {
    Point a, b, c;

    Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {}
    Triangle(const Triangle& other) : a(other.a), b(other.b), c(other.c) {}
    Triangle& operator=(const Triangle& other);

    double area() const;
    double perimeter() const;
    bool containsPoint(const Point& p) const;
    
    static bool pDisjoint(const Triangle& a, const Triangle &b);
    static bool isInsedeOf(const Triangle& a, const Triangle &b);
};
