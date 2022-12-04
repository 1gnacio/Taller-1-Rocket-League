#ifndef ROCKET_LEAGUE_BALL_H
#define ROCKET_LEAGUE_BALL_H

#include <memory>
#include "../../box2d/include/box2d/box2d.h"
#include "../../src/constants/logic_values.h"
#include "../src/configuration/attributes/server_configuration_attributes.h"

class Ball {
private:
    ServerConfigurationAttributes& configuration;
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
    float forceInFlipShot;
    float forceInRedShot;
    float forceInPurpleShot;
    float forceInGoldShot;



    b2BodyDef createBodyDef();
    b2FixtureDef createFixtureDef();
    b2CircleShape createShape();
    void createFixture(b2FixtureDef &fixture);
    void setForces(float forceFlip, float forceRed, float forcePurple, float forceGold);
public:
    b2Body *getBallBody() const;

    bool isWasPunchedNormal() const;

    bool isWasPunchedFlipShot() const;

    bool isWasPunchedRedShot() const;

    bool isWasPunchedPurpleShot() const;

    bool isWasPunchedGoldShot() const;

public:
    explicit Ball(ServerConfigurationAttributes &configuration, std::unique_ptr<b2World> &world);
    void setBody(b2Body* ball);
    void punch(int typeOfPunch);
    void resetPunch();

    bool isAwake();

    float getData(int i);

    void verifyPunch();

    float directionForce(int key);

    void copy(Ball &ball);

    bool isWasPunched();
};




#endif //ROCKET_LEAGUE_BALL_H
