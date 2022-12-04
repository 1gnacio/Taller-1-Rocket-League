#ifndef ROCKET_LEAGUE_BALL_H
#define ROCKET_LEAGUE_BALL_H
#include "../../box2d/include/box2d/box2d.h"
#include "../../src/constants/logic_values.h"

class Ball {
private:

    b2Body* ballBody;
    bool wasPunchedNormal;
    bool wasPunchedFlipShot;
    bool wasPunchedRedShot;
    bool wasPunchedPurpleShot;
    bool wasPunchedGoldShot;
    int framesAfterPunched;
    float secAfterPunched;
    float forceInFlipShot;
    float forceInRedShot;
    float forceInPurpleShot;
    float forceInGoldShot;


public:
    b2Body *getBallBody() const;

    bool isWasPunchedNormal() const;

    bool isWasPunchedFlipShot() const;

    bool isWasPunchedRedShot() const;

    bool isWasPunchedPurpleShot() const;

    bool isWasPunchedGoldShot() const;

public:
    // explicit Ball(b2Body* ballBody);
    Ball();
    void setBody(b2Body* ball);
    void setForces(float forceFlip, float forceRed, float forcePurple, float forceGold);
    void punch(int typeOfPunch);
    void resetPunch();
    void createFixture(b2FixtureDef &fixture);

    bool isAwake();

    float getData(int i);

    void verifyPunch();

    float directionForce(int key);

    void copy(Ball &ball);

    bool isWasPunched();
};




#endif //ROCKET_LEAGUE_BALL_H
