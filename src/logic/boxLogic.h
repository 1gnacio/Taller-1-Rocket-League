#ifndef SRC_LOGIC_BOXLOGIC_H_
#define SRC_LOGIC_BOXLOGIC_H_

#include "../../box2d/include/box2d/box2d.h"
#include "../protocolo/commands/command.h"
#include <vector>
#include "../../src/constants/logic_values.h"
#include "../protocolo/responses/player_responses.h"
#include "car.h"
#include "SoccerGoal.h"
#include "../src/protocolo/responses/match_response.h"
#include <memory>

// Clase de la logica que contiene todos los movimientos de box2d

class BoxLogic {
 private:
    bool isActive;
    b2Body* ball;
    std::unique_ptr<b2World> world;
    std::vector<b2Body*> walls;
    std::vector<Car> cars;
    std::vector<SoccerGoal> soccerGoals;
    void createWalls();
    void createBall();
    static float getData(int key, const b2Body* body);

 public:
    BoxLogic();
    void createCar(int id);  // Cuando haya una conexion se creara un auto nuevo
    void addPlayer(int id);  // Tendra atributo para saber el equipo
    bool hasPlayer(int id);
    void removePlayer(int id) { /*TODO*/ }
    void update(Command &command);
    void update();
    b2Vec2 getGravity();
    void updateTime();
    void updateStatus();
    ~BoxLogic();

    void close();
    int wallsAmount();
    int playersAmount();
    void startMove(int carNumber, bool direction);  // direc: 0=Izq | 1=Der
    void stopMove(int carNumber);
    void jump(int carNumber);
    void applyTurbo(int carNumber);

    bool ballIsAwake();
    float getBallData(int key);
    float getCarData(int carNumber, int key);
    PlayerResponses getPlayersData();
    BallResponse getBallResponse();

    Car* getCar(int carNumber);
    static b2Vec2 getVectorForce(int direction);

    void verifyDoubleJump();
    void verifyTurbo();

    void SoccerGoals();

    void createSoccerGoals();
};

#endif  //  SRC_LOGIC_BOXLOGIC_H_
