#ifndef SRC_LOGIC_BOXLOGIC_H_
#define SRC_LOGIC_BOXLOGIC_H_

#include "../../box2d/include/box2d/box2d.h"
#include "../protocolo/commands/command.h"
#include <vector>
#include "../../src/constants/logic_values.h"
#include "../protocolo/responses/player_responses.h"
#include "car.h"
#include "SoccerGoal.h"
#include <memory>
#include "game.h"
#include "../src/game_entities/room.h"
#include "contactListenerHits.h"
#include "../src/constants/command_values.h"

/*
 * Objeto que manipula la física de cada partida a partir de box2d
 */

class BoxLogic {
 private:
    bool isActive;
    std::unique_ptr<b2World> world;
    Game game;
    Ball ball;
    std::vector<b2Body*> walls;
    std::vector<Car> cars;
    std::vector<SoccerGoal> soccerGoals;
    std::vector<int> ballPunchesLocal;
    std::vector<int> ballPunchesVisitor;
    ContactListenerHits contactListener;
    void createWalls();
    static float getData(int key, const b2Body* body);
    void addGoalToPlayer(int id);
 public:
    /*
     * Se instancia una mundo y a partir de ello,
     * una pelota, los bordes del mapa y los arcos
     */
    explicit BoxLogic(int requiredPlayers, const char *name);

    void createCar(int id);  // Cuando haya una conexion se creara un auto nuevo
    void createSoccerGoals();

    /*
     * Cuando ingresa un nuevo jugador, se instancia un auto nuevo
     * (Actualmente cuando ingresa llega un commando "TURBO_RELEASE" que debe ser modificado).
     */
    void addPlayer(int id);

    /*
     * Actualiza el tiempo en el mundo usando el método Step() en 0.04 segundos.
     * Además, para que se vea realista su forma de actuar, se utiliza la función usleep()
     * con el mismo tiempo.
     */
    void updateTime();
    /*
     * Luego de cada actualización del tiempo, se verifican los estados de
     * doble salto; goles y Turbo para actualizarlos según correspondan.
     */
    void updateStatus();
    void update(Command &command);
    void update();
    /*
     * Se aplican los siguientes métodos em el auto dependiendo lo que se quiera
     * hacer.
     */
    void startMove(int carNumber, bool direction);  // direc: 0=Izq | 1=Der
    void stopMove(int carNumber);
    void jump(int carNumber);
    void applyTurbo(int carNumber);

    /*
     * Para los siguientes 2 métodos se utilizan como claves:
     *  POS_X = 0;
     *  POS_Y = 1;
     *  ANGLE = 2;
     *  X_VELOCITY = 3;
     *  Y_VELOCITY = 4;
     */
    float getBallData(int key);
    float getCarData(int carNumber, int key);

    PlayerResponses getPlayersData();
    Car* getCar(int carNumber);
    static b2Vec2 getVectorForce(int direction, directions& lastDir);
    void verifyDoubleJump();
    void verifyTurbo();
    void verifyGoal();
    void resetPositions();
    MatchResponse gameData(BallResponse &ball, PlayerResponses &players);

    void updateGoal();

    /*
     * Luego de cada gol, se resetea los atributos de Game,
     * que contiene si existe un gol de algún équipo
     */
    void resetData();

    b2Vec2 getGravity();
    int wallsAmount();
    int playersAmount();
    bool ballIsAwake();
    ~BoxLogic();

    void verifyAcceleration();

    int getTime();

    void removePlayer(int i);

    bool isGoal();

    void setRoomInfo(Room &room, bool b);

    bool matchFinished();

    void updateLastDirection(int id, const std::basic_string<char>& deserializedCommand);

    void verifyFlip();

    void verifyPunch();

    bool getBallDataPunched(const int i);

    bool BallHasBeenPunched();
};

#endif  //  SRC_LOGIC_BOXLOGIC_H_
