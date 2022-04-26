//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CUSTOMERLOCATIONALGORITHMAPP_COORDINATE_H
#define CUSTOMERLOCATIONALGORITHMAPP_COORDINATE_H


#include <numbers>

class Coordinate {
protected:
    double latitude;
    double longitude;
public:
    Coordinate(double latitude, double longitude);

    [[nodiscard]] double getLatitude() const;
    void setLatitude(double aLatitude);
    [[nodiscard]] double getLongitude() const;
    void setLongitude(double aLongitude);

    double getDistanceTo(Coordinate coordinate);

private:
    double toRadian(double degrees) { return degrees * std::numbers::pi / 180 ; }

};


#endif //CUSTOMERLOCATIONALGORITHMAPP_COORDINATE_H
