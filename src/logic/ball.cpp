#include <iostream>
#include "ball.h"
#include "../src/constants/b2DVars.h"

Ball::Ball(ServerConfigurationAttributes &configuration, std::unique_ptr<b2World> &world) :
configuration(configuration),
bodyDef(this->createBodyDef()),
shape(this->createShape()),
fixtureDef(this->createFixtureDef()),
ballBody(world->CreateBody(&this->bodyDef)),
wasPunchedNormal(false),
wasPunchedFlipShot(false),
wasPunchedRedShot(false),
wasPunchedPurpleShot(false),
wasPunchedGoldShot(false),
framesAfterPunched(0),
secAfterPunched(0) {
    this->ballBody->CreateFixture(&this->fixtureDef);
    this->setForces(configuration.getForceFlipShot(), configuration.getForceRedShot(),
                         configuration.getForcePurpleShot(), configuration.getForceGoldShot());
}

b2CircleShape Ball::createShape() {
    b2CircleShape shapeCircle;
    shapeCircle.m_radius = configuration.getBallRadius();

    return shapeCircle;
}

b2BodyDef Ball::createBodyDef() {
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(0, -2.8f);
    return ballDef;
}

b2FixtureDef Ball::createFixtureDef() {
    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &this->shape;
    fixtureCircle.density = configuration.getBallDensity();
    fixtureCircle.friction = configuration.getBallFriction();
    fixtureCircle.restitution = configuration.getBallRestitution();
    fixtureCircle.filter.categoryBits = B2DVars().BIT_BALL;
    fixtureCircle.filter.maskBits = B2DVars().BIT_CAR |
                                    B2DVars().BIT_GROUND |
                                    B2DVars().BIT_SOCCER_GOAL;

    return fixtureCircle;
}

void Ball::punch(int typeOfPunch) {
    switch (typeOfPunch) {
        case 0:
            this->wasPunchedNormal = true;
        case 1:
            this->wasPunchedFlipShot = true;
        case 2:
            this->wasPunchedRedShot = true;
        case 3:
            this->wasPunchedPurpleShot = true;
        case 4:
            this->wasPunchedGoldShot = true;
    }
    framesAfterPunched = 0;
    secAfterPunched = 0;
}

void Ball::resetPunch() {
    wasPunchedNormal = false;
    wasPunchedFlipShot = false;
    wasPunchedRedShot = false;
    wasPunchedPurpleShot = false;
    wasPunchedGoldShot = false;
}

b2Body *Ball::getBallBody() const {
    return ballBody;
}

void Ball::createFixture(b2FixtureDef &fixture) {
    ballBody->CreateFixture(&fixture);
}

bool Ball::isAwake() {
    return ballBody->IsAwake();
}

void Ball::setBody(b2Body *ball) {
    ballBody = ball;
}

float Ball::getData(int key) {
    switch (key) {
        case 0:
            return ballBody->GetPosition().x;
        case 1:
            return ballBody->GetPosition().y;
        case 2:
            return ballBody->GetAngle();
        case 3:
            return ballBody->GetLinearVelocity().x;
        case 4:
            return ballBody->GetLinearVelocity().y;
    }
    return 0;
}

float Ball::directionForce(int key) {
    if (key == LogicValues().X_VELOCITY) {
        if (getData(LogicValues().X_VELOCITY) > 1)
            return 1;
        else
            return -1;
    } else if (key == LogicValues().Y_VELOCITY) {
        if (getData(LogicValues().Y_VELOCITY) > 1)
            return 1;
        else
            return -1;
    }
    return 0;
}

void Ball::verifyPunch() {
    if (secAfterPunched == 0) {
        if (wasPunchedFlipShot) {
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(LogicValues().X_VELOCITY)*forceInFlipShot,
                                                directionForce(LogicValues().Y_VELOCITY)*forceInFlipShot),
                                                true);
        } else if (wasPunchedRedShot) {
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(LogicValues().X_VELOCITY)*forceInRedShot,
                                                directionForce(LogicValues().Y_VELOCITY)*forceInRedShot),
                                                true);
        } else if (wasPunchedPurpleShot) {
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*forceInPurpleShot,
                                                directionForce(4)*forceInPurpleShot),
                                                true);
        } else if (wasPunchedGoldShot) {
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*forceInGoldShot,
                                                directionForce(4)*forceInGoldShot),
                                                true);
        }
    }
    secAfterPunched += 0.04;
    if (secAfterPunched > 3) {
        resetPunch();
        secAfterPunched = 0;
    }
}

bool Ball::isWasPunchedNormal() const {
    return wasPunchedNormal;
}

bool Ball::isWasPunchedFlipShot() const {
    return wasPunchedFlipShot;
}

bool Ball::isWasPunchedRedShot() const {
    return wasPunchedRedShot;
}

bool Ball::isWasPunchedPurpleShot() const {
    return wasPunchedPurpleShot;
}

bool Ball::isWasPunchedGoldShot() const {
    return wasPunchedGoldShot;
}

bool Ball::isWasPunched() {
    return (wasPunchedGoldShot || wasPunchedPurpleShot ||
            wasPunchedRedShot || wasPunchedFlipShot || wasPunchedNormal);
}

void Ball::setForces(float forceFlip, float forceRed, float forcePurple, float forceGold) {
    this->forceInFlipShot = forceFlip;
    this->forceInRedShot = forceRed;
    this->forceInPurpleShot = forcePurple;
    this->forceInGoldShot = forceGold;

}
