//
// Created by dreadlopp on 2022-04-26.
//

#include <sstream>
#include <iostream>
#include "../include/FileParser.h"

std::vector<Position> FileParser::getPositions() {

    // open file
    fileStream.open(fileName, std::ifstream::in);
    if(!fileStream.is_open()) throw std::runtime_error("Error opening file");

    // vector for storing position objects read from file
    std::vector<Position> positions;

    // read lines from file
    std::string line;
    while (std::getline(fileStream, line)) {

        // replace comma with whitespace
        std::replace(line.begin(), line.end(), ',', ' ');

        // Create a stringstream of line read from file
        std::stringstream ss(line);

        double latitude;
        double longitude;
        double accuracy;
        long time;
        std::string provider;

        ss >> time >> provider >> accuracy >> latitude >> longitude;

        Position pos(latitude, longitude, accuracy, time, provider);
        positions.push_back(pos);
    }

    // close file and return vector with all positions
    fileStream.close();
    return positions;
}

void FileParser::setFilename(std::string aFilename) { fileName = aFilename; }
