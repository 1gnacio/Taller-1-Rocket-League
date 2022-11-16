//
// Created by Nahuel on 14/11/22.
//

#include "car.h"
#include <iostream>

Car::Car(b2Body *body):carBody(body), secondJump(true) {
}

void Car::createFixture(b2FixtureDef & fixture) {
    carBody->CreateFixture(&fixture);

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
    }
    return 0;


}

void Car::startMove(b2Vec2 vel) {
    if( !isJumping() )
        carBody->SetLinearVelocity(vel);
    else {
        float torque = (vel.x<0 ? 1.0f : -1.0f);
        carBody->ApplyTorque(torque, true);
    }

}

void Car::stopMove() {
    carBody->SetLinearVelocity(b2Vec2(0,0));
}

bool Car::canJump(){
    return (!isJumping() || (isJumping() && !jumpedTwoTimes()));
}
bool Car::jumpedTwoTimes() const{
    return this->secondJump;
}

void Car::modifyJumpedTwoTimes() {

    this->secondJump = 1;

}

void Car::jump(b2Vec2 vel) {
    //std::cout << secondJump << std::endl;
    if(this->canJump()) {
        if(isJumping()) {
            modifyJumpedTwoTimes();
        }
        carBody->ApplyLinearImpulseToCenter(vel,true);
    }
}

bool Car::isJumping() {
    return (carBody->GetPosition().y < (2.23)); // posicion del suelo
}

void Car::verifyDoubleJump() {
    //std::cout << secondJump << std::endl;
    if(!isJumping()) {
        secondJump = false;

    }
}

void Car::verifyTurbo() {


}
