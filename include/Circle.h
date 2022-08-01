//
// Created by dreadlopp on 2022-05-28.
//

#ifndef CLA_CIRCLE_H
#define CLA_CIRCLE_H


#include "Point.h"
#include "Shape.h"

class Circle: public Shape {

public:
    Circle(Point center, double radius): m_radius(radius) { m_origin = center; }

    bool isInside(Point point) override { return m_origin.distanceTo(point) < m_radius; }
    double area() override { return std::numbers::pi * m_radius * m_radius; }
    std::vector<Point> generatePointsInside(int amount) override;
    [[nodiscard]] double getRadius() const { return m_radius; }

private:
    double m_radius;
};


#endif //CLA_CIRCLE_H
