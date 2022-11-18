//
// Created by igb on 18/11/22.
//

#include "unit_conversion.h"
#include <cmath>

unit_conversion::unit_conversion(double maxWidthMeters, double maxHeightMeters, double minWidthMeters,
                                 double minHeightMeters) {
    this->maxWidthMeters = maxWidthMeters;
    this->maxHeightMeters = maxHeightMeters;
    this->minHeightMeters = minHeightMeters;
    this->minWidthMeters = minWidthMeters;
}

double unit_conversion::toPixels(double meter) {
    return 0;
}

double unit_conversion::toDegrees(double radian) {
    return ((180.0/M_PI)*radian);
}

double unit_conversion::toRadians(double degree) {
    return  ((M_PI/180.0)*degree);
}
