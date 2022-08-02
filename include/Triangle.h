//
// Created by Petrus Söderström on 2022-05-18.
//

#ifndef CLA_TRIANGLE_H
#define CLA_TRIANGLE_H


#include <random>
#include "Point.h"
#include "Edge.h"
#include "Shape.h"
#include <tuple>

class Triangle: public Shape {
public:
    Triangle(Point origin, Point adjacent, Point opposite) :
                        m_adjacent(adjacent), m_opposite(opposite) {
        m_origin = origin;
        vertices.push_back(m_origin);
        vertices.push_back(m_adjacent);
        vertices.push_back(m_opposite);
    }
    // Generates a collection of points inside the triangle
    std::vector<Point> generatePointsInside(int amount) override;
    // Generates a collection of points outside the triangle by some fixed distance
    std::vector<Point> generatePointsOutside(int amount, int distance);
    // Get area of the triangle
    double area() override;
    // Calculate the area of the outer section between a circle and the triangle
    double circleOuterSectionArea(Point circleCenter, int radius);

    bool isInside(Point point) override;
    std::vector<Point> getPoints() override { return std::vector<Point> { m_origin, m_adjacent, m_opposite }; }

private:
    double area(double x1, double y1, double x2, double y2, double x3, double y3);
    double circleLineIntersectionQuadratic(double slope, double intercept, double radius, Point circleCenter, bool positive);
    void addIntersectionPoint(std::vector<std::tuple<Edge, Point>> &points, Point a, Point b, double slope, double yIntercept, double xValue, double min_x, double min_y, double max_x, double max_y);
    double calculateOuterCircleSectionArea(const std::vector<std::tuple<Edge, Point>>& intersections, Point circleCenter, double radius, const std::vector<Point>& innerVertices);
    Point m_adjacent, m_opposite;
    std::vector<Point> vertices;
};


#endif //CLA_TRIANGLE_H
