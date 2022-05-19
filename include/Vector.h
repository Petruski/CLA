//
// Created by Petrus Söderström on 2022-05-19.
//

#ifndef CLA_VECTOR_H
#define CLA_VECTOR_H

#include "Point.h"

class Vector {
public:
    // Positional vector constructor
    Vector(Point a) {
        m_x = a.getX();
        m_y = a.getY();
    }
    // Directional vector constructor
    Vector(Point a, Point b) {
        // Subtract start from terminal point. A - starting point. B - terminal point
        m_x = b.getX() - a.getX();
        m_y = b.getY() - a.getY();
    }
    Vector operator+(const Vector &vector) const {
        return {Point(this->m_x + vector.m_x, this->m_y + vector.m_y)};
    }
    Vector operator-(const Vector &vector) const {
        return {Point(this->m_x - vector.m_x, this->m_y - vector.m_y)};
    }
    Vector operator-() const {
        return {Point(-this->m_x, -this->m_y)};
    }
    Vector operator*(const Vector &vector) const {
        return {Point(this->m_x * vector.m_x, this->m_y * vector.m_y)};
    }
    Vector operator*(const double scalar) const {
        return {Point(this->m_x * scalar, this->m_y * scalar)};
    }
    Vector operator/(const Vector &vector) const {
        return {Point (this->m_x / vector.m_x, this->m_y / vector.m_y)};
    }
    bool operator<(const Vector &vector) const {
        return std::sqrt(m_x * m_x + m_y * m_y) < std::sqrt(vector.m_x * vector.m_x + vector.m_y * vector.m_y);
    }
    double getX() const { return m_x; }
    double getY() const { return m_y; }
    Vector squareRoot() {
        m_x = std::sqrt(std::pow(m_x, 2));
        m_y = std::sqrt(std::pow(m_y, 2));
        return *this;
    }
private:
    double m_x;
    double m_y;
};

#endif //CLA_VECTOR_H
