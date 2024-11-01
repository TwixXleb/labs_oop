
#ifndef LAB0_POINT_02_H
#define LAB0_POINT_02_H

// Point_02.h
#pragma once
#include <iostream>
#include "ScalarConcept.h"

template<Scalar T>
class Point_02 {
public:
    T x, y;

    Point_02() : x(0), y(0) {}
    Point_02(T x_, T y_) : x(x_), y(y_) {}

    // Copy constructor
    Point_02(const Point_02& other) = default;

    // Move constructor
    Point_02(Point_02&& other) noexcept = default;

    // Copy assignment
    Point_02& operator=(const Point_02& other) = default;

    // Move assignment
    Point_02& operator=(Point_02&& other) noexcept = default;

    // Destructor
    ~Point_02() = default;

    // Overload output operator
    friend std::ostream& operator<<(std::ostream& os, const Point_02& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }

    // Overload input operator
    friend std::istream& operator>>(std::istream& is, Point_02& point) {
        is >> point.x >> point.y;
        return is;
    }
};

#endif //LAB0_POINT_02_H
