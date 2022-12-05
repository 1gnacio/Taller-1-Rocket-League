#ifndef SRC_LOGIC_CONTACTLISTENERHITS_H_
#define SRC_LOGIC_CONTACTLISTENERHITS_H_
#include "../../box2d/include/box2d/box2d.h"
#include "car.h"
#include "ball.h"
#include <vector>

/*
 * Clase que hereda de b2ConctactListener, el cual se encarga de
 * informar cuando se produce un conctact entre la pelota y algún auto.
 * Tiene la capacidad de informar qué tipo de golpe se produjo, dado que conoce a los
 * autos y a la pelota.
 */

class ContactListenerHits: public b2ContactListener {
 private:
    Ball* ball;
    std::vector<Car>& cars;
    std::vector<int>& ballPunchesLocal;
    std::vector<int>& ballPunchesVisitor;
    bool ballIsAlmostLocalGoal;
    bool ballIsAlmostVisitorGoal;

 public:
    ContactListenerHits(std::vector<Car> &cars,
                        std::vector<int> &ballPunchesLocal,
                        std::vector<int> &ballPunchesVisitor);
    void addBall(Ball* sameBall);
    void BeginContact(b2Contact * contact) override;
    void EndContact(b2Contact * contact) override;
    int getId(b2Body *carBody);
    Car *getCar(int carID);
    void verifyFlip(Car &car);

    void addPunch(int id, float ballVelocityX);

    void verifyAlmostGoal(float ballPositionX,
                            float ballPositionY,
                            float ballVelocityX);
};

#endif  // SRC_LOGIC_CONTACTLISTENERHITS_H_
