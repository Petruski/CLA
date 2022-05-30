//
// Created by dreadlopp on 2022-05-29.
//

#ifndef CLA_UTILITYFUNCTIONS_H
#define CLA_UTILITYFUNCTIONS_H

#include <cmath>
#include "Constants.h"

namespace utils {
    bool equal(double a, double b);

    // convert decimal degrees to radians and vice versa
    double toRadians(double degrees);
    double toDegrees(double radians);

    double toDouble(char *c);

    int toInt(char *c);
}

#endif //CLA_UTILITYFUNCTIONS_H
