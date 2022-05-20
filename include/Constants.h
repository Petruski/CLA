/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-05-19
 * @brief The class represents a coordinate on earth written in decimal degrees
 */

#ifndef CLA_CONSTANTS_H
#define CLA_CONSTANTS_H

// Settings defaults, controlled with command line arguments

#include <string>

// filename for file containing position data
const std::string DEFAULT_FILENAME = "positions.txt";

// no of monte carlo variables, higher value means better accuracy of Monte Carlo but slower app
const int NO_OF_RANDOM_MC_VARIABLES = 10000;

// How big part of the circle around a position must be inside a venue for the position to be considered to be inside
// [0-1] 1 means whole circle must be inside for the position to count as inside. 0.5 means half and 0 means none, etc
const double IS_INSIDE_LIMIT = 0.50;

#endif //CLA_CONSTANTS_H
