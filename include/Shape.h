//
// Created by dreadlopp on 2022-05-29.
//

#ifndef CLA_SHAPE_H
#define CLA_SHAPE_H


#include <vector>
#include "Point.h"

class Shape {
public:
    virtual bool isInside(Point point) = 0;
    virtual double area() = 0;
    Point getOrigin() { return m_origin; }
    virtual std::vector<Point> generatePointsInside(int amount) = 0;
    double intersectionArea(Shape *shape, int samples);
    virtual std::vector<Point> getPoints();

protected:
    Point m_origin;

};


#endif //CLA_SHAPE_H
