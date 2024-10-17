#include "../../include/Pentagon.h"
#include <cmath>
#include <iostream>

Pentagon::Pentagon(double x, double y, double side_length) : center_coords(x, y) {
    vertices = new std::pair<double, double>[vertex_count];
    side = side_length;
    calculate_vertices(side_length);
}

Pentagon::Pentagon(const Pentagon& other) : side(other.side) {
    center_coords = other.center_coords;
    vertices = new std::pair<double, double>[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
    if (this == &other) return *this;
    side = other.side;

    center_coords = other.center_coords;
    delete[] vertices;
    vertices = new std::pair<double, double>[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i] = other.vertices[i];
    }
    return *this;
}

Pentagon::Pentagon(Pentagon&& other) noexcept : center_coords(other.center_coords), vertices(other.vertices) {
    other.vertices = nullptr;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
    if (this != &other) {
        delete[] vertices;
        center_coords = other.center_coords;
        vertices = other.vertices;
        other.vertices = nullptr;
    }
    return *this;
}

// Перегрузка оператора вывода (<<)
std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon) {
    os << "Pentagon with center (" << pentagon.center_coords.first << ", " << pentagon.center_coords.second << ") and vertices:\n";
    for (size_t i = 0; i < pentagon.vertex_count; ++i) {
        os << "(" << pentagon.vertices[i].first << ", " << pentagon.vertices[i].second << ")\n";
    }
    return os;
}

// Перегрузка оператора ввода (>>)
std::istream& operator>>(std::istream& is, Pentagon& pentagon) {
    std::cout << "Enter center coordinates (x, y): ";
    is >> pentagon.center_coords.first >> pentagon.center_coords.second;

    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;

    pentagon.calculate_vertices(side_length);  // Вычисляем координаты вершин на основе новой длины сторон
    return is;
}

bool Pentagon::operator==(const Figure& other) const {
    const Pentagon* p = dynamic_cast<const Pentagon*>(&other);
    if (!p) return false;
    if (center_coords != p->center_coords) return false;
    for (size_t i = 0; i < vertex_count; ++i) {
        if (vertices[i] != p->vertices[i]) return false;
    }
    return true;
}

double Pentagon::area() const {
    double tan_36 = 5 - 2 * sqrt(5);
    double s = (5 * std::pow(side, 2)) / (4 * std::sqrt(tan_36));
    return s;
}

void Pentagon::print(std::ostream& os) const {
    os << "Pentagon with center (" << center_coords.first << ", " << center_coords.second << ") and vertices: \n";
    for (size_t i = 0; i < vertex_count; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")\n";
    }
}

void Pentagon::read(std::istream& is) {
    std::cout << "Enter the coordinates of the center (x, y): ";
    is >> center_coords.first >> center_coords.second;
    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;
    calculate_vertices(side_length);
}

std::pair<double, double> Pentagon::center() const {
    return center_coords;
}

void Pentagon::move(double new_x, double new_y) {
    double dx = new_x - center_coords.first;
    double dy = new_y - center_coords.second;
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i].first += dx;
        vertices[i].second += dy;
    }
    center_coords = {new_x, new_y};
}

void Pentagon::rotate(double angle) {
    for (size_t i = 0; i < vertex_count; ++i) {
        double x = vertices[i].first - center_coords.first;
        double y = vertices[i].second - center_coords.second;
        vertices[i].first = x * cos(angle) - y * sin(angle) + center_coords.first;
        vertices[i].second = x * sin(angle) + y * cos(angle) + center_coords.second;
    }
}

Figure* Pentagon::clone() const {
    return new Pentagon(*this);
}

void Pentagon::calculate_vertices(double side_length) {
    double angle = 2 * M_PI / 5;
    for (int i = 0; i < 5; ++i) {
        double x = center_coords.first + side_length * cos(i * angle);
        double y = center_coords.second + side_length * sin(i * angle);
        vertices[i] = {x, y};
    }
}

Pentagon::~Pentagon() {
    delete[] vertices;
}
