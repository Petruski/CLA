/**
 * @author Petrus Söderström
 * @author Mattias Lindell
 * @date 2022-04-26
 * @brief The class reads a csv file of GNSS positions
 */

#ifndef CLA_FILEPARSER_H
#define CLA_FILEPARSER_H

#include <fstream>
#include <utility>
#include <vector>
#include "Position.h"

class FileParser {
private:
    std::ifstream fileStream;
    std::string fileName;
public:
    FileParser() { fileName = ""; }
    explicit FileParser(std::string aFileName): fileName(std::move(aFileName)) {}

    void setFilename(std::string aFilename);
    std::vector<Position> getPositions();
};


#endif //CLA_FILEPARSER_H
