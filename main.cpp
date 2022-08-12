#include <iostream>
#include "Constants.h"
#include "CLA.h"
#include "UtilityFunctions.h"

int main(int argc, char *argv[]) {

    // string describing how to use cla
    std::string appName(argv[0]);
    std::string usage = "Usage: \n"
        + appName + "[latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n"
        + appName + "[filename][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n"
        + appName + "[filename][isInsideLimit][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]"
        + appName + "[filename][isInsideLimit][timeFrame][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n"
        + appName + "[filename][isInsideLimit][timeFrame][averages][latitude_1][longitude_1][latitude_2][longitude_2][latitude_3][longitude_3][latitude_4][longitude_4]\n";

    // check arg
    std::string fileName;
    double isInsideLimit, cornerA_lat, cornerA_lon, cornerB_lat, cornerB_lon, cornerC_lat, cornerC_lon, cornerD_lat, cornerD_lon;
    int timeFrame, no_averages;

    if (!(argc == 9 || argc == 10 || argc == 11 || argc == 12 || argc == 13)) {
        std::cout << usage << std::endl;
        return -1;
    }
    if (argc == 9) {
        fileName = DEFAULT_FILENAME;
        isInsideLimit = IS_INSIDE_LIMIT;
        timeFrame = TIME_FRAME;
        no_averages = NO_AVERAGES;

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
        timeFrame = TIME_FRAME;
        no_averages = NO_AVERAGES;

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
    else if (argc == 11)  {

        fileName = argv[1];
        timeFrame = TIME_FRAME;
        no_averages = NO_AVERAGES;

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
        // If argc == 12
    else if(argc == 12) {
        fileName = argv[1];
        no_averages = NO_AVERAGES;

        try {
            isInsideLimit = utils::toDouble(argv[2]);
            timeFrame = utils::toInt(argv[3]);
            cornerA_lat = utils::toDouble(argv[4]);
            cornerA_lon = utils::toDouble(argv[5]);
            cornerB_lat = utils::toDouble(argv[6]);
            cornerB_lon = utils::toDouble(argv[7]);
            cornerC_lat = utils::toDouble(argv[8]);
            cornerC_lon = utils::toDouble((argv[9]));
            cornerD_lat = utils::toDouble(argv[10]);
            cornerD_lon = utils::toDouble(argv[11]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }
    } else {
        fileName = argv[1];

        try {
            isInsideLimit = utils::toDouble(argv[2]);
            timeFrame = utils::toInt(argv[3]);
            no_averages = utils::toInt(argv[4]);
            cornerA_lat = utils::toDouble(argv[5]);
            cornerA_lon = utils::toDouble(argv[6]);
            cornerB_lat = utils::toDouble(argv[7]);
            cornerB_lon = utils::toDouble(argv[8]);
            cornerC_lat = utils::toDouble(argv[9]);
            cornerC_lon = utils::toDouble((argv[10]));
            cornerD_lat = utils::toDouble(argv[11]);
            cornerD_lon = utils::toDouble(argv[12]);
        } catch (std::runtime_error &e) {
            std::cout << "Exception: " << e.what() << std::endl;
            std::cout << usage << std::endl;
            return 1;
        }
    }
    // Initialize CLA
    CLA cla(cornerA_lat, cornerA_lon, cornerB_lat, cornerB_lon, cornerC_lat,
            cornerC_lon, cornerD_lat, cornerD_lon, timeFrame, no_averages, 16, isInsideLimit, fileName);
    cla.startCLA();
//    std::cout << "Filename is: " << fileName << std::endl;
//    std::cout << "IsInsideLimit is: " << isInsideLimit << std::endl;
//    std::cout << "Corner A: " << cornerA_lat << ", " << cornerA_lon << std::endl;
//    std::cout << "Corner B: " << cornerB_lat << ", " << cornerB_lon << std::endl;
//    std::cout << "Corner C: " << cornerC_lat << ", " << cornerC_lon << std::endl;
//    std::cout << "Corner D: " << cornerD_lat << ", " << cornerD_lon << std::endl;

    return 0;
}



