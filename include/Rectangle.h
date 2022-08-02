//
// Created by dreadlopp on 2022-05-28.
//

#ifndef CLA_RECTANGLE_H
#define CLA_RECTANGLE_H


#include "Shape.h"
/**
 * A rectangle drawn on a cartesian plane. The rectangle is roted around its origin point. The second point is calculated
 * using the height property in the y-plane, width is in the x-plane. The origin point is the south west corner of the
 * rectangle. The rotation is an angle in radians between the last edge of the rectangle (edge between getPoints SW and SE) and
 * the x axis. A positive rotation is counter clockwise.
 */
class Rectangle: public Shape {

public:
    Rectangle(Point origin, double height, double width, double rotation): m_height(height), m_width(width), m_rotation(rotation) { m_origin = origin; }

    bool isInside(Point point) override;
    std::vector<Point> getPoints() override;
    [[nodiscard]] double area() override { return m_height * m_width; }
    std::vector<Point> generatePointsInside(int amount) override;

private:
    double m_height, m_width, m_rotation;

    void doRotationAroundOrigin(Point &point);

};


#endif //CLA_RECTANGLE_H
