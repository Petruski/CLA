//
// Created by Petrus Söderström on 2022-05-24.
//

#ifndef CLA_CLA_H
#define CLA_CLA_H


#include <utility>

#include "Position.h"
#include "VenueRect.h"

class CLA {
public:
    CLA(double a_map_marker_lat, double a_map_marker_lon, double cornerA_lat, double cornerA_lon,
        double cornerB_lat, double cornerB_lon, double cornerC_lat, double cornerC_lon,
        double cornerD_lat, double cornerD_lon, int time, int no_averages, int margin, double isInsideLimit, std::string filename)
    : m_map_marker_lat(a_map_marker_lat), m_map_marker_lon(a_map_marker_lon), m_cornerA_lat(cornerA_lat),
      m_cornerA_lon(cornerA_lon), m_cornerB_lat(cornerB_lat), m_cornerB_lon(cornerB_lon),
      m_cornerC_lat(cornerC_lat), m_cornerC_lon(cornerC_lon), m_cornerD_lat(cornerD_lat), m_cornerD_lon(cornerD_lon),
      m_time(time), m_averages(no_averages), m_margin(margin), m_isInsideLimit(isInsideLimit), m_filename(std::move(filename)) {}
    void startCLA();
    static bool startShortestDistance(const Position& position, const VenueRect& venue, const std::vector<VenueRect>& dummyVenues, int cutoff);
    static void setupDummyVenues(std::vector<VenueRect>& dummyVenues);
private:
    double m_map_marker_lat;
    double m_map_marker_lon;
    double m_cornerA_lat;
    double m_cornerA_lon;
    double m_cornerB_lat;
    double m_cornerB_lon;
    double m_cornerC_lat;
    double m_cornerC_lon;
    double m_cornerD_lat;
    double m_cornerD_lon;
    int m_margin;
    int m_time;
    int m_averages;
    double m_isInsideLimit;
    std::string m_filename;
};


#endif //CLA_CLA_H
