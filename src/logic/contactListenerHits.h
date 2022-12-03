#ifndef ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#define ROCKET_LEAGUE_CONTACTLISTENERHITS_H
#include "../../box2d/include/box2d/box2d.h"
#include "car.h"
#include "ball.h"
#include <vector>

class ContactListenerHits: public b2ContactListener {
private:
    Ball* ball;
public:
   void addBall(Ball* sameBall);
   void addCar(Car &car);
   void BeginContact(b2Contact * contact);
   void EndContact(b2Contact * contact);
   // void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
   // void PostSOlve(b2Contact* contact, const b2ContactImpulse* impulse);
   int getId(b2Body *carBody);

    Car *getCar(int carID);


    void verifyFlip(Car &car);
    std::vector<Car>& cars;
    std::vector<int>& ballPunchesLocal;
    std::vector<int>& ballPunchesVisitor;
    bool ballIsAlmostLocalGoal;
    bool ballIsAlmostVisitorGoal;
    void addPunch(int id, float ballVelocityX);
    void verifyAlmostGoal(float ballPositionX,
                            float ballPositionY,
                            float ballVelocityX);
public:
    ContactListenerHits(std::vector<Car> &cars,
                        std::vector<int> &ballPunchesLocal,
                        std::vector<int> &ballPunchesVisitor);
    // void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    // void PostSOlve(b2Contact* contact, const b2ContactImpulse* impulse);


};


#endif //ROCKET_LEAGUE_CONTACTLISTENERHITS_H
