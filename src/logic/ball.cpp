#include <iostream>
#include "ball.h"

void Ball::punch(const int typeOfPunch) {
    switch (typeOfPunch) {
        case LogicValues().NORMAL_SHOT:
            this->wasPunchedNormal = true;
            break;
        case LogicValues().FLIP_SHOT:
            this->wasPunchedFlipShot = true;
            break;
        case LogicValues().RED_SHOT:
            this->wasPunchedRedShot = true;
            break;
        case LogicValues().PURPLE_SHOT:
            this->wasPunchedPurpleShot = true;
            break;
        case LogicValues().GOLD_SHOT:
            this->wasPunchedGoldShot = true;
            break;
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

Ball::Ball():
            ballBody(nullptr),
            wasPunchedNormal(),
            wasPunchedFlipShot(false),
            wasPunchedRedShot(false),
            wasPunchedPurpleShot(false),
            wasPunchedGoldShot(false),
            framesAfterPunched(0),
            secAfterPunched(0),
            forceInFlipShot(0),
            forceInRedShot(0),
            forceInPurpleShot(0),
            forceInGoldShot(0) {
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
        return (getData(LogicValues().X_VELOCITY) > 1) ? 1 : -1;
    } else if (key == LogicValues().Y_VELOCITY) {
        return (getData(LogicValues().Y_VELOCITY) > 1) ? 1 : -1;
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
    if (secAfterPunched > 2) {
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

void Ball::setForces(float forceFlip, float forceRed,
                     float forcePurple, float forceGold) {
    this->forceInFlipShot = forceFlip;
    this->forceInRedShot = forceRed;
    this->forceInPurpleShot = forcePurple;
    this->forceInGoldShot = forceGold;
}
