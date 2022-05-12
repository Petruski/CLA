//
// Created by Petrus Söderström on 2022-05-09.
//

#ifndef CLA_POINT_H
#define CLA_POINT_H


class Point {
public:
    Point(double x, double y) : m_x(x), m_y(y) {}
    [[nodiscard]] double getX() const { return m_x; }
    [[nodiscard]] double getY() const { return m_y; }
private:
    double m_x;
    double m_y;
};


#endif //CLA_POINT_H
