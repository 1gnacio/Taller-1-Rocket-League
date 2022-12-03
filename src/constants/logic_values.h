
#ifndef LOGIC_VALUES_H
#define LOGIC_VALUES_H


class LogicValues {
public:

    const int POS_X = 0;
    const int POS_Y = 1;
    const int ANGLE = 2;
    const int X_VELOCITY = 3;
    const int Y_VELOCITY = 4;
    const int TURBO_TANK = 5;
    const int USING_TURBO = 6;
    const int ACCELERATING = 7;
    const int LEFT_DIRECTION = 0;
    const int RIGHT_DIRECTION = 1;
    const int UP_DIRECTION = 2;
    const int DOWN_DIRECTION = 3;
    const int PUNCHED = 8;

    constexpr static const float W_CAR = 1.2;
    constexpr static const float H_CAR = 0.5;

    const float DENSITY_CAR = 1;
    const float FRICTION_CAR = 0.2f;
    const float RESTITUTION_CAR = 0.0f;
    const float ANGLE_CAR = 0;

    const float DENSITY_BALL = 0.5;
    const float FRICTION_BALL = 0.3f;
    const float RESTITUTION_BALL = 0.6f;
    constexpr static const float RADIUS_BALL = 0.2f;
    const float ANGLE_BALL = 0;

    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;

};

#endif //LOGIC_VALUES_H
