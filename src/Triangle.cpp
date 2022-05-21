//
// Created by Petrus Söderström on 2022-05-18.
//

#include <cfloat>
#include "Triangle.h"
#include "Vector.h"

std::vector<Point> Triangle::generatePointsInside(int amount) {
    std::vector<Point> points;
    // Create a random device and generator
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(0, 1);
    // Generate a random point according to uniform distribution inside a quadrilateral
    // Where x = a1v1 + a2v2 where A1, A2 [0,1] and v1, v2 are two of the vertices of the triangle.
    while (points.size() < amount) {
        double x = dis(gen) * m_adjacent.getX() + dis(gen) * m_opposite.getX();
        double y = dis(gen) * m_adjacent.getY() + dis(gen) * m_opposite.getY();
        // Check if the point is inside the interior of the triangle by creating three triangles from this point
        // Compare the area of those triangles to the original triangle. If they equal, it is inside.
        double original_area = area(m_origin.getX(), m_origin.getY(), m_opposite.getX(), m_opposite.getY(), m_adjacent.getX(), m_adjacent.getY());
        double area_one = area(x, y, m_opposite.getX(), m_opposite.getY(), m_adjacent.getX(), m_adjacent.getY());
        double area_two = area(m_origin.getX(), m_origin.getY(), x, y, m_adjacent.getX(), m_adjacent.getY());
        double area_three = area(m_origin.getX(), m_origin.getY(), m_opposite.getX(), m_opposite.getY(), x, y);
        if (area_one + area_two + area_three == original_area) {
            points.emplace_back(x, y);
        }
    }
    return points;
}

double Triangle::area(double x1, double y1, double x2, double y2, double x3, double y3) {
    return std::abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2)) / 2.0);
}

double Triangle::area() {
    return std::abs((m_origin.getX() * (m_adjacent.getY() - m_opposite.getY()) +
                          m_adjacent.getX() * (m_opposite.getY() - m_origin.getY()) +
                          m_opposite.getX() * (m_origin.getY() - m_adjacent.getY())) / 2);
}

