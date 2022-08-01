//
// Created by dreadlopp on 2022-05-28.
//

#include <random>
#include "Circle.h"

std::vector<Point> Circle::generatePointsInside(int amount) {
    std::vector<Point> points;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(-m_radius, m_radius);

    int addedPointsCounter = 0;

    while (addedPointsCounter < amount) {
        Point point(m_origin.getX() + dis(gen), m_origin.getY() + dis(gen));
        if (isInside(point)) {
            points.push_back(point);
            addedPointsCounter++;
        }
    }

    return points;
}
