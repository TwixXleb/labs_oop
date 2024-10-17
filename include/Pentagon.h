#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include <iostream>

class Pentagon : public Figure {
private:
    std::pair<double, double> center_coords;  // Центр фигуры
    std::pair<double, double>* vertices;      // Вершины фигуры (динамический массив)
    size_t vertex_count = 5;                  // Количество вершин (5 для пятиугольника)

public:
    Pentagon(double x = 0, double y = 0, double side_length = 1);

    // Операции копирования и перемещения
    Pentagon(const Pentagon& other);
    Pentagon& operator=(const Pentagon& other);
    Pentagon(Pentagon&& other) noexcept;
    Pentagon& operator=(Pentagon&& other) noexcept;

    // Операция сравнения
    bool operator==(const Figure& other) const override;

    // Виртуальные методы
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    double area() const override;
    std::pair<double, double> center() const override;
    void move(double new_x, double new_y) override;
    void rotate(double angle) override;
    Figure* clone() const override;

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Pentagon& pentagon);
    friend std::istream& operator>>(std::istream& is, Pentagon& pentagon);

    // Деструктор
    ~Pentagon() override;

private:
    void calculate_vertices(double side_length);
};

#endif // PENTAGON_H
