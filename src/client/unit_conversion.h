#ifndef ROCKET_LEAGUE_UNIT_CONVERSION_H
#define ROCKET_LEAGUE_UNIT_CONVERSION_H

#define MAX_WIDTH 4.0
#define MAX_HEIGHT 3.0

class unit_conversion {
private:
    double maxWidthMeters;
    double maxHeightMeters;
public:
    unit_conversion(double maxWidthMeters, double maxHeightMeters);
    ~unit_conversion() = default;
    double toPixels(double meter, int maxWidthPixels);
    double toDegrees(double radian);
    double toRadians(double degree);

};

#endif //ROCKET_LEAGUE_UNIT_CONVERSION_H
