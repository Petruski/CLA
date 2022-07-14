//
// Created by dreadlopp on 2022-06-01.
//
#include <iostream>
#include "catch.hpp"
#include "Coordinate.h"
#include "Position.h"
#include "Venue.h"
#include "VenueRect.h"
#include "Circle.h"

SCENARIO("Testing Coordinate Class") {
    GIVEN("Coordinate object") {
        Coordinate c;

        WHEN("Object is constructed") {
            THEN("coordinates should be 0") {
                REQUIRE(c.getLatitude() == 0.0);
                REQUIRE(c.getLongitude() == 0.0);
            }
        }AND_WHEN("Coordinates are set to a value") {
            double latitude = 70;
            double longitude = -140;
            c.set(latitude, longitude);

            THEN("coordinates should have this very value") {
                REQUIRE(c.getLatitude() == latitude);
                REQUIRE(c.getLongitude() == longitude);
            }

        }AND_WHEN("Coordinates are set to positive edge values") {
            double latitude = 90;
            double longitude = 180;
            c.set(latitude, longitude);

            THEN("coordinates should have this very value") {
                REQUIRE(c.getLatitude() == latitude);
                REQUIRE(c.getLongitude() == longitude);
            }
        }AND_WHEN("Coordinates are set to negative edge values") {
            double latitude = -90;
            double longitude = -180;
            c.set(latitude, longitude);

            THEN("coordinates should have this very value") {
                REQUIRE(c.getLatitude() == latitude);
                REQUIRE(c.getLongitude() == longitude);
            }
        }

        AND_WHEN("Coordinates are set to values out of range") {

            THEN("an exception should be thrown") {
                REQUIRE_THROWS_AS(c.setLatitude(1000), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLatitude(-1000), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLongitude(1000), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLongitude(-1000), std::out_of_range);
                REQUIRE_THROWS_AS(c.set(500, 500), std::out_of_range);
                REQUIRE_THROWS_AS(c.set(-500, -500), std::out_of_range);
            }
        }

        AND_WHEN("Coordinates are set to edge values out of range") {

            THEN("an out_of_range exception should be thrown") {
                REQUIRE_THROWS_AS(c.setLatitude(90.001), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLongitude(180.001), std::out_of_range);
                REQUIRE_THROWS_AS(c.set(90.001, 180.001), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLatitude(-90.001), std::out_of_range);
                REQUIRE_THROWS_AS(c.setLongitude(-180.001), std::out_of_range);
                REQUIRE_THROWS_AS(c.set(-90.001, -180.001), std::out_of_range);
            }
        }
    }GIVEN("Two coordinates") {
        Coordinate c1, c2;
        WHEN("setting them up with certain coordinates") {
            THEN("bearing should have correct value") {
                c1.set(47.76234, 173.1234);
                c2.set(-10, -179.19);
                REQUIRE(c1.getBearingTo(c2) == Approx(171.08048555874961));
            }
        }
    }GIVEN("A coordinate") {
        Coordinate c1;
        WHEN("Adding latitudes and longitudes to coordinate") {
            THEN("coordinates should still be in range") {
                c1.set(90, 180);
                c1.add(10, 10);
                REQUIRE(c1.getLatitude() == 80);
                REQUIRE(c1.getLongitude() == -170);
                c1.add(-70, -180);
                REQUIRE(c1.getLatitude() == 10);
                REQUIRE(c1.getLongitude() == 10);
                c1.add(-20.1, +180.1);
                REQUIRE(c1.getLatitude() == Approx(-10.1));
                REQUIRE(c1.getLongitude() == Approx(-169.9));
                c1.add(-80, -180);
                REQUIRE(c1.getLatitude() == Approx(-89.9));
                REQUIRE(c1.getLongitude() == Approx(10.1));

            }
        }
    }GIVEN("A a coordinate with a latitude") {
        Coordinate c;

        WHEN("calculating radius") {
            THEN ("radius is in correct interval") {
                c.setLatitude(0);
                REQUIRE(c.getEarthRadius() == 6378137.0);
                c.setLatitude(90);
                REQUIRE(c.getEarthRadius() == 6356752.0);
                c.setLatitude(-90);
                REQUIRE(c.getEarthRadius() == 6356752.0);

                for (int i = -90; i < 90; i++) {
                    c.setLatitude(i);
                    REQUIRE(c.getEarthRadius() <= 6378137.0);
                    REQUIRE(c.getEarthRadius() >= 6356752.0);
                }
            }
        }
    }
}

