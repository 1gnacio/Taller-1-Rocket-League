//
// Created by Nahuel on 14/11/22.
//

#include "car.h"
#include <iostream>
#include "../../src/constants/logic_values.h"

Car::Car(b2Body *body, int ID): carBody(body),
                                secondJump(0),
                                id(ID),
                                turboTank(1),
                                isAccelerating(false),
                                usingTurbo(0),
                                isLocalTeam(!(id%2)),
                                lastDirection(NONE),
                                goals(0),
                                assists(0),
                                saves(0),
                                secFlip(0),
                                makeFlip(false),
                                facingLeft(false),
                                timeAfterPunched(0) {
}

int Car::getId() {
    return this->id;
}

void Car::createFixture(b2FixtureDef & fixture, uintptr_t codeFixture) {
    carBody->CreateFixture(&fixture)->GetUserData().pointer = codeFixture;
}

float Car::getData(int key) {
    switch (key) {
        case 0:
            return carBody->GetPosition().x;
        case 1:
            return carBody->GetPosition().y;
        case 2:
            return carBody->GetAngle();
        case 3:
            return carBody->GetLinearVelocity().x;
        case 4:
            return carBody->GetLinearVelocity().y;
        case 5:
            return turboTank;
        case 6:
            return usingTurbo;
        case 7:
            return isAccelerating;
    }
    return 0;
}


void Car::startMove(b2Vec2 vel) {
    if (!isJumping()) {
        carBody->ApplyForceToCenter(vel, true);
        isAccelerating = true;
        this->facingLeft = vel.x < 0;
    } else {
        float torque = (vel.x < 0 ? -2.0f : 2.0f);
        if (carBody->GetAngularVelocity() < 2.0f &&
            carBody->GetAngularVelocity() > -2.0f) {
            carBody->ApplyTorque(torque, true);
        }
    }
}

void Car::stopMove() {
    if (isJumping()) {
        carBody->SetAngularVelocity(0);
    }
}

bool Car::canJump() {
    return (!isJumping() || (isJumping() && !jumpedTwoTimes()));
}
bool Car::jumpedTwoTimes() {
    return this->secondJump;
}

void Car::modifyJumpedTwoTimes() {
    this->secondJump = 1;
    makeFlip = true;
}

b2Vec2 Car::forceInFlip() {
    if (lastDirection == RIGHT_LAST_DIRECTION) {
        return (b2Vec2(1, -0.5));
    } else if (lastDirection == LEFT_LAST_DIRECTION) {
        return (b2Vec2(-1, -0.5));
    } else if (lastDirection == UP_LAST_DIRECTION) {
        return (b2Vec2(0, -2));
    } else if (lastDirection == DOWN_LAST_DIRECTION) {
        return (b2Vec2(0, 2));
    }
    makeFlip = false;
    return b2Vec2(0, -2);
}

float Car::forceInTorque() {
    if (lastDirection == RIGHT_LAST_DIRECTION) {
        return (10);
    } else if (lastDirection == LEFT_LAST_DIRECTION) {
        return (-10);
    } else if (lastDirection == UP_LAST_DIRECTION) {
        return (-10);
    } else if (lastDirection == DOWN_LAST_DIRECTION) {
        return (-10);
    }
    makeFlip = false;
    return 0;
}

void Car::jump(b2Vec2 vel) {
    if (!secondJump) {
       if (isJumping()) {
           this->modifyJumpedTwoTimes();
           carBody->ApplyLinearImpulseToCenter(forceInFlip(), true);
           carBody->ApplyTorque(forceInTorque(), true);
       } else {
           carBody->ApplyLinearImpulseToCenter(vel, true);
       }
    }
}

bool Car::isJumping() {
    return (carBody->GetPosition().y < (2.23));  // posicion del suelo
}

void Car::verifyDoubleJump() {
    if (!isJumping()) {
        this->secondJump = 0;
        this->secFlip = 0;

        this->lastDirection = NONE;
    }
}
void Car::verifyAcceleration() {
    this->isAccelerating = false;
}

