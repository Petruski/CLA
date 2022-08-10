//
// Created by Petrus Söderström on 2022-05-12.
//

#ifndef CLA_EDGE_H
#define CLA_EDGE_H

#include <cmath>
#include "Point.h"

class Edge {
public:
    Edge(Point pointA, Point pointB) : m_point_a(pointA), m_point_b(pointB) {}
    double distance() {
        return std::sqrt(std::pow((m_point_a.getX() - m_point_b.getX()), 2) +
                        (std::pow((m_point_a.getY() - m_point_b.getY()), 2)));
    }
    bool operator==(const Edge& edge) const {
        return this->m_point_a == edge.m_point_a && this->m_point_b == edge.m_point_b;
    }
    [[nodiscard]] Point getA() const { return m_point_a; }
    [[nodiscard]] Point getB() const { return m_point_b; }
    [[nodiscard]] bool containsPoint(Point point) const { return point == m_point_a || point == m_point_b; }
private:
    Point m_point_a;
    Point m_point_b;
};

#endif //CLA_EDGE_H
