#ifndef ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#define ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#include "../../box2d/include/box2d/box2d.h"
#include "car.h"
#include <vector>

class ContactListenerHits: public b2ContactListener {
private:
    std::vector<Car> cars;
    b2Body* ball;
public:
   void addBall(b2Body* sameBall);
   void addCar(Car &car);
   void BeginContact(b2Contact * contact);
   void EndContact(b2Contact * contact);
   // void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
   // void PostSOlve(b2Contact* contact, const b2ContactImpulse* impulse);
   int getId(b2Body *carBody);
};


#endif //ROCKET_LEAGUE_CONTACTLISTENERHITS_H