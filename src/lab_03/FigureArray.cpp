#include "../../include/FigureArray.h"
#include <stdexcept>
#include <iostream>

FigureArray::FigureArray() : size(0), capacity(2) {
    figures = new Figure*[capacity];
}

FigureArray::~FigureArray() {
    for (size_t i = 0; i < size; ++i) {
        delete figures[i];
    }
    delete[] figures;
}

FigureArray::FigureArray(const FigureArray& other) : size(other.size), capacity(other.capacity) {
    figures = new Figure*[capacity];
    for (size_t i = 0; i < size; ++i) {
        figures[i] = other.figures[i]->clone();
    }
}

FigureArray& FigureArray::operator=(const FigureArray& other) {
    if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
            delete figures[i];
        }
        delete[] figures;

        size = other.size;
        capacity = other.capacity;
        figures = new Figure*[capacity];
        for (size_t i = 0; i < size; ++i) {
            figures[i] = other.figures[i]->clone();
        }
    }
    return *this;
}

FigureArray::FigureArray(FigureArray&& other) noexcept : figures(other.figures), size(other.size), capacity(other.capacity) {
    other.figures = nullptr;
    other.size = 0;
    other.capacity = 0;
}

FigureArray& FigureArray::operator=(FigureArray&& other) noexcept {
    if (this != &other) {
        for (size_t i = 0; i < size; ++i) {
            delete figures[i];
        }
        delete[] figures;

        figures = other.figures;
        size = other.size;
        capacity = other.capacity;

        other.figures = nullptr;
        other.size = 0;
        other.capacity = 0;
    }
    return *this;
}

void FigureArray::resize(size_t new_capacity) {
    Figure** new_figures = new Figure*[new_capacity];
    for (size_t i = 0; i < size; ++i) {
        new_figures[i] = figures[i];
    }
    delete[] figures;
    figures = new_figures;
    capacity = new_capacity;
}

void FigureArray::add(Figure* fig) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    figures[size++] = fig;
}

void FigureArray::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete figures[index];
    for (size_t i = index; i < size - 1; ++i) {
        figures[i] = figures[i + 1];
    }
    --size;
}

void FigureArray::print_all() const {
    for (size_t i = 0; i < size; ++i) {
        figures[i]->print(std::cout);
        std::cout << " Area: " << figures[i]->area() << std::endl;
    }
}

double FigureArray::total_area() const {
    double total = 0;
    for (size_t i = 0; i < size; ++i) {
        total += figures[i]->area();
    }
    return total;
}
