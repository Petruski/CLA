//
// Created by Mattias Lindell on 2022-04-26.
//

#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include "../include/VenueRect.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"
#include "Rectangle.h"

VenueRect::VenueRect(Coordinate cornerA, Coordinate cornerB, Coordinate cornerC, Coordinate cornerD) {

    // sort corners
    std::vector<Coordinate> corners {cornerA, cornerB, cornerC, cornerD};
    DataStreamIterator<Coordinate> cornerIt (corners);
    // Order the corners SW, NW, NE, SE
    PositionParser::order(cornerIt);

    // set corners
    m_cornerSW = corners[0];
    m_cornerNW = corners[1];
    m_cornerNE = corners[2];
    m_cornerSE = corners[3];
}

/**
 * Calculate the venue's circumference
 * @return the circumference in meters
 */
double VenueRect::getCircumference() {
    return m_cornerSW.getDistanceTo(m_cornerNW) + m_cornerNW.getDistanceTo(m_cornerNE) + m_cornerNE.getDistanceTo(m_cornerSE) + m_cornerSE.getDistanceTo(m_cornerSW);
}










