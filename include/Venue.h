//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CLA_VENUE_H
#define CLA_VENUE_H


#include <string>
#include "Coordinate.h"
#include "Position.h"

class Venue {
protected:
    std::string name;
    Coordinate mapMarker;

public:
    [[nodiscard]] const std::string &getName() const { return name; }
    void setName(const std::string &name) { Venue::name = name; }
    [[nodiscard]] const Coordinate &getMapMarker() const { return mapMarker; }
    void setMapMarker(double latitude, double longitude);

    virtual double getCircumference() = 0;
    virtual bool isInside(Position position) = 0;
    virtual std::vector<Coordinate> getCorners() const = 0;

    virtual  ~Venue() {}
};


#endif //CLA_VENUE_H
