#ifndef ROCKET_LEAGUE_UNIT_CONVERSION_H
#define ROCKET_LEAGUE_UNIT_CONVERSION_H

#define MAX_WIDTH 4.0
#define MAX_HEIGHT 3.0
#include <iostream>
#include <chrono>

class unit_conversion {
private:
    double maxWidthMeters;
    double maxHeightMeters;
public:
    unit_conversion(double maxWidthMeters, double maxHeightMeters);
    ~unit_conversion() = default;
    double WtoPixels(double meter, int maxWidthPixels);
    double HtoPixels(double meter, int maxHeightPixels);
    double toPixels(double meter, int maxPixel);
    double toDegrees(double radian);
    double toRadians(double degree);
    std::string timeToString(std::chrono::milliseconds ms);

};

#endif //ROCKET_LEAGUE_UNIT_CONVERSION_H
