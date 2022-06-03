//
// Created by dreadlopp on 2022-06-01.
//
#include <iostream>
#include "catch.hpp"
#include "Coordinate.h"

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