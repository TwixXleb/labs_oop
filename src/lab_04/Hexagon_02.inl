// Hexagon_02.inl
#pragma once

template<Scalar T>
void Hexagon_02<T>::CalculateVertices() {
    vertices.clear();
    double angle = 0.0; // Start at 0 degrees
    double angle_increment = 2 * M_PI / 6; // 360 degrees / 6

    for (int i = 0; i < 6; ++i) {
        T x = center.x + side_length * std::cos(angle);
        T y = center.y + side_length * std::sin(angle);
        vertices.push_back(std::make_unique<Point_02<T>>(x, y));
        angle += angle_increment;
    }
}

template<Scalar T>
Hexagon_02<T>::Hexagon_02() : side_length(1), center(Point_02<T>(0, 0)) {
    CalculateVertices();
}

template<Scalar T>
Hexagon_02<T>::Hexagon_02(const Point_02<T>& center_, T side_length_) : center(center_), side_length(side_length_) {
    if (side_length_ <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    CalculateVertices();
}

template<Scalar T>
Hexagon_02<T>::Hexagon_02(const Hexagon_02& other) : side_length(other.side_length), center(other.center) {
    for (const auto& vertex : other.vertices) {
        vertices.push_back(std::make_unique<Point_02<T>>(*vertex));
    }
}

template<Scalar T>
Hexagon_02<T>::Hexagon_02(Hexagon_02&& other) noexcept
        : side_length(std::move(other.side_length)),
          center(std::move(other.center)),
          vertices(std::move(other.vertices)) {}

template<Scalar T>
Hexagon_02<T>& Hexagon_02<T>::operator=(const Hexagon_02& other) {
    if (this == &other)
        return *this;
    side_length = other.side_length;
    center = other.center;
    vertices.clear();
    for (const auto& vertex : other.vertices) {
        vertices.push_back(std::make_unique<Point_02<T>>(*vertex));
    }
    return *this;
}

template<Scalar T>
Hexagon_02<T>& Hexagon_02<T>::operator=(Hexagon_02&& other) noexcept {
    if (this == &other)
        return *this;
    side_length = std::move(other.side_length);
    center = std::move(other.center);
    vertices = std::move(other.vertices);
    return *this;
}

template<Scalar T>
void Hexagon_02<T>::Rotate(double angle_rad) {
    for (auto& vertex : vertices) {
        T x_new = center.x + (vertex->x - center.x) * std::cos(angle_rad) - (vertex->y - center.y) * std::sin(angle_rad);
        T y_new = center.y + (vertex->x - center.x) * std::sin(angle_rad) + (vertex->y - center.y) * std::cos(angle_rad);
        vertex->x = x_new;
        vertex->y = y_new;
    }
}

template<Scalar T>
void Hexagon_02<T>::Translate(T dx, T dy) {
center.x += dx;
center.y += dy;
for (auto& vertex : vertices) {
vertex->x += dx;
vertex->y += dy;
}
}

template<Scalar T>
double Hexagon_02<T>::Area() const {
    double area = (3 * std::sqrt(3) * side_length * side_length) / 2.0;
    return area;
}

template<Scalar T>
Point_02<T> Hexagon_02<T>::Center() const {
    return center;
}

template<Scalar T>
void Hexagon_02<T>::Print(std::ostream& os) const {
    os << "Hexagon_02 with center " << center << " and side length " << side_length << "\n";
    os << "Vertices:\n";
    for (const auto& vertex : vertices) {
        os << *vertex << "\n";
    }
}

template<Scalar T>
bool Hexagon_02<T>::operator==(const Hexagon_02& other) const {
    return side_length == other.side_length && center.x == other.center.x && center.y == other.center.y;
}

template<Scalar T>
bool Hexagon_02<T>::operator!=(const Hexagon_02& other) const {
    return !(*this == other);
}

template<Scalar T>
bool Hexagon_02<T>::operator<(const Hexagon_02& other) const {
    return this->Area() < other.Area();
}

template<Scalar T>
bool Hexagon_02<T>::operator<=(const Hexagon_02& other) const {
    return this->Area() <= other.Area();
}

template<Scalar T>
bool Hexagon_02<T>::operator>(const Hexagon_02& other) const {
    return this->Area() > other.Area();
}

template<Scalar T>
bool Hexagon_02<T>::operator>=(const Hexagon_02& other) const {
    return this->Area() >= other.Area();
}

template<Scalar T>
Hexagon_02<T>::operator double() const {
    return this->Area();
}

template<Scalar U>
std::istream& operator>>(std::istream& is, Hexagon_02<U>& hexagon) {
    std::cout << "Enter center coordinates (x y): ";
    is >> hexagon.center.x >> hexagon.center.y;
    std::cout << "Enter side length: ";
    is >> hexagon.side_length;
    if (hexagon.side_length <= 0) {
        throw std::invalid_argument("Side length must be positive");
    }
    hexagon.CalculateVertices();
    return is;
}

template<Scalar U>
std::ostream& operator<<(std::ostream& os, const Hexagon_02<U>& hexagon) {
    hexagon.Print(os);
    return os;
}
