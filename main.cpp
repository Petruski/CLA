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
#include "Constants.h"
#include "CLA.h"
#include "Rectangle.h"
#include "Circle.h"
#include "UtilityFunctions.h"
#include "Point.h"

int main(int argc, char *argv[]) {

    // string describing how to use cla
    std::string appName(argv[0]);
    std::string usage = "Usage: \n"
        + appName + "[latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n"
        + appName + "[filename][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n"
        + appName + "[filename][isInsideLimit][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]";

    // check arg
    std::string fileName;
    double isInsideLimit, cornerA_lat, cornerA_lon, cornerB_lat, cornerB_lon, cornerC_lat, cornerC_lon, cornerD_lat, cornerD_lon;

    if (!(argc == 9 || argc == 10 || argc == 11)) {
        std::cout << usage << std::endl;
        return -1;
    }
    if (argc == 9) {
        fileName = DEFAULT_FILENAME;;
        isInsideLimit = IS_INSIDE_LIMIT;

        try {
            cornerA_lat = utils::toDouble(argv[1]);
            cornerA_lon = utils::toDouble(argv[2]);
            cornerB_lat = utils::toDouble(argv[3]);
            cornerB_lon = utils::toDouble(argv[4]);
            cornerC_lat = utils::toDouble(argv[5]);
            cornerC_lon = utils::toDouble((argv[6]));
            cornerD_lat = utils::toDouble(argv[7]);
            cornerD_lon = utils::toDouble(argv[8]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return -1;
        }
    }
    else if (argc == 10) {
        fileName = argv[1];
        isInsideLimit = IS_INSIDE_LIMIT;

        try {
            cornerA_lat = utils::toDouble(argv[2]);
            cornerA_lon = utils::toDouble(argv[3]);
            cornerB_lat = utils::toDouble(argv[4]);
            cornerB_lon = utils::toDouble(argv[5]);
            cornerC_lat = utils::toDouble(argv[6]);
            cornerC_lon = utils::toDouble((argv[7]));
            cornerD_lat = utils::toDouble(argv[8]);
            cornerD_lon = utils::toDouble(argv[9]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return -1;
        }
    }
        // if argc == 11
    else  {

        fileName = argv[1];

        try {
            isInsideLimit = utils::toDouble(argv[2]);
            cornerA_lat = utils::toDouble(argv[3]);
            cornerA_lon = utils::toDouble(argv[4]);
            cornerB_lat = utils::toDouble(argv[5]);
            cornerB_lon = utils::toDouble(argv[6]);
            cornerC_lat = utils::toDouble(argv[7]);
            cornerC_lon = utils::toDouble((argv[8]));
            cornerD_lat = utils::toDouble(argv[9]);
            cornerD_lon = utils::toDouble(argv[10]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }

    }
    // Initialize CLA
    CLA cla(cornerA_lat, cornerA_lon, cornerB_lat, cornerB_lon, cornerC_lat,
            cornerC_lon, cornerD_lat, cornerD_lon, 10000, isInsideLimit, fileName);
    cla.startCLA();
    std::cout << "Filename is: " << fileName << std::endl;
    std::cout << "IsInsideLimit is: " << isInsideLimit << std::endl;
    std::cout << "Corner A: " << cornerA_lat << ", " << cornerA_lon << std::endl;
    std::cout << "Corner B: " << cornerB_lat << ", " << cornerB_lon << std::endl;
    std::cout << "Corner C: " << cornerC_lat << ", " << cornerC_lon << std::endl;
    std::cout << "Corner D: " << cornerD_lat << ", " << cornerD_lon << std::endl;



    /**
     * Get coordinates in geographic and cartesian plane
     */
    Coordinate aC, bC, cC, dC, marker;
//    aC.set(45, 70);
//    bC.set(45, 70.007);
//    cC.set(45.004, 70.007);
//    dC.set(45.004, 70);
//    marker.set(44.998, 69.99);
//    VenueRect venueRect(aC, bC, cC, dC);
//    double distanceGeo = aC.getDistanceTo(marker);
//    double bearingGeo = aC.getBearingTo(marker); // degrees
//
//    double height = aC.getDistanceTo(bC);
//    double width = bC.getDistanceTo(cC);
//    Rectangle rec(Point(0,0), height, width, 0);
//    double markerX = distanceGeo * std::cos(utils::toRadians(bearingGeo));
//    double markerY = distanceGeo * std::sin(utils::toRadians(bearingGeo));
//
//    std::vector<Point> recPoints = rec.getPoints();
//    for (auto p: recPoints) {
//        std::cout << "Corner: (" << p.getX() << "," << p.getY() << ")\n";
//    }
//    Point markerPoint(markerX,markerY);
//    std::cout << "Marker: (" << markerPoint.getX() << "," << markerPoint.getY() << ")\n";
    /**
     * TESTING GEOMETRIC CLASSES
     */
/*
    Point origin(2,2);
    Shape *rectangle = new Rectangle(origin, 5, 10, 45 * std::numbers::pi / 180);

    std::cout << "Origin: (" << rectangle->getOrigin().getX() << "," << rectangle->getOrigin().getY() << ")\n";
    std::cout << "Area: " << rectangle->area() << std::endl;
    std::cout << "Corners: ";
    std::vector<Point> corners = rectangle->getPoints();
    for (auto point: corners) {
        std::cout << "(" << point.getX() << "," << point.getY() << ") ";
    }

    std::vector<Point> generatedPoints = rectangle->generatePointsInside(5);
    for (auto p: generatedPoints) {
        std::cout << "Generated point: (" << p.getX() << "," << p.getY() << ")";
        if(rectangle->isInside(p)) {
            std::cout << " Gen-point is inside" << std::endl;
        } else {
            std::cout << " Gen-point is outside" << std::endl;
        }
    }

    Point circleOrigin(5,10);
    Shape *circle = new Circle(circleOrigin, 5);
    std::cout << "Circle Origin: (" << circle->getOrigin().getX() << "," << circle->getOrigin().getY() << ")\n";
    //std::cout << "Circle radius: " << circle.getRadius() << std::endl;
    std::cout << "Circle area: " << circle->area() << std::endl;
    generatedPoints = circle->generatePointsInside(5);
    for (auto p: generatedPoints) {
        std::cout << "Generated point: (" << p.getX() << "," << p.getY() << ") Distance to point: " << circle->getOrigin().distanceTo(p);
        if(circle->isInside(p)) {
            std::cout << " Gen-point is inside" << std::endl;
        } else {
            std::cout << " Gen-point is outside" << std::endl;
        }
    }

    for (int i = 0; i < 20; i++) {
        //    std::cout << "Intersection area: " << circle->intersectionArea(rectangle, NO_OF_MONTE_CARLO_SAMPLES) << std::endl;
    }

    Point triOrigin(5, 10);
    Point triAdj(7,9);
    Point triOpp(1,1);
    Shape *triangle = new Triangle(triOrigin, triAdj, triOpp);
    std::cout << "Tri Origin: (" << triangle->getOrigin().getX() << "," << triangle->getOrigin().getY() << ")\n";
    std::cout << "Tri area: " << triangle->area() << std::endl;
    generatedPoints = triangle->generatePointsInside(5);
    for (auto p: generatedPoints) {
        std::cout << "Generated point: (" << p.getX() << "," << p.getY() << ")";
        if(triangle->isInside(p)) {
            std::cout << " Gen-point is inside" << std::endl;
        } else {
            std::cout << " Gen-point is outside" << std::endl;
        }
    }

    for (int i = 0; i < 20; i++) {
        std::cout << "Intersection area: " << circle->intersectionArea_approximated(triangle, NO_OF_MONTE_CARLO_SAMPLES) << std::endl;
    }

    std::cout << std::endl;
    Point test(2,5);
    std::cout << "Test point: (" << test.getX() << "," << test.getY() << ")";
    if(triangle->isInside(test)) {
        std::cout << " Test-point is inside" << std::endl;
    } else {
        std::cout << " Test-point is outside" << std::endl;
    }
*/

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
//    VenueRect venueRect(limit, monteCarloValues);
//    venueRect.setCornerA(cornerA_lat, cornerA_lon);
//    venueRect.setCornerB(cornerB_lat, cornerB_lon);
//    venueRect.setCornerC(cornerC_lat, cornerC_lon);
//    venueRect.setCornerD(cornerD_lat, cornerD_lon);
//    for (auto e: positions) {
//        std::cout << std::setprecision(15) << e.getTime() << "," << e.getProvider() << "," << e.getAccuracy() << "," << e.getLatitude() << "," << e.getLongitude();
//        if (venueRect.isInside(e.getLatitude(), e.getLongitude()))
//            std::cout << " coordinate is INSIDE";
//        else
//            std::cout << " coordinate is OUTSIDE";
//        if (venueRect.isInside(e))
//            std::cout << " position is INSIDE";
//        else
//            std::cout << " position is OUTSIDE";
//        std::cout << std::endl;
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



