/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a coordinate on earth written in decimal degrees with accuracy, time of GNSS reading and provider.
 */

#ifndef CLA_POSITION_H
#define CLA_POSITION_H

#include <string>
#include <utility>
#include "Coordinate.h"

class Position: public Coordinate {
private:
    double accuracy; /// accuracy radius of GNSS position in meters
    long time; /// timestamp of the GNSS position reading
    std::string provider; /// GNSS provider
public:
    Position(): accuracy(0), time(0) {}
    Position(double aAccuracy, long aTime, std::string aProvider): accuracy(aAccuracy), time(aTime), provider(std::move(aProvider)) {}

    // getters and setters
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
