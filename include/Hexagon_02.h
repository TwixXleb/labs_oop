
#ifndef LAB0_HEXAGON_02_H
#define LAB0_HEXAGON_02_H

// Hexagon_02.h
#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "Figure_02.h"

template<Scalar T>
class Hexagon_02 : public Figure_02<T> {
private:
    T side_length;
    Point_02<T> center;
    std::vector<std::unique_ptr<Point_02<T>>> vertices;

    void CalculateVertices();

public:
    // Constructors
    Hexagon_02();
    Hexagon_02(const Point_02<T>& center_, T side_length_);

    // Rule of Five
    Hexagon_02(const Hexagon_02& other);
    Hexagon_02(Hexagon_02&& other) noexcept;
    Hexagon_02& operator=(const Hexagon_02& other);
    Hexagon_02& operator=(Hexagon_02&& other) noexcept;
    ~Hexagon_02() override = default;

    // Figure methods
    void Rotate(double angle_rad) override;
    void Translate(T dx, T dy) override;
    double Area() const override;
    Point_02<T> Center() const override;
    void Print(std::ostream& os) const override;

    // Comparison operators
    bool operator==(const Hexagon_02& other) const;
    bool operator!=(const Hexagon_02& other) const;
    bool operator<(const Hexagon_02& other) const;
    bool operator<=(const Hexagon_02& other) const;
    bool operator>(const Hexagon_02& other) const;
    bool operator>=(const Hexagon_02& other) const;

    // Cast to double (area)
    explicit operator double() const;

    // Overload input/output operators
    template<Scalar U>
    friend std::istream& operator>>(std::istream& is, Hexagon_02<U>& hexagon);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Hexagon_02<U>& hexagon);
};

// Implementation
#include "Hexagon_02.inl"

#endif //LAB0_HEXAGON_02_H
