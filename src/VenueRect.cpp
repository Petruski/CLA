//
// Created by dreadlopp on 2022-04-26.
//

#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include "../include/VenueRect.h"

void VenueRect::setCornerA(double latitude, double longitude) {
    cornerA.setLatitude(latitude);
    cornerA.setLongitude(longitude);
}

void VenueRect::setCornerB(double latitude, double longitude) {
    cornerB.setLatitude(latitude);
    cornerB.setLongitude(longitude);
}

void VenueRect::setCornerC(double latitude, double longitude) {
    cornerC.setLatitude(latitude);
    cornerC.setLongitude(longitude);
}

void VenueRect::setCornerD(double latitude, double longitude) {
    cornerD.setLatitude(latitude);
    cornerD.setLongitude(longitude);
}

double VenueRect::getCircumference() {
    return cornerA.getDistanceTo(cornerB) + cornerB.getDistanceTo(cornerC) + cornerC.getDistanceTo(cornerD) + cornerD.getDistanceTo(cornerA);
}

bool VenueRect::isInside(Position position) {

    // do monte carlo test

    double hits = 0; // number of generated positions that are both in position perimeter and in venue perimeter
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

    // calculate probability of being inside and return true if probability is equal or greater the constant value
    if (hits / NO_OF_RANDOM_MC_VARIABLES >= IS_INSIDE_LIMIT)
        return true;

    return false;
}

bool VenueRect::isInside(double latitude, double longitude) {

    // a point P is outside a rectangle (the venue) with the corners ABCD's bounds if the area of the triangles
    // PAB + PBC + PCD + PDA is greater than the area of the rectangle
    // to account for floating point errors, the venue's coordinates are moved about 1 cm apart to increase area

    // 1.11 cm in the decimap gnss coordinate system
    const double INCREASE_RECT_AREA =  0.0000001;
    // venue area
    double venueArea = (cornerA.getEucDistanceTo(cornerB) + INCREASE_RECT_AREA) * (cornerB.getEucDistanceTo(cornerC) + INCREASE_RECT_AREA);

    // the point
    Coordinate p(latitude, longitude);

    // area of triangles PAB, PBC, PCD, PDA
    double trianglesArea = areaTriangle(p,cornerA, cornerB) + areaTriangle(p, cornerB, cornerC) + areaTriangle(p, cornerC, cornerD) +
            areaTriangle(p, cornerD, cornerA);

    // if area of triangles is bigger than rectangle, the coordinate is outside
    if (trianglesArea > venueArea + 0.00001)
        return false;

    return true;
}

double VenueRect::areaTriangle(Coordinate ca, Coordinate cb, Coordinate cc) {

    // area T of triangle: T = sqrt(s(s-a)(s-b)(s-c)) where a, b and c are length of sides and s is semi perimeter
    double a = ca.getEucDistanceTo(cb);
    double b = cb.getEucDistanceTo(cc);
    double c = cc.getEucDistanceTo(ca);
    double s = (a+b+c) / 2;

    return std::sqrt( s * (s-a) * (s-b) * (s-c));
}


