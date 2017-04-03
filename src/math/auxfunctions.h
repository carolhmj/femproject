#ifndef AUXFUNCTIONS
#define AUXFUNCTIONS

#include <cmath>

#define EPSILON 1e-3

namespace AuxFunctions {
    double clampToZero(double number) {
        if (std::abs(number) < EPSILON) {
            return 0.0;
        }
        return number;
    }
}

#endif // AUXFUNCTIONS

