#ifndef FIGURE_ARRAY_H
#define FIGURE_ARRAY_H

#include "Figure.h"

class FigureArray {
private:
    Figure** figures;  // Динамический массив указателей на фигуры
    size_t size;       // Текущий размер
    size_t capacity;   // Вместимость

    void resize(size_t new_capacity);  // Увеличение размера массива

public:
    FigureArray();
    ~FigureArray();
    FigureArray(const FigureArray& other);            // Конструктор копирования
    FigureArray& operator=(const FigureArray& other); // Оператор копирования
    FigureArray(FigureArray&& other) noexcept;        // Конструктор перемещения
    FigureArray& operator=(FigureArray&& other) noexcept; // Оператор перемещения

    void add(Figure* fig);     // Добавление фигуры
    void remove(size_t index); // Удаление фигуры по индексу
    void print_all() const;    // Вывод всех фигур
    double total_area() const; // Общая площадь всех фигур
};

#endif // FIGURE_ARRAY_H
