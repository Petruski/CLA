#include <iostream>
#include <iomanip>
#include <cmath>
#include "include/Position.h"
#include "include/FileParser.h"
#include "include/Venue.h"
#include "include/VenueRect.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"
#include "Statistics.h"
#include "Triangle.h"
=======
#include "Constants.h"

double toDouble(char *c) {
    if (isdigit(c[0])) {
        return strtod(c, nullptr);
    } else {
        throw std::runtime_error("unable to convert value to double");
    }
}

int toInt(char *c) {
    if (isdigit(c[0])) {
        return std::stoi(c, nullptr,10);
    } else {
        throw std::runtime_error("unable to convert value to int");
    }
}

int main(int argc, char *argv[]) {

    // string describing how to use cla
    std::string appName(argv[0]);
    std::string usage = "Usage: \n"
            + appName + "[cornerA][cornerB][cornerC][cornerD]\n"
            + appName + "[filename][cornerA][cornerB][cornerC][cornerD]\n"
            + appName + "[filename][limit][no_of_variables][cornerA][cornerB][cornerC][cornerD]";

    // check arg
    std::string fileName;
    int monteCarloValues;
    double limit, cornerA, cornerB, cornerC, cornerD;

    if (!(argc == 5 || argc == 6 || argc == 8)) {
        std::cout << usage << std::endl;
        return 1;
    }
    if (argc == 5) {
        fileName = DEFAULT_FILENAME;;
        limit = IS_INSIDE_LIMIT;
        monteCarloValues = NO_OF_RANDOM_MC_VARIABLES;

        try {
            cornerA = toDouble(argv[1]);
            cornerB = toDouble(argv[2]);
            cornerC = toDouble(argv[3]);
            cornerD = toDouble(argv[4]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }
    }
    else if (argc == 6) {
        fileName = argv[1];
        limit = IS_INSIDE_LIMIT;
        monteCarloValues = NO_OF_RANDOM_MC_VARIABLES;

        try {
            cornerA = toDouble(argv[2]);
            cornerB = toDouble(argv[3]);
            cornerC = toDouble(argv[4]);
            cornerD = toDouble(argv[5]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }
    }
    // if argc == 8
    else  {

        fileName = argv[1];

        try {
            limit = toDouble(argv[2]);
            monteCarloValues = toInt(argv[3]);
            cornerA = toDouble(argv[4]);
            cornerB = toDouble(argv[5]);
            cornerC = toDouble(argv[6]);
            cornerD = toDouble(argv[7]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }

    }

    std::cout << "Filename is: " << fileName << std::endl;
    std::cout << "Limit is: " << limit << std::endl;
    std::cout << "Variable count is: " << monteCarloValues << std::endl;
    std::cout << "Corner A: " << cornerA << std::endl;
    std::cout << "Corner B: " << cornerB << std::endl;
    std::cout << "Corner C: " << cornerC << std::endl;
    std::cout << "Corner D: " << cornerD << std::endl;


    /* ****************************************
     * TESTING COORDINATES/POSITION CLASS
     ******************************************/
//    std::cout << "Testing Coordinate/Position class!" << std::endl;
//    Position pos1(100,12, "GPS");
//    pos1.setLatitude(59.33258);
//    pos1.setLongitude(18.0649);
//    Position pos2(100,12, "GPS");
//    pos2.setLatitude(57.70716);
//    pos2.setLongitude(11.96679);
//    std::cout << "Distance should be 397400 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
//    std::cout << "Euc Distance should be 6.3110170138021 and is: " << std::setprecision(10) << pos2.getEucDistanceTo(pos1) << std::endl;
//
//    pos1.setLatitude(-26.4390917);
//    pos1.setLongitude(133.281323);
//    pos2.setLatitude(56.0);
//    pos2.setLongitude(-96.0);
//    std::cout << "Distance should be 14910000 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
//    std::cout << "Euc Distance should be 154.54312135113 and is: " << std::setprecision(10) << pos2.getEucDistanceTo(pos1) << std::endl;
//
//    pos1.setLatitude(-90);
//    pos1.setLongitude(-180);
//    pos2.setLatitude(-90);
//    pos2.setLongitude(180);
//    std::cout << "Distance should be 0 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
//    std::cout << "Euc Distance should be 0 and is: " << std::setprecision(10) << pos2.getEucDistanceTo(pos1) << std::endl;
//
//    pos1.setLatitude(-90);
//    pos1.setLongitude(-179);
//    pos2.setLatitude(90);
//    pos2.setLongitude(179);
//    std::cout << "Distance should be 20020000 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
//    std::cout << "Euc Distance should be 180.0111107682 and is: " << std::setprecision(10) << pos2.getEucDistanceTo(pos1) << std::endl;
//
//    std::cout << std::endl;
    /* ****************************************
     * END TEST
     ******************************************/

    /* ****************************************
     * TESTING FILE PARSER
     ******************************************/
//    std::cout << "Testing FileParser class!" << std::endl;
//    FileParser fileParser(fileName);
//    //fileParser.setFile("positions.txt");
//    std::vector<Position> positions = fileParser.getPositions();
//
//    for (auto e: positions) {
//        std::cout << std::setprecision(15) << e.getTime() << "," << e.getProvider() << "," << e.getAccuracy() << "," << e.getLatitude() << "," << e.getLongitude() << std::endl;
//    }
//     std::cout << std::endl;
    /* ****************************************
     * END TEST
     ******************************************/

    /* ****************************************
     * TESTING VENUE
     ******************************************/
//    std::cout << "Testing Venue class!" << std::endl;
//    VenueRect venue1;
//    venue1.setName("test venue");
//    venue1.setMapMarker(12,12);
//    venue1.setCornerA(-1, -50);
//    venue1.setCornerB(-1, 12);
//    venue1.setCornerC(1, 12);
//    venue1.setCornerD(1, -50);
//
//    std::cout << std::setprecision(10) << "Circumference should be 14230800 and is: " << venue1.getCircumference() << std::endl;
//
//    std::cout << "Testing isInside functions!" << std::endl;
//
//    for (int i = 0; i < 20; i++) {
//
//    venue1.setMapMarker(0, 10);
//    venue1.setCornerA(1, 0);
//    venue1.setCornerB(1, 1);
//    venue1.setCornerC(0, 1);
//    venue1.setCornerD(0, 0);
//
//    Position p1(0.1, 1234, "GPS");
//    p1.setLatitude(1);
//    p1.setLongitude(0.5);
//    if (venue1.isInside(p1))
//        std::cout << "Position is inside" << std::endl;
//    else
//        std::cout << "Position is OUTSIDE" << std::endl;
//
//    }

    /* ****************************************
     * END TEST
     ******************************************/

//    Position one(10, 25, 12, 10000, "First");
//    Position two(122, 25, 24, 10000, "Second");
//    Position three(12, 25, 24, 40000, "Third");
//    Position four(15, 25, 12, 210000, "Fourth");
//    std::vector<Position> cords;
//    cords.push_back(one);
//    cords.push_back(two);
//    cords.push_back(three);
//    cords.push_back(four);
//    DataStreamIterator<Position> cordStream(cords);
//    Position test = PositionParser::average(cordStream, 2);
//    std::cout << "Latitude: " << test.getLatitude() << std::endl;
//    std::cout << "Longitude: " << test.getLongitude() << std::endl;
//    std::cout << "Accuracy: " << test.getAccuracy() << std::endl;
//    std::cout << "Time: " << test.getTime() << std::endl;
//    std::cout << "Provider: " << test.getProvider() << std::endl;
//    test = PositionParser::average(cordStream, 2);
//    std::cout << "Latitude: " << test.getLatitude() << std::endl;
//    std::cout << "Longitude: " << test.getLongitude() << std::endl;
//    std::cout << "Accuracy: " << test.getAccuracy() << std::endl;
//    std::cout << "Time: " << test.getTime() << std::endl;
//    std::cout << "Provider: " << test.getProvider() << std::endl;
//    PositionParser::filter(cordStream, 12);
//    for (const Position& pos : cords) {
//        std::cout << pos.getProvider() << std::endl;
//    }
//  std::cout << Statistics::multiBayesian(0.99, 0.97, Statistics::getLowPrior(), 0, 2) << std::endl;

    // Test for realistic venue
//    VenueRect venueRect;
//    venueRect.setCornerA(64.75031671628982, 20.966330771163626);
//    venueRect.setCornerB(64.75038336195998, 20.966622461395538);
//    venueRect.setCornerC(64.75041711378174, 20.966202695682487);
//    venueRect.setCornerD(64.75048461729877, 20.966495056466663);
//    std::cout.precision(14);
//    double stat = Statistics::calcSpecificity(venueRect, 12, 1000);
//    std::cout << "SPECIFICITY: " << stat << std::endl;
//    double SE = 64.75002841754927;
//    double SW = 64.75001697609392;
//    double NW = 64.75013596699291;
//    double NE = 64.75014769443297;
//    for (Coordinate p : venueRect.getCorners()) {
//        std::cout << p.getLatitude() << ", " << p.getLongitude();
//        if (p.getLatitude() == SW)
//            std::cout << " South West" << std::endl;
//        if (p.getLatitude() == SE)
//            std::cout << " South East" << std::endl;
//        if (p.getLatitude() == NW)
//            std::cout << " North West" << std::endl;
//        if (p.getLatitude() == NE)
//            std::cout << " North East" << std::endl;
//    }
//    std::vector<Coordinate> cords = venueRect.getCorners();
//    DataStreamIterator<Coordinate> stream(cords);
//    std::vector<Coordinate> newCords = PositionParser::order(stream);
//    std::cout << std::endl;
//    for (Coordinate p : newCords) {
//        std::cout << p.getLatitude() << ", " << p.getLongitude();
//        if (p.getLatitude() == SW)
//            std::cout << " South West" << std::endl;
//        if (p.getLatitude() == SE)
//            std::cout << " South East" << std::endl;
//        if (p.getLatitude() == NW)
//            std::cout << " North West" << std::endl;
//        if (p.getLatitude() == NE)
//            std::cout << " North East" << std::endl;
//    }
    return 0;
}



