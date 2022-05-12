//
// Created by dreadlopp on 2022-04-26.
//

#include <cmath>
#include "../include/Coordinate.h"

Coordinate::Coordinate(double latitude, double longitude) : latitude(latitude), longitude(longitude) {}

double Coordinate::getLatitude() const {
    return latitude;
}

void Coordinate::setLatitude(double aLatitude) {
    latitude = aLatitude;
}

double Coordinate::getLongitude() const {
    return longitude;
}

void Coordinate::setLongitude(double aLongitude) {
    longitude = aLongitude;
}

double Coordinate::getDistanceTo(Coordinate coordinate) {

    const double RADIUS = 6371000;

    double lat1 = toRadian(latitude);
    double lat2 = toRadian(coordinate.latitude);
    double lon1 = toRadian(longitude);
    double lon2 = toRadian(coordinate.longitude);

    // use Haversine Formula to calculate distance between two coordinates on earth
    // φ = latitude in radians
    // λ = longitude in radians
    // r = earth's radius in meters
    // d = distance in meters
    // d = 2 * r * arcsin(√(    sin²((φ2-φ1)/2) + cos(φ1) * cos(φ2) * sin²((λ2-λ1)/2)  ))

    return 2 * RADIUS * std::asin(sqrt(std::pow(std::sin((lat2-lat1)/2), 2.0) + std::cos(lat1) * std::cos(lat2) * pow(std::sin((lon2-lon1)/2), 2.0)));
}

double Coordinate::getDistanceTo(double lat, double lon) {
    Coordinate c(lat, lon);
    return getDistanceTo(c);
}

double Coordinate::getEucDistanceTo(Coordinate coordinate) const {

    double x1 = latitude;
    double y1 = longitude;
    double x2 = coordinate.getLatitude();
    double y2 = coordinate.getLongitude();

    return sqrt(std::abs(pow((x2-x1),2) + pow((y2-y1),2)));
}

double Coordinate::getEucDistanceTo(double lat, double lon) const {
    Coordinate c(lat, lon);
    return getEucDistanceTo(c);
}

double Coordinate::getBearingTo(Coordinate coordinate) {
    double distance_y = coordinate.getLatitude() - this->getLatitude();
    double distance_x = std::cos(M_PI/180 * this->getLatitude()) * (coordinate.getLongitude() - this->getLongitude());
    return std::atan2(distance_y, distance_x) * 180/M_PI;
}
