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
    double latitude;
    double longitude;
public:
    Coordinate(): latitude(0), longitude(0) {}

    // getters and setters
    [[nodiscard]] double getLatitude() const;
    void setLatitude(double aLatitude);
    [[nodiscard]] double getLongitude() const;
    void setLongitude(double aLongitude);

    // get earth radius at this coordinate in meters
    [[nodiscard]] double getEarthRadius() const;

    // real earth distance in meters
    [[nodiscard]] double getDistanceTo(Coordinate coordinate) const;
    [[nodiscard]] double getDistanceTo(double lat, double lon) const;

    // Euclidean distance in decimal degrees
    [[nodiscard]] double getEucDistanceTo(Coordinate coordinate) const;
    [[nodiscard]] double getEucDistanceTo(double lat, double lon) const;

    // convert decimal degrees to radians
    static double toRadian(double degrees);
};

#endif //CLA_COORDINATE_H
