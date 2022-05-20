/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a rectangular venue
 */

#ifndef CLA_VENUERECT_H
#define CLA_VENUERECT_H

#include "Venue.h"
#include "Constants.h"

class VenueRect: public Venue {
private:

    // data members, the corners of the venue
    Coordinate cornerA, cornerB, cornerC, cornerD;

    double limit; // limit for position to be considered as inside, 0 = always in. 0.5 = half. 1 = never in.
    int monteCarloValueCount; // number of monte carlo variables

    // calculate area of a triangle given gps coordinates. Not real area, see documentation in source file.
    static double areaTriangle(Coordinate cA, Coordinate cB, Coordinate cC);

    static void setCorner(double latitude, double longitude, Coordinate &corner);
public:
    VenueRect(): limit(IS_INSIDE_LIMIT), monteCarloValueCount(NO_OF_RANDOM_MC_VARIABLES) {}
    VenueRect(double aLimit, int mcValueCount): limit(aLimit), monteCarloValueCount(mcValueCount) {}

    // Setters
    void setCornerA(double latitude, double longitude);
    void setCornerB(double latitude, double longitude);
    void setCornerC(double latitude, double longitude);
    void setCornerD(double latitude, double longitude);

    // sum of all sides AB, BC, CD, DA
    double getCircumference() override;

    // check if position is inside using monte carlo method
    bool isInside(Position position) override;

    // check if exact coordinate is inside venue
    // being on the border counts as inside
    bool isInside(double latitude, double longitude);
};

#endif //CLA_VENUERECT_H
