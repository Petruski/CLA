cmake_minimum_required(VERSION 3.22)
project(CustomerLocationAlgorithmApp)

set(CMAKE_CXX_STANDARD 20)

add_executable(CustomerLocationAlgorithmApp main.cpp FileParser.cpp FileParser.h Coordinate.cpp Coordinate.h Position.cpp Position.h)
