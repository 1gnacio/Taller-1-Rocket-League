
#include "contactListenerHits.h"
#include <iostream>

void ContactListenerHits::BeginContact(b2Contact * contact){

   // std::cout << "begin contact" << std::endl;
   b2Fixture* fa = contact->GetFixtureA();
   b2Fixture* fb = contact->GetFixtureB();
   if(fa->IsSensor()) {
      // std::cout << "choco con la parte superior del auto" << std::endl;
       b2Body* body = fb->GetBody();
      // body->SetLinearVelocity(b2Vec2(-5,-5));
   } else if (fb->IsSensor()) {
      // std::cout << "choco con la parte superior del auto" << std::endl;
       b2Body* body = fa->GetBody();
      // body->SetLinearVelocity(b2Vec2(-5,-5));
   }

}

void ContactListenerHits::EndContact(b2Contact *contact) {
   // std::cout << "emd contact" << std::endl;

}
