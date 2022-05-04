//
// Created by Petrus Söderström on 2022-05-01.
//

#include "Statistics.h"
#include <cmath>

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
