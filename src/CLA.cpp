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
    venueRect.setMapMarker(m_map_marker_lat, m_map_marker_lon);

    // Set up dummy venues
    std::vector<VenueRect> dummyVenues;
    setupDummyVenues(dummyVenues);

    // Initialize the file parser and data stream iterator
    FileParser fileParser(m_filename);
    std::vector<Position> positions = fileParser.getPositions();
    DataStreamIterator iterator(positions);

    // Filter the positions -- TODO determine if average or median should be used
    PositionParser::filter(iterator, m_margin, cornerA);
    Position emptyPos;
    Position position;
    std::vector<Position> averagedPositions;
    while (emptyPos != (position = PositionParser::average(iterator, m_time))) {
        averagedPositions.push_back(position);
        if (averagedPositions.size() == m_averages)
            break;
    }
    // Set up variables for statistical analysis
    int positiveResults = 0;
    int negativeResults = 0;
    int positiveShortestDistanceResults = 0;
    int negativeShortestDistanceResults = 0;
    double specificity;
    double sensitivity;

    // cartesian projection of venue
    std::vector<Coordinate> venueCorners = venueRect.getCorners();
    DataStreamIterator<Coordinate> it(venueCorners);
    PositionParser::order(it);
    // Get the degrees between SW-NW corners
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
        if (m_isInsideLimit <= 0) {
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

        // Shortest distance approach tested for each position between the three venues -- VERY STATIC AND NAIVE
        if (startShortestDistance(p, venueRect, dummyVenues, m_margin)) {
            positiveShortestDistanceResults++;
        } else {
            negativeShortestDistanceResults++;
        }
    }

    delete rectangle;

    // -- TODO -- This is extremely slow and does not actually create amazing specificity or sensitivity values.
    // -- TODO -- It actually seems like the specificity and sensitivity values will trend towards zero or one.
//    if (m_isInsideLimit <= 0) {
//        specificity = Statistics::calcSpecificity(venueRect, m_margin, NO_OF_POINT_SAMPLES);
//        sensitivity = Statistics::calcSensitivity(venueRect, m_margin, NO_OF_POINT_SAMPLES);
//    } else {
//        specificity = Statistics::calcSpecificity(venueRect, m_margin, m_isInsideLimit);
//        sensitivity = Statistics::calcSensitivity(venueRect, m_margin, m_isInsideLimit);
//    }
    // Calculate the specificity and sensitivity for use in Bayesian analysis
    specificity = Statistics::calcSpecificity(venueRect, m_margin, NO_OF_POINT_SAMPLES);
    sensitivity = Statistics::calcSensitivity(venueRect, m_margin, NO_OF_POINT_SAMPLES);

    // Calculate the confidence interval for the given successes/failures and some assumed a_prior values
    double low_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getLowPrior(), negativeResults, positiveResults);
    double med_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getMedPrior(), negativeResults, positiveResults);
    double high_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getHighPrior(), negativeResults, positiveResults);

    double low_a_prior_CI_SDA = Statistics::multiBayesian(specificity, sensitivity, Statistics::getLowPrior(), negativeShortestDistanceResults, positiveShortestDistanceResults);
    double med_a_prior_CI_SDA = Statistics::multiBayesian(specificity, sensitivity, Statistics::getMedPrior(), negativeShortestDistanceResults, positiveShortestDistanceResults);
    double high_a_prior_CI_SDA = Statistics::multiBayesian(specificity, sensitivity, Statistics::getHighPrior(), negativeShortestDistanceResults, positiveShortestDistanceResults);

//    std::cout << "Low CI: " << low_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
//    std::cout << "Med CI: " << med_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
//    std::cout << "High CI: " <<  high_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
    std::cout << low_a_prior_CI << ", " <<  med_a_prior_CI << ", " << high_a_prior_CI << ", " << low_a_prior_CI_SDA << ", "
              << med_a_prior_CI_SDA << ", " << high_a_prior_CI_SDA << ", " << positiveResults << ", " << negativeResults << ", "
              << positiveShortestDistanceResults << ", " << negativeShortestDistanceResults << ", " << specificity << ", " << sensitivity;
}

bool CLA::startShortestDistance(const Position& position, const VenueRect& venue, const std::vector<VenueRect>& dummyVenues, int cutoff) {
    // Get all distances between the venue we're interested in, and many neighbouring venues.
    // If the venue that we are interested in is the closest, then it's a positive result
    std::vector<double> distances;
    for (const auto& x : dummyVenues) {
        distances.emplace_back(x.getMapMarker().getDistanceTo(position));
    }
    distances.emplace_back(venue.getMapMarker().getDistanceTo(position));
    auto result = std::min_element(distances.begin(), distances.end());
    auto index = std::distance(distances.begin(), result);
    // Check if the distance between the Venue's map marker and the position is the shortest distance out of all possible distances
    if (utils::equal(distances[index], venue.getMapMarker().getDistanceTo(position))) {
        return true;
    }
    return false;
}

void CLA::setupDummyVenues(std::vector<VenueRect> &dummyVenues) {
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75005844153877, 20.95989377221487)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75024311573505, 20.960119142255596)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75036616140464, 20.958868001015478)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75041749531754, 20.959789173706202)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75074894625376, 20.953150311778764)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.751025009119, 20.95328789326456)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75074964221162, 20.95272692014174)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.75091006479093, 20.952868609217933)));
    dummyVenues.emplace_back(VenueRect(Coordinate(64.73155004747157, 20.975432053841548)));
}
