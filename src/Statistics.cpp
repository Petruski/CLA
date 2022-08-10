//
// Created by Petrus Söderström on 2022-05-01.
//

#include "Statistics.h"
#include <iostream>
#include <utility>

double Statistics::multiBayesian(double specificity, double sensitivity, double prior, int negativeResults,
                                 int positiveResults) {
    // Numerator - Sensitivity^n * (1 - Sensitivity)^j * Prior where n == positive, j == negative
    double numerator = std::pow(sensitivity, positiveResults) *
                       std::pow((1 - sensitivity), negativeResults) * prior;
    // Denominator - Sensitivity^n * (1 - Sensitivity)^j * Prior + (1 - Specificity)^n * Specificity^j * (1 - Prior)
    double denominator = (std::pow(sensitivity, positiveResults) * std::pow((1 - sensitivity), negativeResults) * prior) +
                         (std::pow(1 - specificity, positiveResults) * std::pow(specificity, negativeResults) * (1 - prior));
    return numerator / denominator;
}

double Statistics::singleBayesian(double specificity, double sensitivity, double prior) {
    return multiBayesian(specificity, sensitivity, prior, 0, 1);
}

double Statistics::calcSensitivity(const VenueRect &venueRect, int margin) {
    // Get the triangles
    auto corners = venueRect.getCorners();
    double rotation;
    auto triangles = generateTriangles(corners, rotation);
    // Make a rectangle
    double height = (corners[0].getDistanceTo(corners[1]) + corners[2].getDistanceTo(corners[3])) / 2;
    double width = (corners[1].getDistanceTo(corners[2]) + corners[3].getDistanceTo(corners[0])) / 2;
    Shape *rectangle = new Rectangle(Point(0, 0), height, width, rotation);
    // Generate points inside the triangles
    auto left = triangles[0].generatePointsInside(NO_OF_POINT_SAMPLES);
    auto right = triangles[1].generatePointsInside(NO_OF_POINT_SAMPLES);
    std::vector<Point> points;
    for (auto point : left)
        points.push_back(point);
    for (auto point : right)
        points.push_back(point);
    double positiveTests = 0.0;
    for (auto point : points) {
        // Create a circle
        Shape *circle = new Circle(point, margin);
        // Check if it's inside using Monte Carlo simulation
        if (rectangle->intersectionArea_approximated(circle, NO_OF_MONTE_CARLO_SAMPLES) / rectangle->area() >=
            IS_INSIDE_LIMIT)
            positiveTests++;
    }
    // Return the ratio of positive results of all points that are inside. This is the True Positive Rate
    return positiveTests / points.size();
}

double Statistics::calcSensitivity(const VenueRect& venueRect, int margin, int iterations) {
    auto triangles = generateTriangles(venueRect.getCorners());
    double leftTriangleArea = triangles[0].area();
    double rightTriangleArea = triangles[1].area();
    std::vector<Point> leftTrianglePoints = triangles[0].generatePointsInside(iterations);
    std::vector<Point> rightTrianglePoint = triangles[1].generatePointsInside(iterations);
    double totalLeftTriangleArea = 0;
    double totalRightTriangleArea = 0;
    for (const Point& p : leftTrianglePoints) {
        totalLeftTriangleArea += triangles[0].circleOuterSectionArea(p, margin);
    }
    for (const Point& p : rightTrianglePoint) {
        totalRightTriangleArea += triangles[1].circleOuterSectionArea(p, margin);
    }
    // Return a weighted percentage of areas outside the triangles
    return (leftTriangleArea / (leftTriangleArea + rightTriangleArea) * (totalLeftTriangleArea / (M_PI * std::pow(margin, 2) * iterations)) +
           rightTriangleArea / (leftTriangleArea + rightTriangleArea) * (totalRightTriangleArea / (M_PI * std::pow(margin, 2) * iterations)));
}

