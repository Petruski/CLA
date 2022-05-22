/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief Base class of venues
 */

#ifndef CLA_VENUE_H
#define CLA_VENUE_H


#include <string>
#include <vector>
#include "Coordinate.h"
#include "Position.h"

class Venue {
protected:
    std::string name;
    Coordinate mapMarker;

public:
    [[nodiscard]] const std::string &getName() const;
    void setName(const std::string &aName);
    [[nodiscard]] const Coordinate &getMapMarker() const;
    void setMapMarker(double latitude, double longitude);

    virtual double getCircumference() = 0;
    virtual bool isInside(Position position) = 0;
    [[nodiscard]] virtual std::vector<Coordinate> getCorners() const = 0;

    virtual  ~Venue() {}
};


#endif //CLA_VENUE_H
