//
// Created by Mattias Lindell on 2022-04-26.
//

#include "../include/VenueRect.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"

VenueRect::VenueRect(Coordinate cornerA, Coordinate cornerB, Coordinate cornerC, Coordinate cornerD) {

    // sort corners
    std::vector<Coordinate> corners {cornerA, cornerB, cornerC, cornerD};
    DataStreamIterator<Coordinate> cornerIt (corners);
    // Order the corners SW, NW, NE, SE
    corners = PositionParser::order(cornerIt);

    // set corners
    m_cornerSW = corners[0];
    m_cornerNW = corners[1];
    m_cornerNE = corners[2];
    m_cornerSE = corners[3];
}

VenueRect::VenueRect(Coordinate mapMarker) {
    this->m_mapMarker = mapMarker;
}










