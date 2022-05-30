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
        m_mapMarker.setLatitude(latitude);
        m_mapMarker.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
    }
}

/**
 * getter
 * @return m_name of the venue
 */
const std::string &Venue::getName() const { return m_name; }

/**
 * getter
 * @return a coordinate, the map marker
 */
const Coordinate &Venue::getMapMarker() const { return m_mapMarker; }

void Venue::setName(const std::string &aName) { m_name = aName; }
