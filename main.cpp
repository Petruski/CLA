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

int main() {

    /* ****************************************
     * TESTING COORDINATES/POSITION CLASS
     ******************************************/
    /*
    std::cout << "Testing Coordinate/Position class!" << std::endl;
    Position pos1(59.33258,18.0649,100,12, "GPS");
    Position pos2(57.70716,11.96679,100,12, "GPS");
    std::cout << "Distance should be 397400 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
    std::cout << "Distance should be 397400 and is: " << std::setprecision(10) << pos2.getDistanceTo(pos1) << std::endl;

    pos1.setLatitude(-26.4390917);
    pos1.setLongitude(133.281323);
    pos2.setLatitude(56.0);
    pos2.setLongitude(-96.0);
    std::cout << "Distance should be 14910000 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
    std::cout << "Distance should be 14910000 and is: " << std::setprecision(10) << pos2.getDistanceTo(pos1) << std::endl;

    pos1.setLatitude(-26.4390917);
    pos1.setLongitude(133.281323);
    pos2.setLatitude(56.0);
    pos2.setLongitude(-96.0);
    std::cout << "Distance should be 14910000 and is: " << std::setprecision(10) << pos1.getDistanceTo(pos2) << std::endl;
    std::cout << "Distance should be 14910000 and is: " << std::setprecision(10) << pos2.getDistanceTo(pos1) << std::endl;

    std::cout << std::endl;
    */
    /* ****************************************
     * END TEST
     ******************************************/

    /* ****************************************
     * TESTING FILE PARSER
     ******************************************/
    /*
    std::cout << "Testing FileParser class!" << std::endl;
    FileParser fileParser;
    //fileParser.setFile("positions.txt");
    std::vector<Position> positions = fileParser.getPositions();

    for (auto e: positions) {
        std::cout << std::setprecision(15) << e.getTime() << "," << e.getProvider() << "," << e.getAccuracy() << "," << e.getLatitude() << "," << e.getLongitude() << std::endl;
    }
     std::cout << std::endl;
     */
    /* ****************************************
     * END TEST
     ******************************************/

    /* ****************************************
     * TESTING VENUE
     ******************************************/
    /*
    std::cout << "Testing Venue class!" << std::endl;
    VenueRect venue3;
    venue3.setName("testrummet");
    venue3.setMapMarker(12,12);
    venue3.setCornerA(-1, -50);
    venue3.setCornerB(-1, 12);
    venue3.setCornerC(1, 12);
    venue3.setCornerD(1, -50);

    std::cout << std::setprecision(10) << "Circumference should be 14230800 and is: " << venue3.getCircumference() << std::endl;

     */
    /* ****************************************
     * END TEST
     ******************************************/

    /* ****************************************
    * TESTING IS INSIDE FUNTIONS
    ******************************************/
    /*
    std::cout << "Testing isInside functions!" << std::endl;

    for (int i = 0; i < 40; i++) {


    VenueRect venue3;
    venue3.setName("testrummet");
    venue3.setMapMarker(0,10);
    venue3.setCornerA(0, 10);
    venue3.setCornerB(10, 10);
    venue3.setCornerC(10, 0);
    venue3.setCornerD(0, 0);

    Position p1(-1, 5, 1, 1234, "GPS");
    if (venue3.isInside(p1))
        std::cout << "Position is inside" << std::endl;
    else
        std::cout << "Position is OUTSIDE" << std::endl;

    }
    */
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
//    Statistics::calcSpecificity(venueRect, 12);
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
    Point one(0, 0);
    Point two(0, 10);
    Point three(10,10);
    Triangle triangle(one, two, three);
    Point isItInside(5, 5);
    triangle.circleOuterSectionArea(isItInside, 5);
    return 0;
}
