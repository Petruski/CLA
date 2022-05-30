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

    // data members, the getPoints of the venue
    Coordinate m_cornerSW, m_cornerNW, m_cornerNE, m_cornerSE;

    double limit; // limit for position to be considered as inside, 0 = always in. 0.5 = half. 1 = never in.
    int monteCarloValueCount; // number of monte carlo variables

    // calculate area of a triangle given gps coordinates. Not real area, see documentation in source file.
    static double areaTriangle(Coordinate cA, Coordinate cB, Coordinate cC);

    void setCorner(double latitude, double longitude, Coordinate &corner);

public:
    VenueRect(): limit(IS_INSIDE_LIMIT), monteCarloValueCount(NO_OF_MONTE_CARLO_SAMPLES) {}
    VenueRect(double aLimit, int mcValueCount): limit(aLimit), monteCarloValueCount(mcValueCount) {}

    // Setters
    void setCornerSW(double latitude, double longitude);
    void setCornerNW(double latitude, double longitude);
    void setCornerNE(double latitude, double longitude);
    void setCornerSE(double latitude, double longitude);
    void setCorners(Coordinate cornerA, Coordinate cornerB, Coordinate cornerC, Coordinate cornerD);
    void setCorners(double latitudeA, double longitudeA, double latitudeB, double longitudeB, double latitudeC, double longitudeC, double latitudeD, double longitudeD);

    // sum of all sides
    double getCircumference() override;

    // check if position is inside using monte carlo method
    bool isInside(Position position) override;

    // check if exact coordinate is inside venue
    // being on the border counts as inside
    bool isInside(double latitude, double longitude);

    // get all coordinates associated with venue rectangle
    [[nodiscard]] std::vector<Coordinate> getCorners() const override;


};

#endif //CLA_VENUERECT_H
