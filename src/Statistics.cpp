//
// Created by Petrus Söderström on 2022-05-01.
//

#include "Statistics.h"
#include "PositionParser.h"
#include "Point.h"
#include "Vertex.h"
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

// TODO - Check that the math checks out for some real coordinates
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
    // Create four vertices between each edge
    Vertex SW_NW_VERTEX(sw_point, nw_point);
    Vertex NW_NE_VERTEX(nw_point, ne_point);
    Vertex NE_SE_VERTEX(ne_point, se_point);
    Vertex SE_SW_VERTEX(se_point, sw_point);
    // Calculate lower and upper X/Y bounds
    double lower_x_bound, lower_y_bound = DBL_MAX;
    double upper_x_bound, upper_y_bound = -DBL_MAX;
    std::vector<Point> points{nw_point, ne_point, se_point};
    for (Point p : points) {
        if (lower_x_bound > p.getX()) {
            lower_x_bound = p.getX();
        }
        if (lower_y_bound > p.getY()) {
            lower_y_bound = p.getY();
        }
        if (upper_x_bound < p.getX()) {
            upper_x_bound = p.getX();
        }
        if (upper_y_bound < p.getY()) {
            upper_y_bound = p.getY();
        }
    }
    return 0;
}

double Statistics::calcSensitivity(const VenueRect& venueRect, int margin) {
    return 0;
}
