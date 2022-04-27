//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CLA_VENUERECT_H
#define CLA_VENUERECT_H


#include "Venue.h"

class VenueRect: public Venue {
private:
    Coordinate cornerA, cornerB, cornerC, cornerD;

    // private functions
    bool isInsideRect(double x, double y);

public:
    VenueRect() {}

    void setCornerA(double latitude, double longitude);
    void setCornerB(double latitude, double longitude);
    void setCornerC(double latitude, double longitude);
    void setCornerD(double latitude, double longitude);

    double getCircumference() override;
    bool isInside(Position position) override;
};


#endif //CLA_VENUERECT_H
