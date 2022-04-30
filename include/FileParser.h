//
// Created by Mattias Lindell on 2022-04-26.
//

#ifndef CLA_FILEPARSER_H
#define CLA_FILEPARSER_H


#include <fstream>
#include <vector>
#include "Position.h"

class FileParser {
private:
    const std::string DEFAULT_FILENAME = "positions.txt";
    std::ifstream fileStream;
    std::string fileName;
public:
    FileParser() { fileName = DEFAULT_FILENAME; }
    explicit FileParser(std::string aFileName): fileName(aFileName) {}

    void setFilename(std::string aFilename);
    std::vector<Position> getPositions();
};


#endif //CLA_FILEPARSER_H