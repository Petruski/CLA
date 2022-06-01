cmake_minimum_required(VERSION 3.22)
project(CLA)

set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Om Debug mode
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Debug mode
    message("Debug mode")
    add_definitions(-DDEBUG)
else(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # Skriv ut meddelandet Release mode.
    message("Release mode")
endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

set(SRC_LIST
        main.cpp
        src/FileParser.cpp
        src/Coordinate.cpp
        src/Position.cpp
        src/Venue.cpp
        src/VenueRect.cpp
        include/DataStreamIterator.hpp
        src/PositionParser.cpp
        src/Statistics.cpp
        src/Triangle.cpp
        src/Rectangle.cpp
        src/Circle.cpp
        src/Shape.cpp
        src/UtilityFunctions.cpp
        src/CLA.cpp)


set(TEST_LIST
        test/main-test.cpp
        src/FileParser.cpp
        src/Coordinate.cpp
        src/Position.cpp
        src/Venue.cpp
        src/VenueRect.cpp
        include/DataStreamIterator.hpp
        src/PositionParser.cpp
        src/Statistics.cpp
        src/Triangle.cpp
        src/Rectangle.cpp
        src/Circle.cpp
        src/Shape.cpp
        src/UtilityFunctions.cpp
        src/CLA.cpp
        test/CLA-tests.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
add_executable(${PROJECT_NAME}-Test ${TEST_LIST})
