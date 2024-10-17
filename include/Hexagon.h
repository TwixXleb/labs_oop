#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"

class Hexagon : public Figure {
private:
    std::pair<double, double> center_coords;
    std::pair<double, double>* vertices;
    size_t vertex_count = 6;
    double side;

public:
    Hexagon(double x = 0, double y = 0, double side_length = 1);

    Hexagon(const Hexagon& other);

    Hexagon& operator=(const Hexagon& other);

    Hexagon(Hexagon&& other) noexcept;
    Hexagon& operator=(Hexagon&& other) noexcept;

    bool operator==(const Figure& other) const override;

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;
    std::pair<double, double> center() const override;

    void move(double new_x, double new_y) override;
    void rotate(double angle) override;

    Figure* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Hexagon& hexagon);
    friend std::istream& operator>>(std::istream& is, Hexagon& hexagon);


    ~Hexagon() override;

private:
    void calculate_vertices(double side_length);
};

#endif // HEXAGON_H
