/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class represents a coordinate on earth written in decimal degrees with m_accuracy, m_time of GNSS reading and m_provider.
 */

#ifndef CLA_POSITION_H
#define CLA_POSITION_H

#include <string>
#include <utility>
#include "Coordinate.h"

class Position: public Coordinate {
private:
    double m_accuracy; /// m_accuracy radius of GNSS position in meters
    long m_time; /// timestamp of the GNSS position reading
    std::string m_provider; /// GNSS m_provider
public:
    Position(): m_accuracy(0), m_time(0) {}
    Position(double accuracy, long time, std::string provider): m_accuracy(accuracy), m_time(time), m_provider(std::move(provider)) {}

    // getters and setters
    [[nodiscard]] double getAccuracy() const;
    void setAccuracy(double aAccuracy);
    [[nodiscard]] long getTime() const;
    void setTime(long aTime);
    [[nodiscard]] const std::string &getProvider() const;
    void setProvider(const std::string &provider);

    // check if coordinate is inside position perimeter where position coordinate is center
    // and position m_accuracy is radius, thus drawing a circle around the position which counts as perimeter
    // a coordinate on the perimeter counts as inside
   // bool isInside(Coordinate p);
   // bool isInside(double latitude, double longitude);
};


#endif //CLA_POSITION_H
