#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>
#include <utility>

class Figure {
public:
    virtual ~Figure() = default;

    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;
    virtual double area() const = 0;
    virtual std::pair<double, double> center() const = 0;

    virtual Figure* clone() const = 0;

    virtual bool operator==(const Figure& other) const = 0;

    virtual void move(double new_x, double new_y) = 0;
    virtual void rotate(double angle) = 0;
};

#endif // FIGURE_H
