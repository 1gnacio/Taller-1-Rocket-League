#include <algorithm>
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

           this->verifyAlmostGoal(fb->GetBody()->GetPosition().x,
                                  fb->GetBody()->GetPosition().y,
                                  fb->GetBody()->GetLinearVelocity().x);

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

           this->verifyAlmostGoal(fa->GetBody()->GetPosition().x,
                                  fa->GetBody()->GetPosition().y,
                                  fa->GetBody()->GetLinearVelocity().x);
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
    b2Fixture* fa = contact->GetFixtureA();
    b2Fixture* fb = contact->GetFixtureB();

    if(fa->IsSensor()) {
        b2Body* body = fa->GetBody();
        int id = getId(body);
        if(fb->GetBody() == ball) {
            this->addPunch(id, fb->GetBody()->GetLinearVelocity().x);
        }
    } else if (fb->IsSensor()) {
        b2Body* body = fb->GetBody();
        int id = getId(body);
        if(fa->GetBody() == ball) {
            this->addPunch(id, fb->GetBody()->GetLinearVelocity().x);
        }
    }
}

void ContactListenerHits::addCar(Car &car) {
    cars.push_back(car);

}

void ContactListenerHits::addBall(b2Body *sameBall) {
    this->ball = sameBall;
}

ContactListenerHits::ContactListenerHits(std::vector<Car> &cars,
                                         std::vector<int> &ballPunchesLocal,
                                         std::vector<int> &ballPunchesVisitor)
: cars(cars),
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
                      [&found](Car &car)
                      {
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
