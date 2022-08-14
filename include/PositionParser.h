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
    static std::vector<Coordinate> order(DataStreamIterator<Coordinate> &iterator);
    static void filter(DataStreamIterator<Position> &iterator, double aFilter);
    static void filter(DataStreamIterator<Position> &iterator, double aFilter, Coordinate centrePoint);
    static Position average(DataStreamIterator<Position> &iterator, int seconds);
    static Position median(DataStreamIterator<Position> &iterator, int seconds);
};


#endif //CLA_POSITIONPARSER_H
