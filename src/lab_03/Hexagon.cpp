#include "../../include/Hexagon.h"
#include <cmath>
#include <iostream>

Hexagon::Hexagon(double x, double y, double side_length) : center_coords(x, y) {
    vertices = new std::pair<double, double>[vertex_count];
    calculate_vertices(side_length);
}

Hexagon::Hexagon(const Hexagon& other) : center_coords(other.center_coords) {
    vertices = new std::pair<double, double>[vertex_count];
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i] = other.vertices[i];
    }
}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        center_coords = other.center_coords;
        delete[] vertices;
        vertices = new std::pair<double, double>[vertex_count];
        for (size_t i = 0; i < vertex_count; ++i) {
            vertices[i] = other.vertices[i];
        }
    }
    return *this;
}

Hexagon::Hexagon(Hexagon&& other) noexcept : center_coords(other.center_coords), vertices(other.vertices) {
    other.vertices = nullptr;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    if (this != &other) {
        delete[] vertices;
        center_coords = other.center_coords;
        vertices = other.vertices;
        other.vertices = nullptr;
    }
    return *this;
}

bool Hexagon::operator==(const Figure& other) const {
    const Hexagon* h = dynamic_cast<const Hexagon*>(&other);
    if (!h) return false;
    if (center_coords != h->center_coords) return false;
    for (size_t i = 0; i < vertex_count; ++i) {
        if (vertices[i] != h->vertices[i]) return false;
    }
    return true;
}

double Hexagon::area() const {
    double s = std::sqrt(std::pow(vertices[0].first - vertices[1].first, 2) + std::pow(vertices[0].second - vertices[1].second, 2));
    return (3.0 * std::sqrt(3) * s * s) / 2.0;
}

void Hexagon::print(std::ostream& os) const {
    os << "Hexagon with center (" << center_coords.first << ", " << center_coords.second << ") and vertices: \n";
    for (size_t i = 0; i < vertex_count; ++i) {
        os << "(" << vertices[i].first << ", " << vertices[i].second << ")\n";
    }
}

std::ostream& operator<<(std::ostream& os, const Hexagon& hexagon) {
    os << "Hexagon with center (" << hexagon.center_coords.first << ", " << hexagon.center_coords.second << ") and vertices:\n";
    for (size_t i = 0; i < hexagon.vertex_count; ++i) {
        os << "(" << hexagon.vertices[i].first << ", " << hexagon.vertices[i].second << ")\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Hexagon& hexagon) {
    std::cout << "Enter center coordinates (x, y): ";
    is >> hexagon.center_coords.first >> hexagon.center_coords.second;

    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;

    hexagon.calculate_vertices(side_length);
    return is;
}

void Hexagon::read(std::istream& is) {
    std::cout << "Enter the coordinates of the center (x, y): ";
    is >> center_coords.first >> center_coords.second;
    std::cout << "Enter side length: ";
    double side_length;
    is >> side_length;
    calculate_vertices(side_length);
}

std::pair<double, double> Hexagon::center() const {
    return center_coords;
}

void Hexagon::move(double new_x, double new_y) {
    double dx = new_x - center_coords.first;
    double dy = new_y - center_coords.second;
    for (size_t i = 0; i < vertex_count; ++i) {
        vertices[i].first += dx;
        vertices[i].second += dy;
    }
    center_coords = {new_x, new_y};
}

void Hexagon::rotate(double angle) {
    for (size_t i = 0; i < vertex_count; ++i) {
        double x = vertices[i].first - center_coords.first;
        double y = vertices[i].second - center_coords.second;
        vertices[i].first = x * cos(angle) - y * sin(angle) + center_coords.first;
        vertices[i].second = x * sin(angle) + y * cos(angle) + center_coords.second;
    }
}

Figure* Hexagon::clone() const {
    return new Hexagon(*this);
}

void Hexagon::calculate_vertices(double side_length) {
    double angle = 2 * M_PI / 6;
    for (int i = 0; i < 6; ++i) {
        double x = center_coords.first + side_length * cos(i * angle);
        double y = center_coords.second + side_length * sin(i * angle);
        vertices[i] = {x, y};
    }
}

Hexagon::~Hexagon() {
    delete[] vertices;
}
