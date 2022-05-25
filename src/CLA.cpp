//
// Created by Petrus Söderström on 2022-05-24.
//

#include <iostream>
#include "CLA.h"
#include "FileParser.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"
#include "Statistics.h"

void CLA::startCLA() {
    // Create venue rectangle out of the positions
    VenueRect venueRect(m_limit, m_monteCarloVariables);
    venueRect.setCornerA(m_cornerA_lat, m_cornerA_lon);
    venueRect.setCornerB(m_cornerB_lat, m_cornerB_lon);
    venueRect.setCornerC(m_cornerC_lat, m_cornerC_lon);
    venueRect.setCornerD(m_cornerD_lat, m_cornerD_lon);

    // Initialize the file parser and data stream iterator
    FileParser fileParser(m_filename);
    std::vector<Position> positions = fileParser.getPositions();
    DataStreamIterator iterator(positions);

    // Filter the positions -- TODO average potentially
    PositionParser::filter(iterator, m_limit);

    // Set up variables for statistical analysis
    int positiveResults = 0;
    int negativeResults = 0;
    double specificity = 0;
    double sensitivity = 0;

    // Categorize each position as inside or outside
    for (const Position& p : positions) {
        if (venueRect.isInside(p)) {
            positiveResults++;
        } else {
            negativeResults++;
        }
    }

    // Calculate the specificity and sensitivity for use in Bayesian analysis
    specificity = Statistics::calcSpecificity(venueRect, m_limit, 10000);
    sensitivity = Statistics::calcSensitivity(venueRect, m_limit, 10000);

    // Calculate the confidence interval for the given successes/failures and some assumed a_prior values
    double low_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getLowPrior(), negativeResults, positiveResults);
    double med_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getMedPrior(), negativeResults, positiveResults);
    double high_a_prior_CI = Statistics::multiBayesian(specificity, sensitivity, Statistics::getHighPrior(), negativeResults, positiveResults);

    std::cout << "CI: " << low_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
    std::cout << "CI: " << med_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
    std::cout << "CI: " <<  high_a_prior_CI << "\nPositive: " << positiveResults << "\nNegative: " << negativeResults << "\nSpecificity: " << specificity << "\nSensitivity: " << sensitivity << std::endl;
}

void CLA::startShortestDistance() {

}
