#include <iostream>
#include <string>
#include "include/troll_defence.h"
#include "include/Money.h"
#include "include/Pentagon.h"
#include "include/Hexagon.h"
#include "include/Octagon.h"
#include "include/FigureArray.h"
#include "include/Pentagon.h"

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

    return 0;

}
