//
// Created by taller on 02/12/22.
//

#include <iostream>
#include "ball.h"


Ball::Ball(b2Body* body): ballBody(body), framesAfterPunched(0),
                          wasPunchedNormal(false),
                          wasPunchedFlipShot(false),
                          wasPunchedGoldShot(false),
                          wasPunchedPurpleShot(false),
                          wasPunchedRedShot(false) {

};


void Ball::punch(int typeOfPunch) {
    switch(typeOfPunch) {
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

Ball::Ball() {

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
    if(key == 3) {
        if(getData(LogicValues().X_VELOCITY) > 1)
            return 1;
        else
            return -1;
    } else if(key == 4) {
        if(getData(LogicValues().Y_VELOCITY) > 1)
            return 1;
        else
            return -1;
    }

}


void Ball::verifyPunch() {
   // if(framesAfterPunched > 3) {
        if(wasPunchedFlipShot) {
            std::cout << "aplico Flip Shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*1,directionForce(4)*1), true);
        } else if(wasPunchedRedShot) {
            std::cout << "aplico Red Shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*2,directionForce(4)*2), true);
        } else if(wasPunchedPurpleShot) {
            std::cout << "aplico Purple shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*5,directionForce(4)*5), true);
        } else if(wasPunchedGoldShot) {
            std::cout << "aplico gold shot" << std::endl;
            ballBody->ApplyForceToCenter(b2Vec2(directionForce(3)*10,directionForce(4)*10), true);
        }
        resetPunch();
        framesAfterPunched = 0;
   /* } else {
        framesAfterPunched++;
    }*/

}

