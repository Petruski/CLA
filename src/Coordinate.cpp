//
// Created by Mattias Lindell on 2022-04-26.
//

#include <cmath>
#include <iostream>
#include "Coordinate.h"
#include "UtilityFunctions.h"

/**
 * Getter
 * @return This coordinate's latitude
 */
double Coordinate::getLatitude() const {
    return m_latitude;
}

/**
 * Setter
 * @param latitude set m_latitude
 * @throws out_of_range exception if latitude is invalid
 */
void Coordinate::setLatitude(double latitude) {
    if (latitude > 90.0 || latitude < -90.0)
        throw std::out_of_range("Latitude is out of range");
    m_latitude = latitude;
}

/**
 * Getter
 * @return This coordinate's longitude
 */
double Coordinate::getLongitude() const {
    return m_longitude;
}

/**
 * setter
 * @param longitude set longitude
 * @throws out_of_range exception if longitude is invalid
 */
void Coordinate::setLongitude(double longitude) {
    if (longitude > 180.0 || longitude < -180.0)
        throw std::out_of_range("Longitude is out of range");
    m_longitude = longitude;
}

/**
 * Sets both latitude and longitude
 * @param latitude
 * @param longitude
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void Coordinate::set(double latitude, double longitude) {
    setLatitude(latitude);
    setLongitude(longitude);
}

/**
 * Calculates real earth distance between this and another coordinate
 * @param coordinate The coordinate to calculate distance too
 * @return the distance in meters
 */
double Coordinate::getDistanceTo(Coordinate coordinate) const {

    // use average radius from this and the other coordinate
    double radius = (getEarthRadius() + coordinate.getEarthRadius()) / 2;

    double lat1 = utils::toRadians(m_latitude);
    double lat2 = utils::toRadians(coordinate.m_latitude);
    double lon1 = utils::toRadians(m_longitude);
    double lon2 = utils::toRadians(coordinate.m_longitude);

    // use Haversine Formula to calculate distance between two coordinates on earth
    // φ = m_latitude in radians
    // λ = m_longitude in radians
    // r = earth's radius in meters
    // d = distance in meters
    // d = 2 * r * arcsin(√(    sin²((φ2-φ1)/2) + cos(φ1) * cos(φ2) * sin²((λ2-λ1)/2)  ))

    return 2 * radius * asin(sqrt(pow(sin((lat2-lat1)/2), 2.0) + cos(lat1) * cos(lat2) * pow(sin((lon2-lon1)/2), 2.0)));
}

/**
 * Calculates real earth distance between this and another coordinate
 * @param latitude m_latitude of the other coordinate
 * @param longitude m_longitude of the other coordinate
 * @return the distance in meters
 */
double Coordinate::getDistanceTo(double latitude, double longitude) const {
    Coordinate c;
    try {
        c.setLatitude(latitude);
        c.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
        return 0.0;
    }
    return getDistanceTo(c);
}

double Coordinate::getBearingTo(Coordinate coordinate) const {

    // ‘L’ be the longitude,
    // ‘θ’ be latitude,
    // ‘β‘ be Bearing.
    // β = atan2(X,Y)
    // X = cos θb * sin ∆L
    // Y = cos θa * sin θb – sin θa * cos θb * cos ∆L
    double lat_a = utils::toRadians(this->getLatitude());
    double lon_a = utils::toRadians(this->getLongitude());
    double lat_b = utils::toRadians(coordinate.getLatitude());
    double lon_b = utils::toRadians(coordinate.getLongitude());
    double delta_lon = lon_b - lon_a;
    double x = std::cos(lat_b) * sin(delta_lon);
    double y = std::cos(lat_a) * sin(lat_b) - sin(lat_a) * cos(lat_b) * cos(delta_lon);

    return utils::toDegrees(std::atan2(x, y));

    /*
    double distance_y = coordinate.getLatitude() - this->getLatitude();
    double distance_x = std::cos(M_PI / 180 * this->getLatitude()) * (coordinate.getLongitude() - this->getLongitude());
    return std::atan2(distance_y, distance_x) * 180 / M_PI;
     */
}

/**
 * Get earth radius at this coordinate's position
 * @return the radius in meters
 */
double Coordinate::getEarthRadius() const {

    // Earth radius at the equator a = 6378137.0
    // Earth radius at pole b = 6356752.
    // source: https://nssdc.gsfc.nasa.gov/planetary/factsheet/earthfact.html

    double a = 6378137.0;
    double b = 6356752.0;
    double l = utils::toRadians(m_latitude);

    // radius r, m_latitude l: r(l) = √( ((a²*cos(l))² + (b²*sin(l))²) / ((a*cos(l)² + (b*sin(l)²) )
    return sqrt(  (pow(a * a * cos(l), 2) + pow(b * b * sin(l), 2)) / (pow(a * cos(l), 2) + pow(b * sin(l), 2)) );
}

/**
 * Add a decimal degrees value to a coordinate
 * @param latitude the m_latitude value to add
 * @param longitude the m_longitude value to add
 */
void Coordinate::add(double latitude, double longitude) {
    m_latitude += latitude;
    m_longitude += longitude;

    // Fix m_latitude
    while (m_latitude > 90) {
        m_latitude = 180 - m_latitude;
    }
    while (m_latitude < -90) {
        m_latitude = -180 - m_latitude;
    }

    // Fix m_longitude
    while (m_longitude > 180) {
        m_longitude =  -360 + m_longitude;
    }
    while (m_longitude < -180) {
        m_longitude = 360 + m_longitude;
    }
}