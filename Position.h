//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CLA_POSITION_H
#define CLA_POSITION_H


#include <string>
#include "Coordinate.h"

class Position: public Coordinate {
private:
    double accuracy;
    long time;
    std::string provider;
public:
    Position(double latitude, double longitude, double accuracy, long time, std::string provider);

    [[nodiscard]] double getAccuracy() const;
    void setAccuracy(double aAccuracy);
    [[nodiscard]] long getTime() const;
    void setTime(long aTime);
    [[nodiscard]] const std::string &getProvider() const;
    void setProvider(const std::string &provider);

    // check if coordinate is inside position perimeter where position coordinate is center
    // and position accuracy is radius, thus drawing a circle around the position which counts as perimeter
    // a coordinate on the perimeter counts as inside
    bool isInside(Coordinate p);
    bool isInside(double latitude, double longitude);
};


#endif //CLA_POSITION_H
