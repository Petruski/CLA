//
// Created by Petrus Söderström on 2022-04-30.
//

#ifndef CLA_POSITIONPARSER_H
#define CLA_POSITIONPARSER_H


#include <utility>

#include "DataStreamIterator.hpp"
#include "Position.h"

class PositionParser {
public:
    static void filter(DataStreamIterator<Position> &iterator, double aFilter);
    static Position average(DataStreamIterator<Position> &iterator, int amount);
};


#endif //CLA_POSITIONPARSER_H