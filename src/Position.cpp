//
// Created by dreadlopp on 2022-04-26.
//

#include "../include/Position.h"
#include <stdexcept>
#include <iostream>

/**
 * Getter
 * @return m_accuracy radius in meters
 */
double Position::getAccuracy() const {
    return m_accuracy;
}

/**
 * setter
 * @param aAccuracy set m_accuracy radius in meters
 */
void Position::setAccuracy(double aAccuracy) {
    m_accuracy = aAccuracy;
}

/**
 * getter
 * @return timestamp of the m_time of the measurement
 */
long Position::getTime() const {
    return m_time;
}

/**
 * setter
 * @param aTime sets timestamp
 */
void Position::setTime(long aTime) {
    m_time = aTime;
}

/**
 * getter
 * @return the m_provider of the GNSS position
 */
const std::string &Position::getProvider() const {
    return m_provider;
}

/**
 * setter
 * @param provider sets the m_provider of the measurement
 */
void Position::setProvider(const std::string &provider) {
    Position::m_provider = provider;
}
/**
 * Check if a coordinate is within the perimeter of the accuracy. Includes values on the perimeter.
 * @param p the coordinate that is checked against this position
 * @return true if coordinate is within or on m_accuracy perimeter
 */
 /*
bool Position::isInside(Coordinate p) {

    if (getDistanceTo(p) >= m_accuracy)
        return false;

    return true;
}
*/

/**
 * Check if a coordinate is within the perimeter of the accuracy. Includes values on the perimeter.
 * @param latitude m_latitude of the coordinate that is checked against this position
 * @param longitude m_longitude of the coordinate that is checked against this position
 * @return true if coordinate is within or on m_accuracy perimeter
 */
 /*
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
*/
