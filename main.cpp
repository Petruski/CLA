#include <iostream>
#include <iomanip>
#include "include/Position.h"
#include "include/FileParser.h"
#include "include/Venue.h"
#include "include/VenueRect.h"

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




    return 0;
}
