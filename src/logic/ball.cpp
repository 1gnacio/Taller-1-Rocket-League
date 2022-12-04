#include <iostream>
#include "ball.h"
#include "../src/constants/b2DVars.h"

Ball::Ball(std::unique_ptr<b2World> &world) :
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
}

b2CircleShape Ball::createShape() {
    b2CircleShape shapeCircle;
    shapeCircle.m_radius = LogicValues::RADIUS_BALL;

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
    fixtureCircle.density = LogicValues().DENSITY_BALL;
    fixtureCircle.friction = LogicValues().FRICTION_BALL;
    fixtureCircle.restitution = LogicValues().RESTITUTION_BALL;
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
    if (key == 3) {
        if (getData(LogicValues().X_VELOCITY) > 1)
            return 1;
        else
            return -1;
    } else if (key == 4) {
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
            std::cout << "aplico Flip Shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*1,
                                                directionForce(4)*1),
                                                true);
        } else if (wasPunchedRedShot) {
            std::cout << "aplico Red Shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*2,
                                                directionForce(4)*2),
                                                true);
        } else if (wasPunchedPurpleShot) {
            std::cout << "aplico Purple shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*5,
                                                directionForce(4)*5),
                                                true);
        } else if (wasPunchedGoldShot) {
            std::cout << "aplico gold shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*10,
                                                directionForce(4)*10),
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

