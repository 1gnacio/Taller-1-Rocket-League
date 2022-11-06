#ifndef ROCKET_LEAGUE_BOXLOGIC_H
#define ROCKET_LEAGUE_BOXLOGIC_H

#include "../../box2d/include/box2d/box2d.h"
#include "../protocolo/commands/command.h"
#include <vector>
#include <thread>
// Clase de la logica que contiene todos los movimientos de box2d

class BoxLogic {
private:
   bool isActive;
   b2World world;
   std::vector<b2Body*> walls;
   std::vector<b2Body*> cars; //Por ahora asi, tendra una clase que contenga, por ej, de qué equipo es.
   b2Body* ball;
   std::thread steps;
   void createWalls();
   void createBall();

public:

    BoxLogic();
    void createCar(); // Cuando haya una conexion se creara un auto nuevo
    void addPlayer();
    void update(Command &command);
    void update();
    void updateTime(); // Su propio thread para actualizar box2d
    ~BoxLogic();
};


#endif //ROCKET_LEAGUE_BOXLOGIC_H
