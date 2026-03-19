#pragma once 
#include <cstdlib>

struct Vector {
    double dx, dy;

    double cross(const Vector& other) const {
        return dx * other.dy - dy * other.dx;
    }

    double dot(const Vector& other) const {
        return dx * other.dx + dy * other.dy;
    }

    double len() const {
        return dx * dx + dy * dy;
    }

    bool isParallel(const Vector& other) const {
        return std::abs(cross(other)) < 1e-18;
    }

    bool isPerpendicular(const Vector& other) const {
        return std::abs(dot(other)) < 1e-18;
    }
};
