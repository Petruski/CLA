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
    Coordinate m_cornerSW, m_cornerNW, m_cornerNE, m_cornerSE;

public:
    VenueRect(Coordinate cornerA, Coordinate cornerB, Coordinate cornerC, Coordinate cornerD);

    // sum of all sides
    double getCircumference() override;

    // get all coordinates associated with venue rectangle
    [[nodiscard]] std::vector<Coordinate> getCorners() const override { return std::vector<Coordinate> {m_cornerSW, m_cornerNW, m_cornerNE, m_cornerSE}; }

};

#endif //CLA_VENUERECT_H
