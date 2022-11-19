//
// Created by igb on 18/11/22.
//

#include "unit_conversion.h"
#include <cmath>

unit_conversion::unit_conversion(double maxWidthMeters, double maxHeightMeters) {
    this->maxWidthMeters = maxWidthMeters;
    this->maxHeightMeters = maxHeightMeters;
}

double unit_conversion::toPixels(double meter, int maxPixels) {
    //TODO chequear bien
    int MET2PIX = maxPixels/8;
    double pixel = (maxPixels / 2.0) + (meter * MET2PIX);
    return pixel;
}

double unit_conversion::toDegrees(double radian) {
    return ((180.0/M_PI)*radian);
}

double unit_conversion::toRadians(double degree) {
    return  ((M_PI/180.0)*degree);
}