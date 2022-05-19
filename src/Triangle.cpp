//
// Created by Petrus Söderström on 2022-05-18.
//

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
     * Calculate points of intersections for each edge - Working with Euclidean vectors.
     * The line will intersect the circle where |p + td - q| = r where p is the starting positional vector,
     * d is the directional vector from p. t is some parameter along the line p + d. q is the positional vector of the
     * center of the circle. The aim is to solve for t using a quadratic equation to solve for the intersections.
     */

    // Positional vectors
    Vector circleCenterVector(circleCenter);
    Vector originVector(m_origin);
    Vector oppositeVector(m_opposite);
    Vector adjacentVector(m_adjacent);

     // Directional vectors
    Vector originToAdjacent(m_origin, m_adjacent);
    Vector originToOpposite(m_origin, m_opposite);
    Vector adjacentToOpposite(m_adjacent, m_opposite);
    Vector circumferenceVector(circleCenter, Point(0, radius)); // Arbitrary point on the circumference

    // Calculate the radii vector expression given the radius and some arbitrary point on the circumference
    Vector radiusVector = (circumferenceVector - circleCenterVector) * (circumferenceVector - circleCenterVector);

    // Vector pairs of positional and directional vectors
    std::vector<std::tuple<Vector, Vector>> vectorTuple{std::tuple<Vector, Vector>(originVector, originToAdjacent),
                                                        std::tuple<Vector, Vector>(oppositeVector, originToOpposite),
                                                        std::tuple<Vector, Vector>(adjacentVector, adjacentToOpposite)};
    // Form a quadratic equation given these vectors and the circle centre and its radius to solve for its roots
    for (std::tuple<Vector, Vector> tuple : vectorTuple) {
        Vector a = std::get<1>(tuple) * std::get<1>(tuple);
        Vector b = ((std::get<1>(tuple) * std::get<0>(tuple)) - (std::get<1>(tuple) * circleCenter)) * 2.0;
        Vector c = (std::get<0>(tuple) * std::get<0>(tuple)) + (circleCenterVector * circleCenterVector) - (std::get<0>(tuple) * 2.0 * circleCenter) - radiusVector;
        if ((b * b) < a * c * 4.0)
            continue;
        Vector t_minus = (-b - ((b * b - a * c * 4.0).squareRoot())) / a * 2.0;
        Vector t_plus = (-b + ((b * b - a * c * 4.0).squareRoot())) / a * 2.0;
    }

    return 0;
}
