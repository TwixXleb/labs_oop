#include <iostream>
#include "../include/troll_defence.h"
#include <string>
bool isvowel(char letter) {

    int k = 0;
    char vowels[6] = {'a', 'e', 'i', 'o', 'u', 'y'};

    for (int i = 0; i < 6; i++){

        if (tolower(letter) == vowels[i]) k++;

    }

    if (k == 1) return true;
    else return false;

}

std::string troll_defence(std::string troll_message) {

    int i = 0;

    while (i < troll_message.size()){

        if (isvowel(troll_message[i])) troll_message.erase(i, 1);
        else i++;

    }

    return troll_message;

}
