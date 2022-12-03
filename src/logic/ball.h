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
public:
    bool isWasPunchedNormal() const;

    bool isWasPunchedFlipShot() const;

    bool isWasPunchedRedShot() const;

    bool isWasPunchedPurpleShot() const;

    bool isWasPunchedGoldShot() const;

private:
    bool wasPunchedFlipShot;
    bool wasPunchedRedShot;
    bool wasPunchedPurpleShot;
    bool wasPunchedGoldShot;
    int framesAfterPunched;
    float secAfterPunched;

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

    bool isWasPunched();
};




#endif //ROCKET_LEAGUE_BALL_H
