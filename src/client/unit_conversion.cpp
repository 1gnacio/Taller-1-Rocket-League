//
// Created by igb on 18/11/22.
//

#include "unit_conversion.h"
#include <cmath>

unit_conversion::unit_conversion(double maxWidthMeters, double maxHeightMeters) {
    this->maxWidthMeters = maxWidthMeters;
    this->maxHeightMeters = maxHeightMeters;
}

double unit_conversion::WtoPixels(double meter, int maxPixels) {
    //TODO chequear bien
    meter = maxWidthMeters + meter;
    double pixel = meter * maxPixels / (maxWidthMeters*2);
    return pixel;
}

double unit_conversion::toDegrees(double radian) {
    return ((180.0/M_PI)*radian);
}

double unit_conversion::toRadians(double degree) {
    return  ((M_PI/180.0)*degree);
}

std::string unit_conversion::timeToString(std::chrono::milliseconds ms) {
    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);
    auto hour = duration_cast<hours>(mins);
    mins -= duration_cast<minutes>(hour);
    std::string time = std::to_string(mins.count()) + ":" + std::to_string(secs.count());
    return time;
}

double unit_conversion::HtoPixels(double meter, int maxHeightPixels) {
    meter = maxHeightMeters + meter;
    double pixel = meter * maxHeightPixels / (maxHeightMeters*2);
    return pixel;
}

double unit_conversion::toPixels(double meter, int maxPixel) {
    return (meter * maxPixel)/(maxWidthMeters*2);
}
