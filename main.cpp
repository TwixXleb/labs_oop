#include <iostream>
#include <string>
#include "include/troll_defence.h"
#include "include/Money.h"
#include "include/Pentagon.h"
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/FigureArray.h"
#include "include/Pentagon.h"
#include "include/Pentagon_02.h"
#include "include/Hexagon_02.h"
#include "include/Octagon_02.h"
#include "include/Array_02.h"
#include "include/Pentagon_02.h"

int main() {

    std::string troll_message;
    getline(std::cin, troll_message);
    std::string result = troll_defence(troll_message);
    std::cout << result << std::endl;

    Money yens("456.00", Currency::JPY);
    std::cout << yens.check_balance() << std::endl;
    yens.withdraw("100.00");
    std::cout << yens.check_balance() << std::endl;
    yens.add("200.50");
    std::cout << yens.check_balance() << std::endl;
    yens.convert_to(Currency::EUR);
    std::cout << yens.check_balance() << std::endl;

    FigureArray figureArray;
    Figure* pentagon1 = new Pentagon(0.0, 0.0, 5.0);
    Figure* pentagon2 = new Pentagon(10.0, 10.0, 3.0);
    figureArray.add(pentagon1);
    figureArray.add(pentagon2);
    std::cout << "=== Figures in the array ===\n";
    figureArray.print_all();
    std::cout << "\n=== Total area of all figures ===\n";
    std::cout << "Total area: " << figureArray.total_area() << "\n";
    std::cout << "=============================\n\n";
    std::cout << "=== Moving the first figure ===\n";
    pentagon1->move(5.0, 5.0);
    std::cout << "Moved the first figure to (5.0, 5.0):\n";
    figureArray.print_all();
    std::cout << "=============================\n\n";
    std::cout << "=== Rotating the second figure by 90 degrees ===\n";
    pentagon2->rotate(3.14159 / 2);
    figureArray.print_all();
    std::cout << "=============================\n\n";
    std::cout << "=== Copying the array ===\n";
    FigureArray copiedArray = figureArray;
    copiedArray.print_all();
    std::cout << "=============================\n\n";
    std::cout << "=== Removing the first figure ===\n";
    figureArray.remove(0);
    figureArray.print_all();
    std::cout << "=============================\n\n";
    std::cout << "=== Moving the array ===\n";
    FigureArray movedArray = std::move(copiedArray);
    movedArray.print_all();
    std::cout << "=============================\n\n";

    try {
        // Создаем пятиугольник с центром в (0, 0) и длиной стороны 5
        Point_02<int> center1(0, 0);
        int side_length1 = 5;
        Pentagon_02<int> pentagon(center1, side_length1);

        // Выводим информацию о пятиугольнике
        std::cout << "Pentagon_02:\n";
        pentagon.Print(std::cout);
        std::cout << "Area: " << pentagon.Area() << "\n";
        std::cout << "Center: " << pentagon.Center() << "\n\n";

        // Создаем шестиугольник с центром в (10, 10) и длиной стороны 7
        Point_02<int> center2(10, 10);
        int side_length2 = 7;
        Hexagon_02<int> hexagon(center2, side_length2);

        // Выводим информацию о шестиугольнике
        std::cout << "Hexagon_02:\n";
        hexagon.Print(std::cout);
        std::cout << "Area: " << hexagon.Area() << "\n";
        std::cout << "Center: " << hexagon.Center() << "\n\n";

        // Создаем восьмиугольник с центром в (-5, -5) и длиной стороны 4
        Point_02<int> center3(-5, -5);
        int side_length3 = 4;
        Octagon_02<int> octagon(center3, side_length3);

        // Выводим информацию о восьмиугольнике
        std::cout << "Octagon_02:\n";
        octagon.Print(std::cout);
        std::cout << "Area: " << octagon.Area() << "\n";
        std::cout << "Center: " << octagon.Center() << "\n\n";

        // Применяем некоторые преобразования
        pentagon.Translate(2, 3);
        hexagon.Rotate(M_PI / 4); // Поворот на 45 градусов
        octagon.Translate(-3, 1);

        // Выводим информацию после преобразований
        std::cout << "After transformations:\n";

        std::cout << "Pentagon_02:\n";
        pentagon.Print(std::cout);
        std::cout << "Center: " << pentagon.Center() << "\n\n";

        std::cout << "Hexagon_02:\n";
        hexagon.Print(std::cout);
        std::cout << "Center: " << hexagon.Center() << "\n\n";

        std::cout << "Octagon_02:\n";
        octagon.Print(std::cout);
        std::cout << "Center: " << octagon.Center() << "\n\n";

        // Сравниваем фигуры по площади
        if (pentagon.Area() < hexagon.Area()) {
            std::cout << "Pentagon_02 has smaller area than Hexagon_02.\n";
        } else {
            std::cout << "Pentagon_02 has larger or equal area than Hexagon_02.\n";
        }

        // Преобразование к double для получения площади
        double pentagon_area = static_cast<double>(pentagon);
        std::cout << "Pentagon_02 area (via cast to double): " << pentagon_area << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }


    return 0;

}
