//
// Created by Petrus Söderström on 2022-05-09.
//

#ifndef CLA_POINT_H
#define CLA_POINT_H


#include <cmath>

class Point {
public:
    Point(double x, double y) : m_x(x), m_y(y) {}
//    Point(const Point &p) {
//        m_x = p.m_x;
//        m_y = p.m_y;
//    }
    [[nodiscard]] double getX() const { return m_x; }
    [[nodiscard]] double getY() const { return m_y; }
    double distanceTo(Point point) {
        return std::sqrt(std::pow((m_x - point.getX()), 2) +
                         (std::pow((m_y - point.getY()), 2)));
    }
//    bool operator=(const Point& point) const {
//        return this->m_x == point.m_x && this->m_y == point.m_y;
//    }
private:
    double m_x;
    double m_y;
};


#endif //CLA_POINT_H
