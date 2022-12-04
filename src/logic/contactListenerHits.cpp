#include <algorithm>
#include "contactListenerHits.h"
#include <iostream>
#include "../constants/logic_values.h"

void ContactListenerHits::BeginContact(b2Contact * contact) {
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();
    if (fa->IsSensor()) {
        if (fb->GetBody() == ball.getBallBody()) {
            int id = getId(fa->GetBody());
            if (getCar(id)->didFlip()) {
                if (fa->GetUserData().pointer == 1) {
                   ball.punch(1);
                } else if (fa->GetUserData().pointer == 2) {
                   ball.punch(3);
                } else if (fa->GetUserData().pointer == 3) {
                   ball.punch(2);
                } else if (fa->GetUserData().pointer == 4) {
                   ball.punch(4);
                } else {
                   ball.punch(0);
                }
            }
           this->verifyAlmostGoal(fb->GetBody()->GetPosition().x,
                                  fb->GetBody()->GetPosition().y,
                                  fb->GetBody()->GetLinearVelocity().x);
        }
    }
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
    for (auto &x : cars) {
        if (x.sameBody(carBody)) {
            return x.getId();
        }
    }
    return 0;
}

void ContactListenerHits::EndContact(b2Contact *contact) {
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    if (fa->IsSensor()) {
        b2Body* body = fa->GetBody();
        int id = getId(body);
        if (fb->GetBody() == ball.getBallBody()) {
            this->addPunch(id, fb->GetBody()->GetLinearVelocity().x);
        }
    } else if (fb->IsSensor()) {
        b2Body* body = fb->GetBody();
        int id = getId(body);
        if (fa->GetBody() == ball.getBallBody()) {
            this->addPunch(id, fb->GetBody()->GetLinearVelocity().x);
        }
    }
}

void ContactListenerHits::addCar(Car &car) {
    cars.push_back(car);
}

void ContactListenerHits::verifyFlip(Car &car) {
    getCar(car.getId())->setMakeFlip(car.isMakeFlip());
    getCar(car.getId())->setSecFlip(car.getSecFlip());
}

ContactListenerHits::ContactListenerHits(Ball &ball,
                                         std::vector<Car> &cars,
                                         std::vector<int> &ballPunchesLocal,
                                         std::vector<int> &ballPunchesVisitor) :
                                         cars(cars), ball(ball),
                                         ballPunchesLocal(ballPunchesLocal),
                                         ballPunchesVisitor(ballPunchesVisitor),
                                         ballIsAlmostLocalGoal(false),
                                         ballIsAlmostVisitorGoal(false) {}

void ContactListenerHits::addPunch(int id, float ballVelocityX) {
    auto found = std::find_if(this->cars.begin(),
                              this->cars.end(),
                              [&id](Car &car)
                              {return car.getId() == id;});

    if (found != this->cars.end()) {
        if (found->isLocal()) {
            this->ballPunchesLocal.push_back(found->getId());
            if (this->ballIsAlmostVisitorGoal &&
                ballVelocityX > 0) {
                found->addSave();
            }
        } else {
            this->ballPunchesVisitor.push_back(found->getId());
            if (this->ballIsAlmostLocalGoal &&
                ballVelocityX < 0) {
                found->addSave();
            }
        }
        found->punchedTheBall();

        std::for_each(this->cars.begin(),
                      this->cars.end(),
                      [&found](Car &car) {
                        if (car.getId() != found->getId()) {
                          car.notPunchedTheBall();
                        }
                      });
    }
}

void ContactListenerHits::verifyAlmostGoal(float ballPositionX,
                                             float ballPositionY,
                                             float ballVelocityX) {
    /*La idea es: si la pelota esta cerca del arco local o visitante y la velocidad
            * de la pelota apunta en x hacia el arco, es un casi gol.
            *
            * SI luego del impacto, la velocidad de la pelota cambia en x hacia fuera del arco,
            * es una atajada, pero cuenta solo si el que la golpea es del equipo contrario*/
    bool isNearLocalGoalX = abs(ballPositionX - 2.5f) < 0.4f;
    bool isNearVisitorGoalX = abs(ballPositionX - (-2.5f)) < 0.4f;
    bool isNearGoalY = abs(ballPositionY - 2.2f) < 0.4f;

    this->ballIsAlmostLocalGoal = isNearLocalGoalX &&
                                  isNearGoalY &&
                                  ballVelocityX > 0;
    this->ballIsAlmostVisitorGoal = isNearVisitorGoalX &&
                                    isNearGoalY &&
                                    ballVelocityX < 0;
}
