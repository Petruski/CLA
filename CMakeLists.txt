cmake_minimum_required(VERSION 3.22)
project(CLA)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
include_directories(src)
include_directories(include)

add_executable(CustomerLocationAlgorithmApp
        main.cpp
        src/FileParser.cpp
        include/FileParser.h
        src/Coordinate.cpp
        include/Coordinate.h
        src/Position.cpp
        include/Position.h
        src/Venue.cpp
        include/Venue.h
        src/VenueRect.cpp
        include/VenueRect.h
        include/DataStreamIterator.hpp
        src/PositionParser.cpp
        include/PositionParser.h include/Constants.h)
