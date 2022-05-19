//
// Created by Petrus Söderström on 2022-05-18.
//

#ifndef CLA_TRIANGLE_H
#define CLA_TRIANGLE_H


#include <random>
#include "Point.h"

class Triangle {
public:
    Triangle(Point origin, Point adjacent, Point opposite) :
                        m_origin(origin), m_adjacent(adjacent), m_opposite(opposite) {}
    // Generates a collection of points inside the triangle
    std::vector<Point> generatePointsInside(int amount);
    // Get area of the triangle
    double area();
    // Calculate the area of the outer section between a circle and the triangle
    double circleOuterSectionArea(Point circleCenter, int radius);
private:
    double area(double x1, double y1, double x2, double y2, double x3, double y3);
    Point m_origin, m_adjacent, m_opposite;
};


#endif //CLA_TRIANGLE_H
