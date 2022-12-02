
#include "contactListenerHits.h"
#include <iostream>

void ContactListenerHits::BeginContact(b2Contact * contact){

   // std::cout << "begin contact" << std::endl;
   b2Fixture* fa = contact->GetFixtureA();
   b2Fixture* fb = contact->GetFixtureB();
   if(fa->IsSensor()) {
       b2Body* body = fa->GetBody();
       int id = getId(body);
       if(fb->GetBody() == ball) {
           if(fa->GetUserData().pointer == 1) {
               std::cout << "choco con la parte superior del auto " << id <<std::endl;
           } else if(fa->GetUserData().pointer == 2) {
               std::cout << "choco con la parte inferior del auto " << id << std::endl;
           } else if(fa->GetUserData().pointer == 3) {
               std::cout << "choco con la parte delantera del auto " << id <<std::endl;
           } else if(fa->GetUserData().pointer == 4) {
               std::cout << "choco con la parte trasera del auto " << id <<std::endl;
           }
       }

   } else if (fb->IsSensor()) {
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

void ContactListenerHits::addBall(b2Body *sameBall) {
    this->ball = sameBall;
}
