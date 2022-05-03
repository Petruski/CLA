#include <iostream>
#include <iomanip>
#include "include/Position.h"
#include "include/FileParser.h"
#include "include/Venue.h"
#include "include/VenueRect.h"
#include "DataStreamIterator.hpp"
#include "PositionParser.h"

int main() {

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
    std::cout << "Testing FileParser class!" << std::endl;
    FileParser fileParser;
    //fileParser.setFile("positions.txt");
    std::vector<Position> positions = fileParser.getPositions();

    for (auto e: positions) {
        std::cout << std::setprecision(15) << e.getTime() << "," << e.getProvider() << "," << e.getAccuracy() << "," << e.getLatitude() << "," << e.getLongitude() << std::endl;
    }
     std::cout << std::endl;
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

    return 0;
}
