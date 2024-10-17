#include "../../include/Octagon.h"
#include <cmath>
#include <iostream>

Octagon::Octagon(double x, double y, double side_length) : center_coords(x, y) {
    vertices = new std::pair<double, double>[vertex_count];
    calculate_vertices(side_length);
    side = side_length;
}

Octagon::Octagon(const Octagon& other) : side(other.side) {
    center_coords = other.center_coords;
    vertices = new std::pair<double, double>[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Octagon& Octagon::operator=(const Octagon& other) {
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

Octagon::Octagon(Octagon&& other) noexcept : center_coords(other.center_coords), vertices(other.vertices) {
    other.vertices = nullptr;
}

Octagon& Octagon::operator=(Octagon&& other) noexcept {
    if (this != &other) {
        delete[] vertices;
        center_coords = other.center_coords;
        vertices = other.vertices;
        other.vertices = nullptr;
    }
    return *this;
}

bool Octagon::operator==(const Figure& other) const {
    const Octagon* o = dynamic_cast<const Octagon*>(&other);
    if (!o) return false;
    if (center_coords != o->center_coords) return false;
    for (size_t i = 0; i < vertex_count; ++i) {
        if (vertices[i] != o->vertices[i]) return false;
    }
    return true;
}

double Octagon::area() const {
    double s = 2 * std::pow(side, 2) * (std::sqrt(2) + 1);
    return s;
}

void Octagon::print(std::ostream& os) const {
    os << "Octagon with center (" << center_coords.first << ", " << center_coords.second << ") and vertices: \n";
    for (size_t i = 0; i < vertex_count; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")\n";
    }
}

void Octagon::read(std::istream& is) {
    std::cout << "Enter the coordinates of the center (x, y): ";
    is >> center_coords.first >> center_coords.second;
    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;
    calculate_vertices(side_length);
}

std::pair<double, double> Octagon::center() const {
    return center_coords;
}

std::ostream& operator<<(std::ostream& os, const Octagon& octagon) {
    os << "Octagon with center (" << octagon.center_coords.first << ", " << octagon.center_coords.second << ") and vertices:\n";
    for (size_t i = 0; i < octagon.vertex_count; ++i) {
        os << "(" << octagon.vertices[i].first << ", " << octagon.vertices[i].second << ")\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Octagon& octagon) {
    std::cout << "Enter center coordinates (x, y): ";
    is >> octagon.center_coords.first >> octagon.center_coords.second;

    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;

    octagon.calculate_vertices(side_length);
    return is;
}


void Octagon::move(double new_x, double new_y) {
    double dx = new_x - center_coords.first;
    double dy = new_y - center_coords.second;
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i].first += dx;
        vertices[i].second += dy;
    }
    center_coords = {new_x, new_y};
}

void Octagon::rotate(double angle) {
    for (size_t i = 0; i < vertex_count; ++i) {
        double x = vertices[i].first - center_coords.first;
        double y = vertices[i].second - center_coords.second;
        vertices[i].first = x * cos(angle) - y * sin(angle) + center_coords.first;
        vertices[i].second = x * sin(angle) + y * cos(angle) + center_coords.second;
    }
}

Figure* Octagon::clone() const {
    return new Octagon(*this);
}

void Octagon::calculate_vertices(double side_length) {
    double angle = 2 * M_PI / 8;
    for (int i = 0; i < 8; ++i) {
        double x = center_coords.first + side_length * cos(i * angle);
        double y = center_coords.second + side_length * sin(i * angle);
        vertices[i] = {x, y};
    }
}

Octagon::~Octagon() {
    delete[] vertices;  // Освобождаем память
}
