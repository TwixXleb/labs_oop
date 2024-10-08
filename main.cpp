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
    yens.check_balance();
    yens.withdraw("100.00");
    yens.check_balance();
    yens.add("200.50");
    yens.check_balance();
    yens.convert_to(Currency::EUR);
    yens.check_balance();

    return 0;

}
