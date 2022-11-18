#ifndef ROCKET_LEAGUE_UNIT_CONVERSION_H
#define ROCKET_LEAGUE_UNIT_CONVERSION_H

#define MAX_WIDTH 4
#define MAX_HEIGHT 3

class unit_conversion {
private:
    double maxWidthMeters;
    double minWidthMeters;
    double maxHeightMeters;
    double minHeightMeters;
public:
    unit_conversion(double maxWidthMeters, double maxHeightMeters, double minWidthMeters, double minHeightMeters);
    ~unit_conversion() = default;
    double toPixels(double meter);
    static double toDegrees(double radian);
    static double toRadians(double degree);

};

#endif //ROCKET_LEAGUE_UNIT_CONVERSION_H
