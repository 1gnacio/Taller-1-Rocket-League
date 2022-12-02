
#include "contactListenerHits.h"
#include <iostream>
#include "../constants/logic_values.h"

void ContactListenerHits::BeginContact(b2Contact * contact){

   // std::cout << "begin contact" << std::endl;
   b2Fixture* fa = contact->GetFixtureA();
   b2Fixture* fb = contact->GetFixtureB();
   if(fa->IsSensor()) {
       if(fb->GetBody() == ball->getBallBody()) {
           int id = getId(fa->GetBody());
           if(getCar(id)->didFlip()) {
               if(fa->GetUserData().pointer == 1) {
                  ball->punch(1);
               } else if(fa->GetUserData().pointer == 2) {
                  ball->punch(3);
               } else if(fa->GetUserData().pointer == 3) {
                  ball->punch(2);
               } else if(fa->GetUserData().pointer == 4) {
                  ball->punch(4);
               } else {
                  ball->punch(0);
               }

           }

       }
   }

   /* else if (fb->IsSensor()) {
       b2Body* body = fb->GetBody();
       int id = getId(body);
       if(fa->GetBody() == ball) {
           if(fb->GetUserData().pointer == 1) {
               std::cout << "choco con la parte superior del auto " << id <<std::endl;
           } else if(fb->GetUserData().pointer == 2) {
               std::cout << "choco con la parte inferior del auto " << id << std::endl;
           } else if(fb->GetUserData().pointer == 3) {
               std::cout << "choco con la parte delantera del auto " << id <<std::endl;
           } else if(fb->GetUserData().pointer == 4) {
               std::cout << "choco con la parte trasera del auto " << id <<std::endl;
           }
       }
   }

    */

}

Car* ContactListenerHits::getCar(int carID) {
    for (auto &x : cars) {
        if (x.getId() == carID) {
            return &x;
        }
    }
    return nullptr;
}

int ContactListenerHits::getId(b2Body* carBody) {
    for(auto &x : cars) {
        if(x.sameBody(carBody)) {
            return x.getId();
        }
    }

}

void ContactListenerHits::EndContact(b2Contact *contact) {
   // std::cout << "emd contact" << std::endl;

}

void ContactListenerHits::addCar(Car &car) {
    cars.push_back(car);

}

void ContactListenerHits::addBall(Ball* sameBall) {
    this->ball = sameBall;
}

void ContactListenerHits::verifyFlip(Car &car) {
    getCar(car.getId())->setMakeFlip(car.isMakeFlip());
    getCar(car.getId())->setSecFlip(car.getSecFlip());

}
/*
void ContactListenerHits::flipShot(Car *pCar) {
    ball->SetLinearVelocity(b2Vec2(pCar->getData(LogicValues().X_VELOCITY),pCar->getData(LogicValues().Y_VELOCITY)));
}

void ContactListenerHits::purpleShot(Car *pCar) {
    ball->SetLinearVelocity(b2Vec2(pCar->getData(LogicValues().X_VELOCITY)*3,pCar->getData(LogicValues().Y_VELOCITY)*3));
}

void ContactListenerHits::redShot(Car *pCar){
    ball->SetLinearVelocity(b2Vec2(pCar->getData(LogicValues().X_VELOCITY)*1.5,pCar->getData(LogicValues().Y_VELOCITY)*1.5));
}

void ContactListenerHits::goldShot(Car *pCar){
    ball->SetLinearVelocity(b2Vec2(pCar->getData(LogicValues().X_VELOCITY)*(-1),pCar->getData(LogicValues().Y_VELOCITY)*(-1)));
}
*/