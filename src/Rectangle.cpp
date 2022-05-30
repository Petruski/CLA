//
// Created by dreadlopp on 2022-05-28.
//

#include <vector>
#include "Rectangle.h"
#include "Triangle.h"
#include "UtilityFunctions.h"

bool Rectangle::isInside(Point point) {
    // a point P is outside the bounds of a rectangle with the getPoints ABCD if the sum of the areas of the triangles
    // PAB + PBC + PCD + PDA is greater than the area of the rectangle

    // area of triangles PAB, PBC, PCD, PDA
    std::vector<Point> rc = getPoints();
    Triangle pab(point, rc[0], rc[1]);
    Triangle pbc(point, rc[1], rc[2]);
    Triangle pcd(point, rc[2], rc[3]);
    Triangle pda(point, rc[3], rc[0]);
    double trianglesArea = pab.area() + pbc.area() + pcd.area() + pda.area();

    if (utils::equal(trianglesArea, area()))
        return true;

    return false;
}

std::vector<Point> Rectangle::getPoints() {
    Point a = m_origin;
    Point b(a.getX(), a.getY() + m_height);
    Point c(b.getX() + m_width, b.getY());
    Point d(c.getX(), a.getY());

    std::vector<Point> points {a, b, c, d};

    // if we need to rotate the triangle, rotate
    if (m_rotation != 0) {
        for (auto &point: points) {
            doRotationAroundOrigin(point);
        }
    }

    return points;
}

/**
 * Generates points inside rectangle
 * @param amount
 * @return
 */
std::vector<Point> Rectangle::generatePointsInside(int amount) {

    std::vector<Point> points;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> disX(m_origin.getX(), m_origin.getX() + m_width);
    std::uniform_real_distribution<double> disY(m_origin.getY(), m_origin.getY() + m_height);

    for (int i = 0; i < amount; i++) {
        Point point(disX(gen), disY(gen));
        points.push_back(point);
    }

    // rotate if needed
    if (m_rotation != 0) {
        for (auto &point: points) {
            doRotationAroundOrigin(point);
        }
    }

    return points;
}

void Rectangle::doRotationAroundOrigin(Point &point) {

    double x = point.getX();
    double y = point.getY();
    double originX = m_origin.getX();
    double originY = m_origin.getY();
    point.setX(std::cos(m_rotation) * (x - originX) - std::sin(m_rotation) * (y - originY) + originX);
    point.setY(std::sin(m_rotation) * (x - originX) + std::cos(m_rotation) * (y - originY) + originY);

}

