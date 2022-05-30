//
// Created by Mattias Lindell on 2022-04-26.
//

#include <stdexcept>
#include <iostream>
#include "../include/Venue.h"

/**
 * setter
 * @param latitude m_latitude of map marker
 * @param longitude m_longitude of map marker
 */
void Venue::setMapMarker(double latitude, double longitude) {
    try {
        mapMarker.setLatitude(latitude);
        mapMarker.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
    }
}

/**
 * getter
 * @return name of the venue
 */
const std::string &Venue::getName() const { return name; }

/**
 * getter
 * @return a coordinate, the map marker
 */
const Coordinate &Venue::getMapMarker() const { return mapMarker; }

void Venue::setName(const std::string &aName) { name = aName; }
