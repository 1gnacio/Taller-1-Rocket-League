#ifndef ROCKET_LEAGUE_BOXLOGIC_H
#define ROCKET_LEAGUE_BOXLOGIC_H

#include "../../box2d/include/box2d/box2d.h"
#include "../protocolo/commands/command.h"
#include <vector>
#include <thread>
#include <mutex>
// Clase de la logica que contiene todos los movimientos de box2d

class BoxLogic {
private:
   bool isActive;
   b2Body* ball;

   std::vector<b2Body*> walls;
   std::vector<b2Body*> cars; //Por ahora asi, tendra una clase que contenga, por ej, de qué equipo es.

   std::thread steps;
   std::mutex mutex;
   void createWalls();
   void createBall();
   static float getData(int key, const b2Body *body);


public:
    std::unique_ptr<b2World> world;
    BoxLogic();
    void createCar(); // Cuando haya una conexion se creara un auto nuevo
    void addPlayer();
    void update(Command &command);
    void update();
    b2Vec2 getGravity();
    void updateTime(); // Su propio thread para actualizar box2d
    ~BoxLogic();

    void close();
    int wallsAmount();

    bool ballIsAwake();
    float getBallData(int key); // 0 -> Pos X | 1 = posY | 2 = angulo (grados)

};


#endif //ROCKET_LEAGUE_BOXLOGIC_H
