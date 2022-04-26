//
// Created by dreadlopp on 2022-04-26.
//

#include "Position.h"

Position::Position(double latitude, double longitude, double accuracy, long time, std::string provider) : Coordinate(latitude, longitude), accuracy(accuracy), time(time), provider(provider) {}

double Position::getAccuracy() const {
    return accuracy;
}

void Position::setAccuracy(double aAccuracy) {
    accuracy = aAccuracy;
}

long Position::getTime() const {
    return time;
}

void Position::setTime(long aTime) {
    time = aTime;
}

const std::string &Position::getProvider() const {
    return provider;
}

void Position::setProvider(const std::string &provider) {
    Position::provider = provider;
}
