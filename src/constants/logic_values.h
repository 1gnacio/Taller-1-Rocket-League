
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

    constexpr static const float W_CAR = 1.2;
    constexpr static const float H_CAR = 0.5;

    const float ANGLE_CAR = 0;

    constexpr static const float RADIUS_BALL = 0.3f;
    const float ANGLE_BALL = 0;

    const int VELOCITY_ITERATIONS = 8;
    const int POSITION_ITERATIONS = 3;

    const int HAS_BEEN_PUNCHED_NORMAL = 6;
    const int HAS_BEEN_PUNCHED_FLIP_SHOT = 7;
    const int HAS_BEEN_PUNCHED_RED_SHOT = 8;
    const int HAS_BEEN_PUNCHED_PURPLE_SHOT = 9;
    const int HAS_BEEN_PUNCHED_GOLD_SHOT = 10;

    const int POS_X_INITIAL_CAR_LOCAL = -2;
    const int POS_Y_INITIAL_CAR_LOCAL = -2;
    const int POS_X_INITIAL_CAR_VISITOR = 2;
    const int POS_Y_INITIAL_CAR_VISITOR = -2;
    const float POS_X_INITIAL_BALL = 0.0f;
    const float POS_Y_INITIAL_BALL = -2.8f;

    const float ALTITUDE_GROUND = 2.23f;

    const int TOP_SENSOR = 1;
    const int DOWN_SENSOR = 2;
    const int HEAD_SENSOR = 3;
    const int TAIL_SENSOR = 4;

    const int NORMAL_SHOT = 0;
    const int FLIP_SHOT = 1;
    const int RED_SHOT = 2;
    const int PURPLE_SHOT = 3;
    const int GOLD_SHOT = 4;

    const int GOAL_LOCAL = 2;
    const int GOAL_VISITOR = 1;
};

#endif //LOGIC_VALUES_H
