#include <iostream>
#include <string>
#include "include/troll_defence.h"

int main() {

    std::string troll_message;
    getline(std::cin, troll_message);
    std::string result = troll_defence(troll_message);
    std::cout << result << std::endl;
    return 0;

}
