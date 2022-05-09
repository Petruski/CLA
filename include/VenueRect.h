//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CLA_VENUERECT_H
#define CLA_VENUERECT_H


#include "Venue.h"

class VenueRect: public Venue {
private:
    const int NO_OF_RANDOM_MC_VARIABLES = 10000; // no of monte carlo variables
    const double IS_INSIDE_LIMIT = 0.50; // >= 1 means whole position with error margin must be inside, <= 0 means always outside
    Coordinate cornerA, cornerB, cornerC, cornerD;

public:
    VenueRect() {}

    void setCornerA(double latitude, double longitude);
    void setCornerB(double latitude, double longitude);
    void setCornerC(double latitude, double longitude);
    void setCornerD(double latitude, double longitude);

    double getCircumference() override;

    // check if position is inside using monte carlo method
    bool isInside(Position position) override;

    // check if exact coordinate is inside venue
    // being on the border counts as inside
    bool isInside(double latitude, double longitude);

    // get all coordinates associated with venue rectangle
    [[nodiscard]] std::vector<Coordinate> getCorners() const override;
    double areaTriangle(Coordinate ca, Coordinate cb, Coordinate cc);
};


#endif //CLA_VENUERECT_H
