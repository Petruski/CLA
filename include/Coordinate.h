/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a coordinate on earth written in decimal degrees
 */

#ifndef CLA_COORDINATE_H
#define CLA_COORDINATE_H

#include <numbers>
#include "Point.h"

class Coordinate {
protected:
    double m_latitude;
    double m_longitude;
public:
    Coordinate(): m_latitude(0), m_longitude(0) {}
    Coordinate(double a_lat, double a_lon) : m_latitude(a_lat), m_longitude(a_lon) {}

    // getters and setters
    [[nodiscard]] double getLatitude() const;
    void setLatitude(double latitude);
    [[nodiscard]] double getLongitude() const;
    void setLongitude(double longitude);
    void set(double latitude, double longitude);

    // get earth radius at this coordinate in meters
    [[nodiscard]] double getEarthRadius() const;

    // Get bearing (angle in degrees) between two coordinates
    [[nodiscard]] double getBearingTo(Coordinate coordinate) const;

    // add degrees to coordinate
    void add(double latitude, double longitude);

    // real earth distance in meters
    [[nodiscard]] double getDistanceTo(Coordinate coordinate) const;
    [[nodiscard]] double getDistanceTo(double latitude, double longitude) const;

    bool operator==(const Coordinate& coordinate) const {
        bool sameLongitude = false;
        if (this->m_longitude == 180 && coordinate.m_longitude == -180) {
            sameLongitude = true;
        } else if (this->m_longitude == -180 && coordinate.m_longitude == 180) {
            sameLongitude = true;
        } else if (this->m_longitude == coordinate.m_longitude) {
            sameLongitude = true;
        }
        return this->m_latitude == coordinate.m_latitude && sameLongitude;
    }
};

#endif //CLA_COORDINATE_H
