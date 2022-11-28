#ifndef ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#define ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#include "../../box2d/include/box2d/box2d.h"

class ContactListenerHits: public b2ContactListener {

public:
   void BeginContact(b2Contact * contact);
   void EndContact(b2Contact * contact);
   // void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
   // void PostSOlve(b2Contact* contact, const b2ContactImpulse* impulse);
};


#endif //ROCKET_LEAGUE_CONTACTLISTENERHITS_H
