#include <iostream>
#include <string>
#include "include/troll_defence.h"
#include "include/Money.h"

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

    return 0;

}
