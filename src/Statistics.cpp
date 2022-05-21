//
// Created by Petrus Söderström on 2022-05-01.
//

#include "Statistics.h"
#include "PositionParser.h"
#include "Point.h"
#include "Vertex.h"
#include "Triangle.h"
#include <cmath>
#include <vector>
#include <cfloat>

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

double Statistics::calcSpecificity(const VenueRect& venueRect, int margin) {
    std::vector<Coordinate> corners = venueRect.getCorners();
    DataStreamIterator<Coordinate> cornerIt (corners);
    // Order the corners SW, NW, NE, SE
    corners = PositionParser::order(cornerIt);
    // Determine the distances between the SW corner and the other corners
    double SW_NW = corners[0].getDistanceTo(corners[1]);
    double SW_NE = corners[0].getDistanceTo(corners[2]);
    double SW_SE = corners[0].getDistanceTo(corners[3]);
    // Determine the bearings between the origin (SW) and each other position
    double SW_NW_BEARING = corners[0].getBearingTo((corners[1]));
    double SW_NE_BEARING = corners[0].getBearingTo(corners[2]);
    double SW_SE_BEARING = corners[0].getBearingTo(corners[3]);
    // Create four edges with the above distances and bearings (angles). SW point represents the origin
    Point sw_point(0, 0);
    Point nw_point(std::cos(SW_NW_BEARING) * SW_NW, std::sin(SW_NW_BEARING) * SW_NW);
    Point ne_point(std::cos(SW_NE_BEARING) * SW_NE, std::sin(SW_NE_BEARING) * SW_NE);
    Point se_point(std::cos(SW_SE_BEARING) * SW_SE, std::sin(SW_SE_BEARING) * SW_SE);
    // Decompose the polygon (assumed rectangle) into two triangles along a diagonal
    Triangle leftTriangle(sw_point, nw_point, se_point);
    Triangle rightTriangle(ne_point, nw_point, se_point);
    double leftTriangleArea = leftTriangle.area();
    double rightTriangleArea = rightTriangle.area();
    std::vector<Point> leftTrianglePoints = leftTriangle.generatePointsInside(1000);
    std::vector<Point> rightTrianglePoint = rightTriangle.generatePointsInside(1000);
    return 0;
}

double Statistics::calcSensitivity(const VenueRect& venueRect, int margin) {
    return 0;
}