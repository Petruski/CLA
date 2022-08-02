//
// Created by dreadlopp on 2022-05-29.
//

#include "UtilityFunctions.h"
#include <stdexcept>


bool utils::equal(double a, double b) {
        return fabs(a - b) <= EPSILON;
}



/**
 * Converts decimal degrees to radians
 * @param degrees the value to convert
 * @return the converted value in radians
 */
double utils::toRadians(double degrees) {
    return degrees * std::numbers::pi / 180;

}

/**
 * Converts radians to decimal degrees
 * @param radians the value to convert
 * @return the converted value in decimal degrees
 */
double utils::toDegrees(double radians) {
    return radians * 180 / std::numbers::pi;
}

double utils::toDouble(char *c) {
    if (isdigit(c[0])) {
        return strtod(c, nullptr);
    } else {
        throw std::runtime_error("unable to convert value to double");
    }
}

int utils::toInt(char *c) {
    if (isdigit(c[0])) {
        return std::stoi(c, nullptr,10);
    } else {
        throw std::runtime_error("unable to convert value to int");
    }
}
