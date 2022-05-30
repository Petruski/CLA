/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a coordinate on earth written in decimal degrees
 */

#ifndef CLA_COORDINATE_H
#define CLA_COORDINATE_H

#include <numbers>

class Coordinate {
protected:
    double m_latitude;
    double m_longitude;
public:
    Coordinate(): m_latitude(0), m_longitude(0) {}

    // getters and setters
    [[nodiscard]] double getLatitude() const;
    void setLatitude(double latitude);
    [[nodiscard]] double getLongitude() const;
    void setLongitude(double longitude);
    void set(double latitude, double longitude);

    // get earth radius at this coordinate in meters
    [[nodiscard]] double getEarthRadius() const;

    // Get bearing (angle) between two coordinates
    [[nodiscard]] double getBearingTo(Coordinate coordinate) const;

    // add degrees to coordinate
    void add(double latitude, double longitude);

    // new coordinate given bearing and distance from another
    [[nodiscard]] Coordinate newCoordinate(double bearing, double distance) const;

    // real earth distance in meters
    [[nodiscard]] double getDistanceTo(Coordinate coordinate) const;
    [[nodiscard]] double getDistanceTo(double latitude, double longitude) const;

    // Euclidean distance in decimal degrees
    [[nodiscard]] double getEucDistanceTo(Coordinate coordinate) const;
    [[nodiscard]] double getEucDistanceTo(double latitude, double longitude) const;

    bool operator==(const Coordinate& coordinate) const {
        return this->m_latitude == coordinate.m_latitude && this->m_longitude == coordinate.m_longitude;
    }
};

#endif //CLA_COORDINATE_H
