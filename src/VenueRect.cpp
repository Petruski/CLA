//
// Created by Mattias Lindell on 2022-04-26.
//

#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include "../include/VenueRect.h"

/**
 * Helper function for the setters
 * @param latitude
 * @param longitude
 * @param corner
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void VenueRect::setCorner(double latitude, double longitude, Coordinate &corner) {
    try {
        corner.setLatitude(latitude);
        corner.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        throw e;
    }
}

/**
 * setter
 * @param latitude the corner's latitude
 * @param longitude the corner's longitude
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void VenueRect::setCornerA(double latitude, double longitude) {
    setCorner(latitude, longitude, cornerA);
}

/**
 * setter
 * @param latitude the corner's latitude
 * @param longitude the corner's longitude
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void VenueRect::setCornerB(double latitude, double longitude) {
    setCorner(latitude, longitude, cornerB);
}

/**
 * setter
 * @param latitude the corner's latitude
 * @param longitude the corner's longitude
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void VenueRect::setCornerC(double latitude, double longitude) {
    setCorner(latitude, longitude, cornerC);
}

/**
 * setter
 * @param latitude the corner's latitude
 * @param longitude the corner's longitude
 * @throws out_of_range exception if latitude or longitude is invalid
 */
void VenueRect::setCornerD(double latitude, double longitude) {
    setCorner(latitude, longitude, cornerD);
}

/**
 * Calculate the venue's circumference
 * @return the circumference in meters
 */
double VenueRect::getCircumference() {
    return cornerA.getDistanceTo(cornerB) + cornerB.getDistanceTo(cornerC) + cornerC.getDistanceTo(cornerD) + cornerD.getDistanceTo(cornerA);
}

/**
 * Check whether a position is inside the venue using the Monte Carlo method
 * @param position the position that is checked to see whether iis inside
 * @return true if the position is inside
 */
bool VenueRect::isInside(Position position) {

    // do monte carlo test
    double hits = 0; // number of generated positions that are both within position perimeter and within venue perimeter
    for (int i = 0; i < NO_OF_RANDOM_MC_VARIABLES; i++) {

        // Create random double generator that generates coordinates within a circle drawn around the position
        // where the radius is the accuracy.
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_real_distribution<double> dis(-position.getAccuracy(), position.getAccuracy());
        double latitude = position.getLatitude() + dis(gen);
        double longitude = position.getLongitude() + dis(gen);

        // increase hits if coordinate is inside venue
        if (isInside(latitude, longitude))
            hits++;
    }

    // calculate probability of being inside and return true if probability is equal to or greater the constant value
    if (hits / NO_OF_RANDOM_MC_VARIABLES >= IS_INSIDE_LIMIT)
        return true;

    return false;
}

/**
 * Check whether a coordinate is inside the venue
 * @param latitude latitude of the coordinate
 * @param longitude longitude of the coordinate
 * @return
 */
bool VenueRect::isInside(double latitude, double longitude) {

    // a point P is outside the bounds of a rectangle (the venue) with the corners ABCD if the sum of the areas of the triangles
    // PAB + PBC + PCD + PDA is greater than the area of the rectangle
    // to account for floating point errors, the venue's coordinates are moved about 1 cm apart to increase its area

    // add about a cm in the decimal GNSS coordinate system
    const double INCREASE_RECT_AREA =  0.0000001; // degrees

    // venue area. The venue is projected on a 2d plane using coordinates in decimal degrees as positions of the corners.
    // the area calculated is not real area, it is only used as a comparison to the area of the triangles
    double venueArea = (cornerA.getEucDistanceTo(cornerB) + INCREASE_RECT_AREA) * (cornerB.getEucDistanceTo(cornerC) + INCREASE_RECT_AREA);

    // the point
    Coordinate p;
    try {
        p.setLatitude(latitude);
        p.setLongitude(longitude);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
        return false;
    }

    // area of triangles PAB, PBC, PCD, PDA
    double trianglesArea = areaTriangle(p,cornerA, cornerB) + areaTriangle(p, cornerB, cornerC) + areaTriangle(p, cornerC, cornerD) +
            areaTriangle(p, cornerD, cornerA);

    // if area of triangles is bigger than area of rectangle, the coordinate is outside
    // std::cout << std::fixed << std::setprecision(10 )<< "Pos: ("<< latitude << ", " << longitude << ") Tri: " << trianglesArea << " Rec: " << venueArea << std::endl;
    if (trianglesArea > venueArea)
        return false;

    return true;
}

/**
 * Calculates the area of a triangle using coordinates measured in decimal degrees. The area is not real area, it is only
 * to be used to compare against other geometric objects in a decimal degree grid to measure their relative size
 * @param cA corner a
 * @param cB corner b
 * @param cC corner c
 * @return the area of the triangle, measured in degrees
 */
double VenueRect::areaTriangle(Coordinate cA, Coordinate cB, Coordinate cC) {

    // area T of triangle: T = sqrt(s(s-a)(s-b)(s-c)) where a, b and c are length of sides and s is semi perimeter
    double a = cA.getEucDistanceTo(cB);
    double b = cB.getEucDistanceTo(cC);
    double c = cC.getEucDistanceTo(cA);
    double s = (a+b+c) / 2;

    return std::sqrt( s * (s-a) * (s-b) * (s-c));
}




