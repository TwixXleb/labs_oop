
#ifndef LAB0_OCTAGON_02_H
#define LAB0_OCTAGON_02_H

// Octagon_02.h
#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "Figure_02.h"

template<Scalar T>
class Octagon_02 : public Figure_02<T> {
private:
    T side_length;
    Point_02<T> center;
    std::vector<std::unique_ptr<Point_02<T>>> vertices;

    void CalculateVertices();

public:
    // Constructors
    Octagon_02();
    Octagon_02(const Point_02<T>& center_, T side_length_);

    // Rule of Five
    Octagon_02(const Octagon_02& other);
    Octagon_02(Octagon_02&& other) noexcept;
    Octagon_02& operator=(const Octagon_02& other);
    Octagon_02& operator=(Octagon_02&& other) noexcept;
    ~Octagon_02() override = default;

    // Figure methods
    void Rotate(double angle_rad) override;
    void Translate(T dx, T dy) override;
    double Area() const override;
    Point_02<T> Center() const override;
    void Print(std::ostream& os) const override;

    // Comparison operators
    bool operator==(const Octagon_02& other) const;
    bool operator!=(const Octagon_02& other) const;
    bool operator<(const Octagon_02& other) const;
    bool operator<=(const Octagon_02& other) const;
    bool operator>(const Octagon_02& other) const;
    bool operator>=(const Octagon_02& other) const;

    // Cast to double (area)
    explicit operator double() const;

    // Overload input/output operators
    template<Scalar U>
    friend std::istream& operator>>(std::istream& is, Octagon_02<U>& octagon);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Octagon_02<U>& octagon);
};

// Implementation
#include "../src/lab_04/Octagon_02.inl"

#endif //LAB0_OCTAGON_02_H
