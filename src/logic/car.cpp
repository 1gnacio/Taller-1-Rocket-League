//
// Created by Nahuel on 14/11/22.
//

#include "car.h"
#include <iostream>
#include "../../src/constants/logic_values.h"

Car::Car(b2Body *body, int ID):carBody(body), secondJump(0), id(ID), turboTank(1), isAccelerating(false), isLocalTeam(!(id%2)) {
}

int Car::getId() {
    return this->id;
}

void Car::createFixture(b2FixtureDef & fixture) {
    carBody->CreateFixture(&fixture); // carBody->CreateFixture(&fixture)->GetUserData->pointer = num;
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
    } else {
        float torque = (vel.x < 0 ? -2.0f : 2.0f);
        carBody->ApplyTorque(torque, true);
    }
}

void Car::stopMove() {
    //carBody->SetLinearVelocity(b2Vec2(0, 0));

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
}

void Car::jump(b2Vec2 vel) {
    if (!secondJump) {
       if (isJumping()) {
           this->modifyJumpedTwoTimes();
       }
        carBody->ApplyLinearImpulseToCenter(vel, true);
    }
}

bool Car::isJumping() {
    return (carBody->GetPosition().y < (2.23));  // posicion del suelo
}

void Car::verifyDoubleJump() {
    if (!isJumping()) {
        this->secondJump = 0;
    }
}
void Car::verifyAcceleration() {
    this->isAccelerating = false;
}

void Car::verifyTurbo() {
    if(usingTurbo) {
        if(turboTank > 0.01f) {
            turboTank -=0.01f;
        } else {
            turboTank = 0;
        }
    } else {
        if(!isJumping() && !usingTurbo && turboTank< 1) {
            turboTank += 0.001f;
        }
    }
    if(usingTurbo >=1)
        usingTurbo-=1;


}

b2Vec2 Car::getVelocity() {
    return carBody->GetLinearVelocity();
}

void Car::applyTurbo() {
    usingTurbo = 2;
   if(turboTank > 0) {
        b2Vec2 vel(carBody->GetLinearVelocity().x*1.1,
                   carBody->GetLinearVelocity().y*1.1);
        carBody->SetLinearVelocity(b2Vec2(vel.x, vel.y));
   }

}

void Car::resetPosition() {
    if(id%2)
        carBody->SetTransform(b2Vec2(-2.0f, -2.0f), LogicValues().ANGLE_CAR);
     else
        carBody->SetTransform(b2Vec2(2.0f, -2.0f), LogicValues().ANGLE_CAR);

    carBody->SetLinearVelocity(b2Vec2(0.1f,0.1f));
}

void Car::destroy(std::unique_ptr<b2World> &world) {
    world->DestroyBody(carBody);
}

bool Car::isLocal(){
    return this->isLocalTeam;
}