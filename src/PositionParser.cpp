//
// Created by Petrus Söderström on 2022-04-30.
//

#include <iostream>
#include "PositionParser.h"

/**
 *
 * @param iterator
 * @param aFilter
 * @return Filtered stream against GNSS m_accuracy
 */
void PositionParser::filter(DataStreamIterator<Position> &iterator, double aFilter) {
    std::vector<Position> temp;
    while(iterator.hasNext()) {
        if (iterator.next().getAccuracy() > aFilter) {
            iterator.remove();
        }
    }
    iterator.reset();
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

    Position p (accuracySum / counter, lastTime, lastProvider);
    try {
        p.setLatitude(latitudeSum / counter);
        p.setLongitude(longitudeSum / counter);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
    }
    return p;
}

/**
 *
 * @param iterator
 * Guarantees SW, NW, NE, SE ordering
 */
std::vector<Coordinate> PositionParser::order(DataStreamIterator<Coordinate> &iterator) {
    std::vector<Coordinate> vector;
    while(iterator.hasNext()) {
        vector.push_back(iterator.next());
    }
    // Split into southern ([0], [1]) and northern ([2], [3])
    std::sort(vector.begin(), vector.end(), [](const Coordinate& a, const Coordinate& b) {
        return a.getLatitude() < b.getLatitude();
    });
    std::vector<Coordinate> south {vector[0], vector[1]};
    std::vector<Coordinate> north {vector[2], vector[3]};
    // Sort with a west priority
    std::sort(south.begin(), south.end(), [](const Coordinate& a, const Coordinate& b) {
        return a.getLongitude() < b.getLongitude();
    });
    std::sort(north.begin(), north.end(), [](const Coordinate& a, const Coordinate& b) {
        return a.getLongitude() < b.getLongitude();
    });
    // Return South West, North West, North East, South East
    return std::vector<Coordinate> {south[0], north[0], north[1], south[1]};
}
