//
// Created by Petrus Söderström on 2022-05-01.
//

#ifndef CLA_STATISTICS_H
#define CLA_STATISTICS_H

#include "VenueRect.h"
#include "Triangle.h"
#include "PositionParser.h"
#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include <cmath>
#include <vector>

/** TO-DO CLEANUP DOCUMENTATION
 * Statistics class
 * Will handle Bayesian analysis and multiple testing
 * Sensitivity - Probability that GNSS measurements place you inside given you are inside
 * Defined by P(T+|D) = [P(T+)P(D|T+)]/P(D).
 * Specificity - Probability that GNSS measurements place you outside given you are outside
 * Defined by P(T-|~D) = [P(T-)P(~D|T-)/P(~D)
 * A prior - Probability of being inside. Assumed values used as this represents intent.
 * Defined by P(D)
 * Definitions:
 * P(T+) - Probability GNSS places you inside. Intersection check based
 * P(T-) - Probability GNSS places you outside. Defined by 1 - P(T+)
 * P(D) - Probability you are inside. A prior, assumed values.
 * P(~D) - Probability you are outside. Defined by 1 - P(D)
 * Multiple tests are done by following this:
 * [Sens^n * (1 - Sens)^x-n * Prior] / [Sens^n * (1 - Sens)^x-n * prior + (1 - spec)^n * Spec^x - n * (1 - Prior)]
 * Where n is defined as the amount of positive results from intersections checks and x is defined as the total amount of
 * checks done.
 */
class Statistics {
public:
    static double singleBayesian(double specificity, double sensitivity, double prior);
    static double multiBayesian(double specificity, double sensitivity, double prior, int negativeResults, int positiveResults);
    // P(T+|D) - How likely are you to be placed inside given you are inside
    static double calcSensitivity(const VenueRect& venueRect, int margin, double insideLimit);
    static double calcSensitivity(const VenueRect& venueRect, int margin, int iterations);
    // P(~T|~D) - How likely are you to be placed outside given you are outside
    static double calcSpecificity(const VenueRect& venueRect, int margin, double insideLimit);
    static double calcSpecificity(const VenueRect& venueRect, int margin, int iterations);
    static double getLowPrior() { return m_prior_probabilities[0]; };
    static double getMedPrior() { return m_prior_probabilities[1]; };
    static double getHighPrior() { return m_prior_probabilities[2]; };
private:
    static std::vector<Triangle> generateTriangles(std::vector<Coordinate> corners, double &rotation);
    static std::vector<Triangle> generateTriangles(std::vector<Coordinate> corners);
    // P(D) - Prior values
    constexpr static const double m_prior_probabilities[3] {0.01, 0.05, 0.1};
};


#endif //CLA_STATISTICS_H
