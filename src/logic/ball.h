#ifndef ROCKET_LEAGUE_BALL_H
#define ROCKET_LEAGUE_BALL_H

#include <memory>
#include "../../box2d/include/box2d/box2d.h"
#include "../../src/constants/logic_values.h"

class Ball {
private:
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixtureDef;
    b2Body* ballBody;
    bool wasPunchedNormal;
    bool wasPunchedFlipShot;
    bool wasPunchedRedShot;
    bool wasPunchedPurpleShot;
    bool wasPunchedGoldShot;
    int framesAfterPunched;
    float secAfterPunched;

    b2BodyDef createBodyDef();
    b2FixtureDef createFixtureDef();
    b2CircleShape createShape();
public:
    b2Body *getBallBody() const;

    bool isWasPunchedNormal() const;

    bool isWasPunchedFlipShot() const;

    bool isWasPunchedRedShot() const;

    bool isWasPunchedPurpleShot() const;

    bool isWasPunchedGoldShot() const;

public:
    explicit Ball(std::unique_ptr<b2World> &world);
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
