//
// Created by Petrus Söderström on 2022-05-12.
//

#ifndef CLA_VERTEX_H
#define CLA_VERTEX_H

#include <cmath>
#include "Point.h"

class Vertex {
public:
    Vertex(Point pointA, Point pointB) : m_point_a(pointA), m_point_b(pointB) {}
    double distance() {
        return std::sqrt(std::pow((m_point_a.getX() - m_point_b.getX()), 2) +
                        (std::pow((m_point_a.getY() - m_point_b.getY()), 2)));
    }
private:
    Point m_point_a;
    Point m_point_b;
};

#endif //CLA_VERTEX_H