SCENARIO("Testing position class") {
    GIVEN("A position") {
        Position p;
        WHEN(" using the default constructor") {
            THEN("Time and accuracy should be 0") {
                REQUIRE(p.getTime() == 0);
                REQUIRE(p.getAccuracy() == 0);
            }
        } WHEN("the setters are used") {
            int time = 1233564;
            double accuracy = 12.3;
            std::string provider = "satelliteX";
            p.setTime(time);
            p.setAccuracy(accuracy);
            p.setProvider(provider);
            THEN("the getters should return the same values") {
                REQUIRE(p.getTime() == time);
                REQUIRE(p.getAccuracy() == accuracy);
                REQUIRE(p.getProvider() == provider);

            }
        }
    }
    GIVEN ("A position with parameters") {
        WHEN("Data members are set using the parameters") {
            int time = 12564;
            double accuracy = 1.32;
            std::string provider = "satelliteY";
            Position p(accuracy, time, provider);
            THEN("The getters should return the correct value") {
                REQUIRE(p.getTime() == time);
                REQUIRE(p.getAccuracy() == accuracy);
                REQUIRE(p.getProvider() == provider);
            }
        }
    }
}

SCENARIO("Testing VenueRect class") {
    GIVEN("A venue") {
        Coordinate a,b,c,d;
        a.set(0,0);
        b.set(1,0);
        c.set(1,1);
        d.set(0,1);
        VenueRect v1(a, b, c, d);
        VenueRect v2(b, c, d, a);
        VenueRect v3(d, c, b, a);
        VenueRect v4(d, a, d, a);
        WHEN("The data members are set using the setters") {
            std::string name = "shop";
            double marker_lat = 0.5;
            double marker_lon = 0.5;
            Coordinate marker;
            marker.set(marker_lat, marker_lon);
            v1.setName(name);
            v1.setMapMarker(marker_lat, marker_lon);
            THEN("The getters should return the same value") {
                REQUIRE(v1.getName() == name);
                REQUIRE(v1.getMapMarker() == marker);
            }
        }AND_WHEN("Returning the corners") {
            std::vector<Coordinate> c1 = v1.getCorners();
            std::vector<Coordinate> c2 = v2.getCorners();
            std::vector<Coordinate> c3 = v3.getCorners();
            std::vector<Coordinate> c4 = v4.getCorners();
            THEN("The corners should be returned sorted") {
                REQUIRE(c1[0] == a);
                REQUIRE(c1[1] == b);
                REQUIRE(c1[2] == c);
                REQUIRE(c1[3] == d);
                REQUIRE(c2[0] == a);
                REQUIRE(c2[1] == b);
                REQUIRE(c2[2] == c);
                REQUIRE(c2[3] == d);
                REQUIRE(c3[0] == a);
                REQUIRE(c3[1] == b);
                REQUIRE(c3[2] == c);
                REQUIRE(c3[3] == d);
                REQUIRE(c4[0] == a);
                REQUIRE(c4[1] == a);
                REQUIRE(c4[2] == d);
                REQUIRE(c4[3] == d);;
            }
        }
    }
}

SCENARIO("Testing Circle class") {
    GIVEN("A Circle with data being set through the constructor") {
        Circle c(Point(5, 7), 12);
        THEN("the radius should be correct") {
            REQUIRE(c.getRadius() == 12);
        }
        THEN("the area should be correct") {
            REQUIRE(c.area() == std::numbers::pi * 12 * 12);
        }
        THEN("The returned origin should be correct") {
            REQUIRE(c.getOrigin() == Point(5,7));
        }
        THEN("the returned points should be a vector with one element, the origin point") {
            std::vector<Point> points = c.getPoints();
            REQUIRE(points.size() == 1);
            REQUIRE(points[0] == Point(5,7));
        }
        WHEN("Generating points inside") {
            std::vector<Point> points = c.generatePointsInside(100);
            THEN("the correct amount of points should be generated") {
                REQUIRE(points.size() == 100);
            }
            THEN("all points should be inside") {
                for (auto point: points) {
                    REQUIRE(c.isInside(point));
                }
            }
        }AND_WHEN("given some points inside the circle, ") {
            Point p1(0, 0);
            Point p2(5, 7);
            Point p3(5, 18.9);
            Point p4(-6.9, 7);
            THEN("The points should be reported as inside") {
                REQUIRE(c.isInside(p1));
                REQUIRE(c.isInside(p2));
                REQUIRE(c.isInside(p3));
                REQUIRE(c.isInside(p4));
            }
        }
        AND_WHEN("given some points outside the circle, ") {
            Point p1(17, 18);
            Point p2(5, 19);
            Point p3(-7, 7);
            THEN("The points should be reported as outside") {
                REQUIRE_FALSE(c.isInside(p1));
                REQUIRE_FALSE(c.isInside(p2));
                REQUIRE_FALSE(c.isInside(p3));
            }
        }
    }
}
/**
* @TODO make tests for:
 * CLA
 * DataStreamIterator
 * Edge
 * FileParser
 * PositionParser
 * Point
 * Rectangle
 * Statistics
 * Triangle
 * UtilityFunctions
*/