
#ifndef LAB0_PENTAGON_02_H
#define LAB0_PENTAGON_02_H

// Pentagon_02.h
#pragma once
#include <vector>
#include <memory>
#include <cmath>
#include "Figure_02.h"

template<Scalar T>
class Pentagon_02 : public Figure_02<T> {
private:
    T side_length;
    Point_02<T> center;
    std::vector<std::unique_ptr<Point_02<T>>> vertices;

    void CalculateVertices();

public:

    // Публичный метод для доступа к вершинам
    std::vector<Point_02<T>> GetVertices() const;

    // Constructors
    Pentagon_02();
    Pentagon_02(const Point_02<T>& center_, T side_length_);

    // Rule of Five
    Pentagon_02(const Pentagon_02& other);
    Pentagon_02(Pentagon_02&& other) noexcept;
    Pentagon_02& operator=(const Pentagon_02& other);
    Pentagon_02& operator=(Pentagon_02&& other) noexcept;
    ~Pentagon_02() override = default;

    // Figure methods
    void Rotate(double angle_rad) override;
    void Translate(T dx, T dy) override;
    double Area() const override;
    Point_02<T> Center() const override;
    void Print(std::ostream& os) const override;

    // Comparison operators
    bool operator==(const Pentagon_02& other) const;
    bool operator!=(const Pentagon_02& other) const;
    bool operator<(const Pentagon_02& other) const;
    bool operator<=(const Pentagon_02& other) const;
    bool operator>(const Pentagon_02& other) const;
    bool operator>=(const Pentagon_02& other) const;

    // Cast to double (area)
    explicit operator double() const;

    // Overload input/output operators
    template<Scalar U>
    friend std::istream& operator>>(std::istream& is, Pentagon_02<U>& pentagon);

    template<Scalar U>
    friend std::ostream& operator<<(std::ostream& os, const Pentagon_02<U>& pentagon);
};

// Implementation
#include "../src/lab_04/Pentagon_02.inl"

#endif //LAB0_PENTAGON_02_H
