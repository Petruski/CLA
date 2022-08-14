//
// Created by Petrus Söderström on 2022-04-30.
//

#include <iostream>
#include <algorithm>
#include <cmath>
#include "PositionParser.h"

/**
 *
 * @param iterator
 * @param aFilter
 * @return Filtered stream against GNSS m_accuracy
 */
void PositionParser::filter(DataStreamIterator<Position> &iterator, double aFilter) {
    while(iterator.hasNext()) {
        if (iterator.next().getAccuracy() > aFilter) {
            iterator.remove();
        }
    }
    iterator.reset();
}

/**
 *
 * @param iterator
 * @param aFilter
 * @param centre point
 * @return Filtered stream against GNSS m_accuracy and distance between user and venue
 */
void PositionParser::filter(DataStreamIterator<Position> &iterator, double aFilter, Coordinate centrePoint) {
    while (iterator.hasNext()) {
        auto next = iterator.next();
        if (next.getAccuracy() > aFilter || next.getDistanceTo(centrePoint) > aFilter) {
            iterator.remove();
        }
    }
    iterator.reset();
}

/**
 * @param iterator
 * @param seconds
 * @return Averaged Position - Naive averaging at the moment
 */
Position PositionParser::average(DataStreamIterator<Position> &iterator, int seconds) {
    std::string lastProvider;
    int counter = 0;
    double latitudeSum = 0, longitudeSum = 0, lastAccuracy = 0;
    long timePeriod = 0, lastTime = 0, currentTime = 0;
    while (timePeriod < seconds) {
        if (iterator.hasNext()) {
            Position current = iterator.next();
            latitudeSum += current.getLatitude();
            longitudeSum += current.getLongitude();
            if (lastAccuracy < current.getAccuracy())
                lastAccuracy = current.getAccuracy();
            // It is milliseconds, otherwise seconds
            if (int(std::log10(current.getTime())) + 1 == 13) {
                currentTime = current.getTime() / 1000;
            } else if (int(std::log10(current.getTime()) + 1) == 10){
                currentTime = current.getTime();
            }
            if (lastTime != 0) {
                timePeriod += currentTime - (lastTime / 1000);
            }
            lastTime = current.getTime();
            lastProvider = current.getProvider();
            counter++;
        } else {
            if (timePeriod == 0) {
                Position p;
                return p;
            }
            break;
        }
    }

    Position p (lastAccuracy, lastTime, lastProvider);
    try {
        p.setLatitude(latitudeSum / counter);
        p.setLongitude(longitudeSum / counter);
    } catch (std::out_of_range &e) {
        std::cout << e.what();
    }
    return p;
}

/**
 * @param iterator
 * @param seconds
 * Retrieves the median Position from a set of coordinates. Coordinates ordered by time
 */

Position PositionParser::median(DataStreamIterator<Position> &iterator, int seconds) {
    std::vector<Position> positions;
    long timePeriod = 0, lastTime = 0, currentTime = 0;
    while (timePeriod < seconds) {
        if (iterator.hasNext()) {
            Position current = iterator.next();
            // It is milliseconds, otherwise seconds
            if (int(std::log10(current.getTime())) + 1 == 13) {
                currentTime = current.getTime() / 1000;
            } else if (int(std::log10(current.getTime()) + 1) == 10){
                currentTime = current.getTime();
            }
            if (lastTime != 0) {
                timePeriod += currentTime - (lastTime / 1000);
            }
            lastTime = current.getTime();
            if (timePeriod <= seconds) {
                positions.push_back(current);
            }
        } else {
            if (timePeriod == 0) {
                Position p;
                return p;
            }
            break;
        }
    }
    size_t n = positions.size();
    size_t middle = n / 2;
    if (n % 2 != 0) {
        return positions[middle + 1];
    } else {
        Position position(std::min(positions[middle].getAccuracy(), positions[middle + 1].getAccuracy()),
                        std::max(positions[middle].getTime(), positions[middle + 1].getTime()),
                        positions[middle + 1].getProvider());
        position.setLatitude((positions[middle].getLatitude() + positions[middle + 1].getLatitude()) / 2);
        position.setLongitude((positions[middle].getLongitude() + positions[middle + 1].getLongitude()) / 2);
        return position;
    }
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