double Statistics::calcSpecificity(const VenueRect &venueRect, int margin) {
    // Get the triangles
    double rotation;
    auto corners = venueRect.getCorners();
    auto triangles = generateTriangles(corners, rotation);
    // Make a rectangle
    double height = (corners[0].getDistanceTo(corners[1]) + corners[2].getDistanceTo(corners[3])) / 2;
    double width = (corners[1].getDistanceTo(corners[2]) + corners[3].getDistanceTo(corners[0])) / 2;
    Shape *rectangle = new Rectangle(Point(0, 0), height, width, rotation);
    // Generate points outside the triangles
    auto left = triangles[0].generatePointsOutside(NO_OF_POINT_SAMPLES, rectangle);
    auto right = triangles[1].generatePointsOutside(NO_OF_POINT_SAMPLES, rectangle);
    std::vector<Point> points;
    for (auto point : left)
        points.push_back(point);
    for (auto point : right)
        points.push_back(point);
    int falsePositives = 0;
    for (auto point : points) {
        // Create a circle
        Shape *circle = new Circle(point, margin);
        // Check if it's inside using Monte Carlo simulation
        if (rectangle->intersectionArea_approximated(circle, NO_OF_MONTE_CARLO_SAMPLES) / rectangle->area() >=
            IS_INSIDE_LIMIT)
            falsePositives++;
    }
    // Return the ratio of all the true negatives by the total number of points outside the triangles
    double trueNegatives = points.size() - falsePositives;
    return trueNegatives / points.size();
}

double Statistics::calcSpecificity(const VenueRect& venueRect, int margin, int iterations) {
    auto triangles = generateTriangles(venueRect.getCorners());
    double leftTriangleArea = triangles[0].area();
    double rightTriangleArea = triangles[1].area();
    std::vector<Point> leftTrianglePoints = triangles[0].generatePointsOutside(iterations);
    std::vector<Point> rightTrianglePoint = triangles[1].generatePointsOutside(iterations);
    double totalLeftTriangleArea = 0;
    double totalRightTriangleArea = 0;
    for (const Point& p : leftTrianglePoints) {
        totalLeftTriangleArea += triangles[0].circleOuterSectionArea(p, margin);
    }
    for (const Point& p : rightTrianglePoint) {
        totalRightTriangleArea += triangles[1].circleOuterSectionArea(p, margin);
    }
    // The total areas represent the likelihood of being placed inside, while being outside the triangle. This is the false positive rate
    // Return a weighted percentage of the areas outside the triangle.
    return (leftTriangleArea / (leftTriangleArea + rightTriangleArea) * (totalLeftTriangleArea / (M_PI * std::pow(margin, 2) * iterations)) +
            rightTriangleArea / (leftTriangleArea + rightTriangleArea) * (totalRightTriangleArea / (M_PI * std::pow(margin, 2) * iterations)));
}

std::vector<Triangle> Statistics::generateTriangles(std::vector<Coordinate> corners, double &rotation) {
    // Initialize an iterator
    DataStreamIterator<Coordinate> it(corners);
    // Order the corners SW, NW, NE, SE
    corners = PositionParser::order(it);
    // Determine the distances between the SW corner and the other corners
    double SW_NW = corners[0].getDistanceTo(corners[1]);
    double SW_NE = corners[0].getDistanceTo(corners[2]);
    double SW_SE = corners[0].getDistanceTo(corners[3]);
    // Determine the bearings between the origin (SW) and each other position
    double SW_NW_BEARING = corners[0].getBearingTo((corners[1]));
    double SW_NE_BEARING = corners[0].getBearingTo(corners[2]);
    double SW_SE_BEARING = corners[0].getBearingTo(corners[3]);
    // Assign the rotation for future rectangle calculations using the SW and NW corners
    rotation = SW_NW_BEARING;
    // Create four edges with the above distances and bearings (angles). SW point represents the origin
    Point sw_point(0, 0);
    Point nw_point(std::cos(SW_NW_BEARING) * SW_NW, std::sin(SW_NW_BEARING) * SW_NW);
    Point ne_point(std::cos(SW_NE_BEARING) * SW_NE, std::sin(SW_NE_BEARING) * SW_NE);
    Point se_point(std::cos(SW_SE_BEARING) * SW_SE, std::sin(SW_SE_BEARING) * SW_SE);
    // Decompose the polygon (assumed rectangle) into two triangles along a diagonal. Ordered as left and right triangle
    return std::vector<Triangle> {Triangle(sw_point, nw_point, se_point),
                                  Triangle(ne_point, nw_point, se_point)};
}

std::vector<Triangle> Statistics::generateTriangles(std::vector<Coordinate> corners) {
    double temp;
    return generateTriangles(std::move(corners), temp);
}
