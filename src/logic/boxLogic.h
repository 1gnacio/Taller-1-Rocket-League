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
    void addPlayer(); // Tendra atributo para saber el equipo
    void update(Command &command);
    void update();
    b2Vec2 getGravity();
    void updateTime(); // Su propio thread para actualizar box2d
    ~BoxLogic();

    void close();
    int wallsAmount();
    int playersAmount();
    void startMove(int carNumber, bool direction);  // Numero de auto | direccion -> 0=Izq | 1=Der
    void stopMove(int carNumber);
    void jump(int carNumber);

    bool ballIsAwake();
    float getBallData(int key); // 0 -> PosX | 1 = posY | 2 = angulo (grados) | 3 = velocidad en X | 4 = velocidad en Y
    float getCarData(int carNumber, int key);

    b2Body* getCar(int carNumber);

    static b2Vec2 getVectorForce(int direction);
};


#endif //ROCKET_LEAGUE_BOXLOGIC_H
