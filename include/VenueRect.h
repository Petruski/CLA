/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a rectangular venue
 */

#ifndef CLA_VENUERECT_H
#define CLA_VENUERECT_H

#include "Venue.h"

class VenueRect: public Venue {
private:
    // constants
    const int NO_OF_RANDOM_MC_VARIABLES = 10000; // no of monte carlo variables, higher value means better accuracy of Monte Carlo

    // >= Determine whether a position, drawn with a circle around it using accuracy as radius, is inside the venue
    const double IS_INSIDE_LIMIT = 0.50; // [0-1] 1 means whole circle must be inside for the position to count as inside. 0.5 means half and 0 means none, etc

    // data members, the corners of the venue
    Coordinate cornerA, cornerB, cornerC, cornerD;

    // calculate area of a triangle given gps coordinates. Not real area, see documentation in source file.
    static double areaTriangle(Coordinate cA, Coordinate cB, Coordinate cC);

    static void setCorner(double latitude, double longitude, Coordinate &corner);
public:
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
