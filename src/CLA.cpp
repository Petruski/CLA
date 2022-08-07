//
// Created by Petrus Söderström on 2022-05-24.
//

#include <iostream>
#include "CLA.h"
#include "FileParser.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"
#include "Statistics.h"
#include "Rectangle.h"
#include "UtilityFunctions.h"
#include "Circle.h"

void CLA::startCLA() {
    // Create venue rectangle out of the positions
    Coordinate cornerA, cornerB, cornerC, cornerD;
    try {
        cornerA.set(m_cornerA_lat, m_cornerA_lon);
        cornerB.set(m_cornerB_lat, m_cornerB_lon);
        cornerC.set(m_cornerC_lat, m_cornerC_lon);
        cornerD.set(m_cornerD_lat, m_cornerD_lon);
    } catch(std::range_error &e) {
        std::cout << e.what() << "\nQuitting..." << std::endl;
        return;
    }
    VenueRect venueRect(cornerA, cornerB, cornerC, cornerD);

    // Initialize the file parser and data stream iterator
    FileParser fileParser(m_filename);
    std::vector<Position> positions = fileParser.getPositions();
    DataStreamIterator iterator(positions);

    // Filter the positions -- TODO determine if average or median should be used
    PositionParser::filter(iterator, m_margin);
    Position emptyPos;
    Position position;
    std::vector<Position> averagedPositions;
    while (emptyPos != (position = PositionParser::average(iterator, 60))) {
        averagedPositions.push_back(position);
    }
    // Set up variables for statistical analysis
    int positiveResults = 0;
    int negativeResults = 0;
    double specificity;
    double sensitivity;

    // cartesian projection of venue
    std::vector<Coordinate> venueCorners = venueRect.getCorners();
    double height = (venueCorners[0].getDistanceTo(venueCorners[1]) + venueCorners[2].getDistanceTo(venueCorners[3])) / 2;
    double width = (venueCorners[1].getDistanceTo(venueCorners[2]) + venueCorners[3].getDistanceTo(venueCorners[0])) / 2;
    Shape *rectangle = new Rectangle(Point(0,0), height, width, 0); // the projection

    // Categorize each position as inside or outside
    for (const Position& p : averagedPositions) {
        // cartesian projection of position
        double distance = venueCorners[0].getDistanceTo(p); // distance from sw corner
        double angle = venueCorners[0].getBearingTo(p); // bearing from sw corner in degrees
        double x = distance * std::cos(utils::toRadians(angle));
        double y = distance * std::sin(utils::toRadians(angle));
        Shape *circle = new Circle(Point(x,y), p.getAccuracy()); // the projection

        // if isInsideLimit is negative, check if each coordinate is inside venue
        if (m_isInsideLimit < 0) {
            if (rectangle->isInside(circle->getOrigin())) {
                positiveResults++;
            } else {
                negativeResults++;
            }
        } else { // check is part of the circle is inside
            if ((rectangle->intersectionArea_approximated(circle, NO_OF_MONTE_CARLO_SAMPLES) / rectangle->area()) >= m_isInsideLimit) {
                positiveResults++;
            } else {
                negativeResults++;
            }
        }
        delete circle;
    }

    delete rectangle;

    // Calculate the specificity and sensitivity for use in Bayesian analysis
    specificity = Statistics::calcSpecificity(venueRect, m_margin, 10000);
    sensitivity = Statistics::calcSensitivity(venueRect, m_margin, 10000);

    // Calculate the confidence interval for the given successes/failures and some assumed a_prior values
    double low_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getLowPrior(), negativeResults, positiveResults);
    double med_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getMedPrior(), negativeResults, positiveResults);
    double high_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getHighPrior(), negativeResults, positiveResults);

    std::cout << "Low CI: " << low_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
    std::cout << "Med CI: " << med_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
    std::cout << "High CI: " <<  high_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
}

void CLA::startShortestDistance() {
}
