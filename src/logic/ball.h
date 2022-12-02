#ifndef ROCKET_LEAGUE_BALL_H
#define ROCKET_LEAGUE_BALL_H
#include "../../box2d/include/box2d/box2d.h"
#include "../../src/constants/logic_values.h"

class Ball {
private:

    b2Body* ballBody;
public:
    b2Body *getBallBody() const;

private:
    bool wasPunchedNormal;
    bool wasPunchedFlipShot;
    bool wasPunchedRedShot;
    bool wasPunchedPurpleShot;
    bool wasPunchedGoldShot;
    int framesAfterPunched;

public:
    explicit Ball(b2Body* ballBody);
    Ball();
    void setBody(b2Body* ball);
    void punch(int typeOfPunch);
    void resetPunch();
    void createFixture(b2FixtureDef &fixture);

    bool isAwake();

    float getData(int i);

    void verifyPunch();

    float directionForce(int key);

    void copy(Ball &ball);
};




#endif //ROCKET_LEAGUE_BALL_H
