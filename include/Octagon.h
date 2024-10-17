#ifndef OCTAGON_H
#define OCTAGON_H

#include "Figure.h"

class Octagon : public Figure {
private:
    std::pair<double, double> center_coords;
    std::pair<double, double>* vertices;
    size_t vertex_count = 8;
    double side;

public:
    Octagon(double x = 0, double y = 0, double side_length = 1);

    Octagon(const Octagon& other);

    Octagon& operator=(const Octagon& other);

    Octagon(Octagon&& other) noexcept;
    Octagon& operator=(Octagon&& other) noexcept;

    bool operator==(const Figure& other) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;
    std::pair<double, double> center() const override;

    void move(double new_x, double new_y) override;
    void rotate(double angle) override;

    friend std::ostream& operator<<(std::ostream& os, const Octagon& octagon);
    friend std::istream& operator>>(std::istream& is, Octagon& octagon);

    Figure* clone() const override;

    ~Octagon() override;

private:
    void calculate_vertices(double side_length);
};

#endif // OCTAGON_H
