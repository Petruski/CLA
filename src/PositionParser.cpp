//
// Created by Petrus Söderström on 2022-04-30.
//

#include <iostream>
#include "PositionParser.h"

/**
 *
 * @param iterator
 * @param aFilter
 * @return Filtered stream against GNSS accuracy
 */
void PositionParser::filter(DataStreamIterator<Position> &iterator, double aFilter) {
    std::vector<Position> temp;
    while(iterator.hasNext()) {
        if (iterator.next().getAccuracy() > aFilter) {
            iterator.remove();
        }
    }
}
/**
 * @param iterator
 * @param amount
 * @return Averaged Position - Naive averaging at the moment
 */
Position PositionParser::average(DataStreamIterator<Position> &iterator, int amount) {
    double latitudeSum = 0;
    double longitudeSum = 0;
    double accuracySum = 0;
    std::string lastProvider;
    long lastTime = 0;
    int counter = 0;
    for (int i = 1; i <= amount; i++) {
        if (iterator.hasNext()) {
            Position current = iterator.next();
            latitudeSum += current.getLatitude();
            longitudeSum += current.getLongitude();
            accuracySum += current.getAccuracy();
            lastProvider = current.getProvider();
            lastTime = current.getTime();
            counter++;
        }
    }
    return {latitudeSum / counter, longitudeSum / counter, accuracySum / counter, lastTime, lastProvider};
}
