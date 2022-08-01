//
// Created by dreadlopp on 2022-05-29.
//

#include <iostream>
#include "Shape.h"

double Shape::intersectionArea_approximated(Shape *shape, int samples) {

    // Generate points inside this shape
    std::vector<Point> pointsInside = generatePointsInside(samples);

    // Check how many points that are in the other shape
    int intersectionPoints = 0;
    for (auto point: pointsInside) {
        if (shape->isInside(point)) {
            intersectionPoints++;
        }
    }

    return area() * intersectionPoints / samples;
}
