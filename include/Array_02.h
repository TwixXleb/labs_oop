
#ifndef LAB0_FIGUREARRAY_02_H
#define LAB0_FIGUREARRAY_02_H
// Array_02.inl.h
#pragma once
#include <memory>
#include <stdexcept>

template<class T>
class Array_02 {
private:
    std::shared_ptr<T[]> data;
    size_t capacity;
    size_t size;

    void increase_capacity();

public:
    // Constructors
    Array_02();
    Array_02(const Array_02& other);
    Array_02(Array_02&& other) noexcept;

    // Assignment operators
    Array_02& operator=(const Array_02& other);
    Array_02& operator=(Array_02&& other) noexcept;

    // Destructor
    ~Array_02() = default;

    // Methods
    void push_back(const T& element);
    void remove(size_t index);
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t get_size() const;
};

// Implementation
#include "Array_02.inl"

#endif //LAB0_FIGUREARRAY_02_H
