//
// Created by Petrus Söderström on 2022-05-18.
//

#include <cfloat>
#include "Triangle.h"
#include "UtilityFunctions.h"

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
        if(utils::equal(area_one + area_two + area_three, original_area)) {
            points.emplace_back(x, y);
        }
    }
    return points;
}

std::vector<Point> Triangle::generatePointsOutside(int amount, int distance) {
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
        // Compare the area of those triangles to the original triangle. If it is not equal it is outside
        double original_area = area(m_origin.getX(), m_origin.getY(), m_opposite.getX(), m_opposite.getY(), m_adjacent.getX(), m_adjacent.getY());
        double area_one = area(x, y, m_opposite.getX(), m_opposite.getY(), m_adjacent.getX(), m_adjacent.getY());
        double area_two = area(m_origin.getX(), m_origin.getY(), x, y, m_adjacent.getX(), m_adjacent.getY());
        double area_three = area(m_origin.getX(), m_origin.getY(), m_opposite.getX(), m_opposite.getY(), x, y);
        if(!utils::equal(area_one + area_two + area_three, original_area)) {
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
    std::vector<Point> innerVertices;
    if (std::pow(m_origin.getX() - circleCenter.getX(), 2) + std::pow((m_origin.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        innerVertices.push_back(m_origin);
    if (std::pow(m_opposite.getX() - circleCenter.getX(), 2) + std::pow((m_opposite.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        innerVertices.push_back(m_opposite);
    if (std::pow(m_adjacent.getX() - circleCenter.getX(), 2) + std::pow((m_adjacent.getY() - circleCenter.getY()), 2) <= std::pow(radius, 2))
        innerVertices.push_back(m_adjacent);
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
     * They are ordered according to their edges. Intersections on an edge come in pairs, tangent intersections on an edge are not considered.
     */
    std::vector<std::tuple<Edge, Point>> interceptPoints;
    addIntersectionPoint(interceptPoints, m_origin, m_opposite, origin_to_opposite_slope, origin_to_opposite_y_intercept,
                         origin_to_opposite_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, m_origin, m_opposite, origin_to_opposite_slope, origin_to_opposite_y_intercept,
                         origin_to_opposite_subtraction_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, m_origin, m_adjacent, origin_to_adjacent_slope, origin_to_adjacent_y_intercept,
                         origin_to_adjacent_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, m_origin, m_adjacent, origin_to_adjacent_slope, origin_to_adjacent_y_intercept,
                         origin_to_adjacent_subtraction_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, m_opposite, m_adjacent, opposite_to_adjacent_slope, opposite_to_adjacent_y_intercept,
                         opposite_to_adjacent_addition_x, min_x, min_y, max_x, max_y);
    addIntersectionPoint(interceptPoints, m_opposite, m_adjacent, opposite_to_adjacent_slope, opposite_to_adjacent_y_intercept,
                         opposite_to_adjacent_subtraction_x, min_x, min_y, max_x, max_y);
    /**
     * Calculate the area of the circle that is outside the triangle
     */
    return calculateOuterCircleSectionArea(interceptPoints, circleCenter, radius, innerVertices);
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

void Triangle::addIntersectionPoint(std::vector<std::tuple<Edge, Point>> &points, Point a, Point b,
                                    double slope, double yIntercept, double xValue, double min_x,
                                    double min_y, double max_x, double max_y) {
    if (min_x <= xValue && xValue <= max_x) {
        double y = slope * xValue + yIntercept;
        if (min_y <= y && y <= max_y) {
            points.emplace_back(std::tuple<Edge, Point>(Edge(a, b), Point(xValue, y)));
        }
    }
}

double Triangle::calculateOuterCircleSectionArea(const std::vector<std::tuple<Edge, Point>> &intersections, Point circleCenter, double radius, const std::vector<Point>& innerVertices) {
    /**
     * Nine cases that depends on amount of vertices contained within the circle and how many edges are intersected
     * Return the area outside the triangle
     */
    //  No vertices, no edges. Circle center points are assumed to be within the triangle. Completely inside.
    if (intersections.empty() && innerVertices.empty()) {
        return 0.0;
    }
    // Three vertices and three edges. The circle completely covers the triangle.
    if (innerVertices.size() == 3) {
        return M_PI * std::pow(radius, 2) - area();
    }
    // No vertices, one edge is intersected.
    if (intersections.size() == 2 && innerVertices.empty()) {
        // Calculate the circular segment that is inside the triangle - First calculate the angle between the intersections
        double c = std::sqrt(std::pow((std::get<1>(intersections[0]).getX() - std::get<1>(intersections[1]).getX()), 2) +
                             std::pow((std::get<1>(intersections[0]).getY() - std::get<1>(intersections[1]).getY()), 2));
        double theta = 2 * std::asin(c / (2 * radius));
        return std::pow(radius , 2) / 2 * (theta - std::sin(theta));
    }
    // No vertices, two edges intersected
    if (intersections.size() == 4 && innerVertices.empty()) {
        // Calculate two circular segments for the same edge intersections
        double totalArea = 0;
        if (std::get<0>(intersections[0]) == std::get<0>(intersections[1])) {
            double c = std::sqrt(std::pow((std::get<1>(intersections[0]).getX() - std::get<1>(intersections[1]).getX()), 2) +
                                 std::pow((std::get<1>(intersections[0]).getY() - std::get<1>(intersections[1]).getY()), 2));
            double theta = 2 * std::asin(c / (2 * radius));
            totalArea += (std::pow(radius, 2) / 2) * (theta - std::sin(theta));
        }
        if (std::get<0>(intersections[2]) == std::get<0>(intersections[3])) {
            double c = std::sqrt(std::pow((std::get<1>(intersections[2]).getX() - std::get<1>(intersections[3]).getX()), 2) +
                                 std::pow((std::get<1>(intersections[2]).getY() - std::get<1>(intersections[3]).getY()), 2));
            double theta = 2 * std::asin(c / (2 * radius));
            totalArea += std::pow(radius, 2) / 2 * (theta -std::sin(theta));
        }
        return totalArea;
    }
    // No vertices, three edges intersected
    if (intersections.size() == 6 && innerVertices.empty()) {
        // Calculate three circular segments for the same edge intersections
        double totalArea = 0;
        if (std::get<0>(intersections[0]) == std::get<0>(intersections[1])) {
            double c = std::sqrt(std::pow((std::get<1>(intersections[0]).getX() - std::get<1>(intersections[1]).getX()), 2) +
                                 std::pow((std::get<1>(intersections[0]).getY() - std::get<1>(intersections[1]).getY()), 2));
            double theta = 2 * std::asin(c / (2 * radius));
            totalArea += (std::pow(radius, 2) / 2) * (theta - std::sin(theta));
        }
        if (std::get<0>(intersections[2]) == std::get<0>(intersections[3])) {
            double c = std::sqrt(std::pow((std::get<1>(intersections[2]).getX() - std::get<1>(intersections[3]).getX()), 2) +
                                 std::pow((std::get<1>(intersections[2]).getY() - std::get<1>(intersections[3]).getY()), 2));
            double theta = 2 * std::asin(c / (2 * radius));
            totalArea += std::pow(radius, 2) / 2 * (theta -std::sin(theta));
        }
        if (std::get<0>(intersections[4]) == std::get<0>(intersections[5])) {
            double c = std::sqrt(std::pow((std::get<1>(intersections[4]).getX() - std::get<1>(intersections[5]).getX()), 2) +
                                 std::pow((std::get<1>(intersections[4]).getY() - std::get<1>(intersections[5]).getY()), 2));
            double theta = 2 * std::asin(c / (2 * radius));
            totalArea += std::pow(radius, 2) / 2 * (theta -std::sin(theta));
        }
        return totalArea;
    }
    // One vertex, two different edges intersected
    if (intersections.size() == 2 && innerVertices.size() == 1) {
        // Intersections in this case will occur on two different edges
        double c = std::sqrt(std::pow((std::get<1>(intersections[0]).getX() - std::get<1>(intersections[1]).getX()), 2) +
                             std::pow((std::get<1>(intersections[0]).getY() - std::get<1>(intersections[1]).getY()), 2));
        double theta = 2 * std::asin(c / (2 * radius));
        double circleSegmentArea = std::pow(radius, 2) / 2 * (theta - std::sin(theta));
        // An inner triangle will form in addition to the circle segment
        double innerTriangleArea = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                        std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                        innerVertices[0].getX(), innerVertices[0].getY());
        double totalInnerArea = circleSegmentArea + innerTriangleArea;
        // The area outside the triangle is the difference between the inner area and the total area of the circle
        return (M_PI * std::pow(radius, 2)) - totalInnerArea;
    }
    // One vertex, three different edges with four intersections
    if (intersections.size() == 4 && innerVertices.size() == 1) {
        // Two of the intersections will occur on the same edge. The other two will occur on two different edges
        // Assume that intersections are paired by same or different edges.
        double innerTriangle = 0;
        double largerSegmentArea = 0;
        double smallerSegmentArea = 0;
        for (int i = 0; i < 3; i++) {
            // Two separate edges
            if (std::get<0>(intersections[i]) != std::get<0>(intersections[i + 1]) && i != 1) {
                // Calculate the inner triangle
                innerTriangle = area(std::get<1>(intersections[i]).getX(), std::get<1>(intersections[i]).getY(),
                                     std::get<1>(intersections[i + 1]).getX(), std::get<1>(intersections[i + 1]).getY(),
                                     innerVertices[0].getX(), innerVertices[0].getY());
                // Calculate the larger circular segment
                double c = std::sqrt(std::pow((std::get<1>(intersections[i]).getX() - std::get<1>(intersections[i + 1]).getX()), 2) +
                                     std::pow((std::get<1>(intersections[i]).getY() - std::get<1>(intersections[i + 1]).getY()), 2));
                double theta = 2 * std::asin(c / (2 * radius));
                largerSegmentArea = std::pow(radius, 2) / 2 * (theta - std::sin(theta));
            } else {
                // Two intersections on the same edge - Calculate the smaller circular segment
                double c = std::sqrt(std::pow((std::get<1>(intersections[i]).getX() - std::get<1>(intersections[i + 1]).getX()), 2) +
                                     std::pow((std::get<1>(intersections[i]).getY() - std::get<1>(intersections[i + 1]).getY()), 2));
                double theta = 2 * std::asin(c / (2 * radius));
                smallerSegmentArea = std::pow(radius, 2) / 2 * (theta - std::sin(theta));
            }
        }
        // The area inside the triangle is the sum of the smaller inner triangle and the difference between the large and small circular segments
        double totalInnerArea = innerTriangle + largerSegmentArea - smallerSegmentArea;
        // Return the area outside the triangle
        return (M_PI * std::pow(radius, 2)) - totalInnerArea;
    }
    // Two vertices, three edges with two intersections on two different edges
    if (intersections.size() == 2 && innerVertices.size() == 2) {
        /**
         * Two inner smaller triangles along with a circular segment can be created from this scenario
         * Check which inner vertex is on which edge
         */
        double firstInnerTriangle = 0;
        double secondInnerTriangle = 0;
        // The first intersection is on the same edge as the first inner vertex
        if (std::get<0>(intersections[0]).getA() == innerVertices[0] || std::get<0>(intersections[0]).getB() == innerVertices[0]) {
            firstInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                      innerVertices[0].getX(), innerVertices[0].getY(),
                                      innerVertices[1].getX(), innerVertices[1].getY());
            secondInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                       std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                       innerVertices[1].getX(), innerVertices[1].getY());

        // The second intersection is on the same edge as the first inner vertex
        } else if (std::get<0>(intersections[1]).getA() == innerVertices[0] || std::get<0>(intersections[1]).getB() == innerVertices[0]) {
            firstInnerTriangle = area(std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                      innerVertices[0].getX(), innerVertices[0].getY(),
                                      innerVertices[1].getX(), innerVertices[1].getY());
            secondInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                       std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                       innerVertices[1].getX(), innerVertices[1].getY());

        // The first intersection is on the same edge as the second inner vertex
        } else if (std::get<0>(intersections[0]).getA() == innerVertices[1] || std::get<0>(intersections[0]).getB() == innerVertices[0]) {
            firstInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                      innerVertices[0].getX(), innerVertices[0].getY(),
                                      innerVertices[1].getX(), innerVertices[1].getY());
            secondInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                       std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                       innerVertices[0].getX(), innerVertices[0].getY());
        // The second intersection is on the same edge as the second inner vertex
        } else if (std::get<0>(intersections[1]).getA() == innerVertices[1] || std::get<0>(intersections[1]).getB() == innerVertices[1]) {
            firstInnerTriangle = area(std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                      innerVertices[0].getX(), innerVertices[0].getY(),
                                      innerVertices[1].getX(), innerVertices[1].getY());
            secondInnerTriangle = area(std::get<1>(intersections[0]).getX(), std::get<1>(intersections[0]).getY(),
                                       std::get<1>(intersections[1]).getX(), std::get<1>(intersections[1]).getY(),
                                       innerVertices[0].getX(), innerVertices[0].getY());
        }
        double c = std::sqrt(std::pow((std::get<1>(intersections[0]).getX() - std::get<1>(intersections[1]).getX()), 2) +
                             std::pow((std::get<1>(intersections[0]).getY() - std::get<1>(intersections[1]).getY()), 2));
        double theta = 2 * std::asin(c / (2 * radius));
        double segmentArea = std::pow(radius, 2) / 2 * (theta - std::sin(theta));
        // Return the difference between the sum of those areas and the circle area
        return (M_PI * std::pow(radius, 2)) - firstInnerTriangle + secondInnerTriangle + segmentArea;
    }
    // Error code
    return -1;
}

bool Triangle::isInside(Point point) {

    // area of triangles PAB, PBC, PAC
    Triangle pab(point, m_origin, m_adjacent);
    Triangle pbc(point, m_adjacent, m_opposite);
    Triangle pac(point, m_origin, m_opposite);
    double trianglesArea = pab.area() + pbc.area() + pac.area();

    if (utils::equal(trianglesArea, area()))
        return true;

    return false;
}



