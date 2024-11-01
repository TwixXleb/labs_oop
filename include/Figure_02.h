
#ifndef LAB0_FIGURE_02_H
#define LAB0_FIGURE_02_H

// Figure_02.h
#pragma once
#include "Point_02.h"

template<Scalar T>
class Figure_02 {
public:
    virtual void Rotate(double angle) = 0;
    virtual void Translate(T dx, T dy) = 0;
    virtual double Area() const = 0;
    virtual Point_02<T> Center() const = 0;
    virtual void Print(std::ostream& os) const = 0;
    virtual ~Figure_02() = default;
};

#endif //LAB0_FIGURE_02_H
