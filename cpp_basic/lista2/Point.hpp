#pragma once 
#include "Vector.hpp"

struct Point {
    double x, y;

    Point(double x, double y) : x(x), y(y) {}

    static double distance(const Point& a, const Point& b);
    static Vector toVector(const Point& a, const Point& b);
};

