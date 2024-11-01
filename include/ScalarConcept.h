
#ifndef LAB0_SCALARCONCEPT_H
#define LAB0_SCALARCONCEPT_H

// ScalarConcept.h
#pragma once
#include <type_traits>

// Concept to ensure T is a scalar type
template<typename T>
concept Scalar = std::is_arithmetic_v<T>;

#endif //LAB0_SCALARCONCEPT_H
