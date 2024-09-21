#include <iostream>
#include <string>
#include "include/troll_defence.h"

int main() {

    std::string troll_message;
    getline(std::cin, troll_message);
    troll_defence(troll_message);
    return 0;

}
