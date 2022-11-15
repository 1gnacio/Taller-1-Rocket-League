//
// Created by Nahuel on 14/11/22.
//

#include "car.h"


Car::Car(b2Body *body):carBody(body) {

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
    carBody->SetLinearVelocity(vel);
}

void Car::stopMove() {
    carBody->SetLinearVelocity(b2Vec2(0,0));
}

bool Car::canJump(){
    return (carBody->GetPosition().y >= (2.23));
}

void Car::jump(b2Vec2 vel) {
    if(this->canJump()) { // Deberia ser posicion del suelo
        carBody->ApplyLinearImpulseToCenter(vel,true);
    }
}

bool Car::isJumping() {
    return (carBody->GetPosition().y < (2.23));
}
