//
// Created by dreadlopp on 2022-04-26.
//

#ifndef CUSTOMERLOCATIONALGORITHMAPP_POSITION_H
#define CUSTOMERLOCATIONALGORITHMAPP_POSITION_H


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
};


#endif //CUSTOMERLOCATIONALGORITHMAPP_POSITION_H
