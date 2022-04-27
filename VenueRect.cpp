//
// Created by dreadlopp on 2022-04-26.
//

#include "VenueRect.h"

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

    // the position is considered to be a circle where the radius
    // is the error margin
    double circleX = position.getLatitude();
    double circleY = position.getLongitude();
    double radius = position.getAccuracy();

    // the venue is a rectangel, it's midpoint is x,y

    return false;
}

bool VenueRect::isInsideRect(double x, double y) {

    // move rectangle to be parallel with x-axis
    double moveY = cornerA.getLongitude() - cornerB.getLongitude();
    double moveX = cornerA.getDistanceTo(cornerB) - cornerA.getDistanceTo(cornerA.getLatitude(), cornerB.getLongitude());

    double rectTopLeftX = cornerA.getLatitude();
    double rectTopLeftY = cornerA.getLongitude();
    double rectBottomRightX = cornerC.getLatitude() + moveX;
    double rectBottomRightY = cornerC.getLongitude() + moveY;
    x += moveX;
    y += moveY;


    return false;
}