void Car::verifyTurbo() {
    if (usingTurbo) {
        if (turboTank > 0.01f) {
            turboTank -= 0.01f;
        } else {
            turboTank = 0;
        }
    } else {
        if (!isJumping() && !usingTurbo && turboTank< 1) {
            turboTank += 0.001f;
        }
    }
    if (usingTurbo >= 1)
        usingTurbo -= 1;
}

void Car::verifyFlip() {
    if (makeFlip) {
        secFlip = secFlip + 0.04;
    }
    if (!isJumping()) {
        this->makeFlip = false;
        this->punched = false;
        secFlip = 0;
    }
}

b2Vec2 Car::getVelocity() {
    return carBody->GetLinearVelocity();
}

float Car::directionForce(int key) {
    if (key == LogicValues().X_VELOCITY) {
        if (getData(LogicValues().X_VELOCITY) > 0)
            return 1;
        else if (getData(LogicValues().X_VELOCITY) < 0)
            return -1;
    } else if (key == LogicValues().Y_VELOCITY) {
        if (getData(LogicValues().Y_VELOCITY) > 0)
            return 1;
        else if (getData(LogicValues().Y_VELOCITY) < 0)
            return -1;
    }
    return 0;
}

void Car::applyTurbo() {
    usingTurbo = 2;
    if (turboTank > 0) {
       carBody->ApplyForceToCenter(b2Vec2(directionForce(LogicValues().X_VELOCITY)*turboForce,directionForce(LogicValues().Y_VELOCITY)*turboForce), true);
    }
}

void Car::resetPosition() {
    if (id%2)
        carBody->SetTransform(b2Vec2(LogicValues().POS_X_INITIAL_CAR_LOCAL, LogicValues().POS_Y_INITIAL_CAR_LOCAL),
                              LogicValues().ANGLE_CAR);
    else
        carBody->SetTransform(b2Vec2(LogicValues().POS_X_INITIAL_CAR_VISITOR, LogicValues().POS_Y_INITIAL_CAR_VISITOR),
                              LogicValues().ANGLE_CAR);
    carBody->SetLinearVelocity(b2Vec2(0.0f, 0.1f));
    carBody->SetAngularVelocity(0);
}

void Car::destroy(std::unique_ptr<b2World> &world) {
    world->DestroyBody(carBody);
}

bool Car::isLocal() {
    return this->isLocalTeam;
}

bool Car::sameBody(b2Body *pBody) {
    return (pBody == carBody);
}

void Car::changeLastDirection(directions &direction) {
    if (lastDirection != direction) {
        this->lastDirection = direction;
    }
}

directions Car::getLastDirection() {
    return this->lastDirection;
}

bool Car::didFlip() {
    if (makeFlip && secFlip < 0.2) {
        return true;
    }
    return false;
}

bool Car::punchedBall() const {
    return punched;
}

void Car::SetPunchedBall(bool set) {
    punched = set;
}

float Car::getSecFlip() const {
    return secFlip;
}

bool Car::isMakeFlip() const {
    return makeFlip;
}

void Car::setMakeFlip(bool makeFlip) {
    Car::makeFlip = makeFlip;
}

void Car::setSecFlip(float secFlip) {
    Car::secFlip = secFlip;
}

int Car::getGoals() {
    return this->goals;
}

int Car::getAssists() {
    return this->assists;
}

int Car::getSaves() {
    return this->saves;
}

bool Car::isFacingLeft() {
    return this->facingLeft;
}

float Car::remainingTurbo() {
    return this->turboTank;
}

void Car::addGoal() {
    this->goals++;
}

void Car::addAssist() {
    this->assists++;
}

void Car::addSave() {
    this->saves++;
}

void Car::punchedTheBall() {
    this->hasPunchedTheBall = true;
}

void Car::notPunchedTheBall() {
    this->hasPunchedTheBall = false;
}

bool Car::getHasPunchedTheBall() {
    return this->hasPunchedTheBall;
}

void Car::verifyPunch() {

    if(timeAfterPunched > 2) {
        this->hasPunchedTheBall = false;
        timeAfterPunched = 0;
    }
    timeAfterPunched++;

}

void Car::setTurboForce(float force) {
    turboForce = force;
}

