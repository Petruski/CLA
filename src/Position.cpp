//
// Created by dreadlopp on 2022-04-26.
//

#include "../include/Position.h"
#include <cmath>
#include <stdexcept>
#include <iostream>

/**
 * Getter
 * @return accuracy radius in meters
 */
double Position::getAccuracy() const {
    return accuracy;
}

/**
 * setter
 * @param aAccuracy set accuracy radius in meters
 */
void Position::setAccuracy(double aAccuracy) {
    accuracy = aAccuracy;
}

/**
 * getter
 * @return timestamp of the time of the measurement
 */
long Position::getTime() const {
    return time;
}

/**
 * setter
 * @param aTime sets timestamp
 */
void Position::setTime(long aTime) {
    time = aTime;
}

/**
 * getter
 * @return the provider of the GNSS position
 */
const std::string &Position::getProvider() const {
    return provider;
}

/**
 * setter
 * @param provider sets the provider of the measurement
 */
void Position::setProvider(const std::string &provider) {
    Position::provider = provider;
}

/**
 * Check if a coordinate is within the perimeter of the accuracy. Includes values on the perimeter.
 * @param p the coordinate that is checked against this position
 * @return true if coordinate is within or on accuracy perimeter
 */
bool Position::isInside(Coordinate p) {


    if (getDistanceTo(p) >= accuracy)
        return false;

    return true;
}

/**
 * Check if a coordinate is within the perimeter of the accuracy. Includes values on the perimeter.
 * @param latitude latitude of the coordinate that is checked against this position
 * @param longitude longitude of the coordinate that is checked against this position
 * @return true if coordinate is within or on accuracy perimeter
 */
bool Position::isInside(double latitude, double longitude) {

    Coordinate p;
    try {
        p.setLatitude(latitude);
        p.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
        return false;
    }
    return isInside(p);
}

bool Position::operator==(const Position &p) {
    return this->latitude == p.latitude &&
           this->longitude == p.longitude &&
           this->accuracy == p.accuracy &&
           this->time == p.time &&
           this->provider == p.provider;
}