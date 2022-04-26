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
