//
// Created by Petrus Söderström on 2022-05-01.
//

#include "Statistics.h"
#include "PositionParser.h"
#include "Point.h"
#include "Vertex.h"
#include <cmath>
#include <vector>

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
    // Determine the distances between each corner
    double SW_NW = corners[0].getDistanceTo(corners[1]);
    double NW_NE = corners[1].getDistanceTo(corners[2]);
    double NE_SE = corners[2].getDistanceTo(corners[3]);
    double SE_SW = corners[3].getDistanceTo(corners[0]);
    // Create four edges with the above distances. SW point represents the origin
    Point sw_point(0, 0);
    Point nw_point(std::sqrt((std::pow(NW_NE, 2)) + std::pow(NE_SE, 2)), SW_NW);
    Point ne_point(NW_NE, std::sqrt((std::pow(SW_NW, 2) + std::pow(NW_NE, 2))));
    Point se_point(SE_SW, 0);
    // Create four vertices between each edge
    Vertex SW_NW_VERTEX(sw_point, nw_point);
    Vertex NW_NE_VERTEX(nw_point, ne_point);
    Vertex NE_SE_VERTEX(ne_point, se_point);
    Vertex SE_SW_VERTEX(se_point, sw_point);
    return 0;
}

double Statistics::calcSensitivity(const VenueRect& venueRect, int margin) {
    return 0;
}