double Triangle::circleOuterSectionArea(Point circleCenter, int radius) {
    // Determine for each vertex of the triangle if it is inside the circle
    bool origin_vertex, opposite_vertex, adjacent_vertex = false;
    if (std::pow(m_origin.getX() - circleCenter.getX(), 2) + std::pow((m_origin.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        origin_vertex = true;
    if (std::pow(m_opposite.getX() - circleCenter.getX(), 2) + std::pow((m_opposite.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        opposite_vertex = true;
    if (std::pow(m_adjacent.getX() - circleCenter.getX(), 2) + std::pow((m_adjacent.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        adjacent_vertex = true;
    /**
     * Determine the bounds of the intersections.
     */
    double min_x, min_y = DBL_MAX;
    double max_x, max_y = -DBL_MAX;
    for (Point p : vertices) {
        if (p.getX() < min_x) {
            min_x = p.getX();
        }
        if (p.getY() < min_y) {
            min_y = p.getY();
        }
        if (p.getX() > max_x) {
            max_x = p.getX();
        }
        if (p.getY() > max_y) {
            max_y = p.getY();
        }
    }
    /**
    * Calculate the slopes of each edge, then solve for the intersections using the circleLineIntersectionQuadratic formula
    * The equation of the line will be in the slope-intercept form y = mx + b
    */
    double origin_to_opposite_slope = (m_origin.getY() - m_opposite.getY()) / (m_origin.getX() - m_opposite.getX());
    double origin_to_adjacent_slope = (m_origin.getY() - m_adjacent.getY() / (m_origin.getX() - m_adjacent.getX()));
    double opposite_to_adjacent_slope = ((m_opposite.getY() - m_adjacent.getY()) / (m_opposite.getX() - m_adjacent.getX()));
    double origin_to_opposite_y_intercept = m_origin.getY() - (origin_to_opposite_slope * m_origin.getX());
    double origin_to_adjacent_y_intercept = m_origin.getY() - (origin_to_adjacent_slope * m_origin.getX());
    double opposite_to_adjacent_y_intercept = m_opposite.getY() - (opposite_to_adjacent_slope * m_opposite.getX());

    /**
    * Define the equation of the circle where x^2 + y^2 = a^2 where a is the radius
    * Solve the circleLineIntersectionQuadratic equation for each of the triangle edges
    */
    double origin_to_opposite_addition_x = circleLineIntersectionQuadratic(origin_to_opposite_slope,
                                                                           origin_to_opposite_y_intercept, radius,
                                                                           circleCenter, true);
    double origin_to_opposite_subtraction_x = circleLineIntersectionQuadratic(origin_to_opposite_slope,
                                                                              origin_to_opposite_y_intercept, radius,
                                                                              circleCenter, false);
    double origin_to_adjacent_addition_x = circleLineIntersectionQuadratic(origin_to_adjacent_slope,
                                                                           origin_to_adjacent_y_intercept, radius,
                                                                           circleCenter, true);
    double origin_to_adjacent_subtraction_x = circleLineIntersectionQuadratic(origin_to_adjacent_slope,
                                                                              origin_to_adjacent_y_intercept, radius,
                                                                              circleCenter, false);
    double opposite_to_adjacent_addition_x = circleLineIntersectionQuadratic(opposite_to_adjacent_slope,
                                                                             opposite_to_adjacent_y_intercept, radius,
                                                                             circleCenter, true);
    double opposite_to_adjacent_subtraction_x = circleLineIntersectionQuadratic(opposite_to_adjacent_slope,
                                                                                opposite_to_adjacent_y_intercept,
                                                                                radius, circleCenter, false);
    /**
     * Add all points of interception between each edge and the circle
     */
    std::vector<Point> interceptPoints;
    addIntersectionPoint(interceptPoints, origin_to_opposite_slope, origin_to_opposite_y_intercept,
                         origin_to_opposite_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, origin_to_opposite_slope, origin_to_opposite_y_intercept,
                         origin_to_opposite_subtraction_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, origin_to_adjacent_slope, origin_to_adjacent_y_intercept,
                         origin_to_adjacent_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, origin_to_adjacent_slope, origin_to_adjacent_y_intercept,
                         origin_to_adjacent_subtraction_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, opposite_to_adjacent_slope, opposite_to_adjacent_y_intercept,
                         opposite_to_adjacent_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, opposite_to_adjacent_slope, opposite_to_adjacent_y_intercept,
                         opposite_to_adjacent_subtraction_x, min_x, min_y, max_x, max_y);
    removeDuplicates(interceptPoints);
    return 0;
}

double Triangle::circleLineIntersectionQuadratic(double slope, double intercept, double radius, Point circleCenter, bool positive) {
    int flip = -1;
    if (positive) {
       flip = 1;
    }
    double a = (1 + std::pow(slope, 2));
    double b = 2 * (slope * intercept - slope * circleCenter.getY() - circleCenter.getX());
    double c = std::pow(intercept, 2) -
               std::pow(radius, 2) +
               std::pow(circleCenter.getX(), 2) -
               (2 * intercept * circleCenter.getY()) +
               std::pow(circleCenter.getY(), 2);
    if (std::pow(b, 2) < 4 * a * c) {
        return -DBL_MAX;
    }
    return (-b + (flip * std::sqrt(std::pow(b, 2) - 4 * a * c))) / (2 * a);
}

void
Triangle::addIntersectionPoint(std::vector<Point> &points, double slope, double yIntercept, double xValue, double min_x,
                               double min_y, double max_x, double max_y) {
    if (min_x <= xValue && xValue <= max_x) {
        double y = slope * xValue + yIntercept;
        if (min_y <= y && y <= max_y) {
            points.emplace_back(Point(xValue, y));
        }
    }
}

void Triangle::removeDuplicates(std::vector<Point> &points) {
    std::sort(points.begin(), points.end(), [](const Point &lhs, const Point &rhs) {
        return lhs.getX() < rhs.getX();
    });
    points.erase(std::unique(points.begin(), points.end(), [](const Point &lhs, const Point &rhs) {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
    }), points.end());
}
