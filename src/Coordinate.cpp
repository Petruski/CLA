//
// Created by Mattias Lindell on 2022-04-26.
//

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "../include/Coordinate.h"

/**
 * Getter
 * @return This coordinate's latitude
 */
double Coordinate::getLatitude() const {
    return latitude;
}

/**
 * Setter
 * @param aLatitude set latitude
 * @throws out_of_range exception if latitude is invalid
 */
void Coordinate::setLatitude(double aLatitude) {
    if (aLatitude > 90.0 || aLatitude < -90.0)
        throw std::out_of_range("Latitude is out of range");
    latitude = aLatitude;
}

/**
 * Getter
 * @return This coordinate's longitude
 */
double Coordinate::getLongitude() const {
    return longitude;
}

/**
 * setter
 * @param aLongitude set longitude
 * @throws out_of_range exception if longitude is invalid
 */
void Coordinate::setLongitude(double aLongitude) {
    if (aLongitude > 180.0 || aLongitude < -180.0)
        throw std::out_of_range("Longitude is out of range");
    longitude = aLongitude;
}

/**
 * Calculates real earth distance between this and another coordinate
 * @param coordinate The coordinate to calculate distance too
 * @return the distance in meters
 */
double Coordinate::getDistanceTo(Coordinate coordinate) const {

    // use average radius from this and the other coordinate
    double radius = (getEarthRadius() + coordinate.getEarthRadius()) / 2;

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

    return 2 * radius * asin(sqrt(pow(sin((lat2-lat1)/2), 2.0) + cos(lat1) * cos(lat2) * pow(sin((lon2-lon1)/2), 2.0)));
}

/**
 * Calculates real earth distance between this and another coordinate
 * @param lat latitude of the other coordinate
 * @param lon longitude of the other coordinate
 * @return the distance in meters
 */
double Coordinate::getDistanceTo(double lat, double lon) const {
    Coordinate c;
    try {
        c.setLatitude(lat);
        c.setLongitude(lon);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
        return 0.0;
    }
    return getDistanceTo(c);
}

/**
 * Calculates Euclidean distance between this and another coordinate, ie distance in a 2d-plane
 * @param coordinate The coordinate to calculate distance too
 * @return the distance in decimal degrees
 */
double Coordinate::getEucDistanceTo(Coordinate coordinate) const {

    double x1 = longitude;
    double y1 = latitude;
    double x2 = coordinate.getLongitude();
    double y2 = coordinate.getLatitude();

    // fix values to be able to calculate distances correctly
    if (x1 < 0) x1 += 360;
    if (x2 < 0) x2 += 360;

    return sqrt(std::abs(pow((x2-x1),2) + pow((y2-y1),2)));
}

/**
 * Calculates Euclidean distance between this and another coordinate, ie distance in a 2d-plane
 * @param lat latitude of the other coordinate
 * @param lon longitude of the other coordinate
 * @return the distance in decimal degrees
 */
double Coordinate::getEucDistanceTo(double lat, double lon) const {
    Coordinate c;
    try {
        c.setLatitude(lat);
        c.setLongitude(lon);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
        return 0.0;
    }
    return getEucDistanceTo(c);
}


double Coordinate::getBearingTo(Coordinate coordinate) {
    double distance_y = coordinate.getLatitude() - this->getLatitude();
    double distance_x = std::cos(M_PI/180 * this->getLatitude()) * (coordinate.getLongitude() - this->getLongitude());
    return std::atan2(distance_y, distance_x) * 180/M_PI;

/**
 * Get earth radius at this coordinate's position
 * @return the radius in meters
 */
double Coordinate::getEarthRadius() const {

    // Earth radius at equator a = 6378137.0
    // Earth radius at pole b = 6356752.
    // source: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html

    double a = 6378137.0;
    double b = 6356752.0;
    double l = toRadian(latitude);

    // radius r, latitude l: r(l) = √( ((a²*cos(l))² + (b²*sin(l))²) / ((a*cos(l)² + (b*sin(l)²) )
    return sqrt(  (pow(a * a * cos(l), 2) + pow(b * b * sin(l), 2)) / (pow(a * cos(l), 2) + pow(b * sin(l), 2)) );
}

/**
 * Converts decimal degrees to radians
 * @param degrees the value to convert
 * @return the converted value in radians
 */
double Coordinate::toRadian(double degrees) {
    return degrees * std::numbers::pi / 180 ;

}
