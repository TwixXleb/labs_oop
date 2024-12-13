#pragma once
#include <string>

struct ComplexType {
    int a;
    double b;
    std::string c;

    bool operator==(const ComplexType& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};
