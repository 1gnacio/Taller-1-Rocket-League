#include <memory>
#include "../../box2d/include/box2d/box2d.h"

#ifndef SRC_LOGIC_CAR_H_
#define SRC_LOGIC_CAR_H_

/*
 * Objeto que simula auto en el juego,
 * el cual puede moverse y realizar golpes especiales.
 */
enum directions {
    NONE,
    RIGHT_LAST_DIRECTION,
    LEFT_LAST_DIRECTION,
    UP_LAST_DIRECTION,
    DOWN_LAST_DIRECTION,
};

class Car {
 private:
    b2Body* carBody;
    int secondJump;
    int id;
    float turboTank;
    bool isAccelerating;
    int usingTurbo;
    bool isLocalTeam;
    directions lastDirection;
    int goals;
    int assists;
    int saves;
    float secFlip;
    bool makeFlip;
    bool facingLeft;
    bool hasPunchedTheBall;
    int timeAfterPunched;
    int timeAfterAccelerate;
    float turboForce;
    float torqueForce;

 public:
    /*
     * Se crea el objeto a partir de un b2Body de la librera de box2D
     */
    Car(b2Body* carBody, int id, float torqueForce);

    /*
     * Comienza el movimiento del auto en la dirección
     * estipulada por el vector que aparece en el parámetro.
     */
    void startMove(b2Vec2 vel);

    /*
     * La velocidad linear del auto se setea en en el vector (0,0)
     */
    void stopMove();

    /*
     * Si es posible, el auto hace un salto, el cual es provocado
     * por un inpulso lineal en la dirección de Y.
     */
    void jump(b2Vec2 vel);


    void applyTurbo();

    /*
     * Retorna un dato pedido según una key:
     * POS_X = 0; POS_Y = 1; ANGLE = 2; X_VELOCITY = 3; Y_VELOCITY = 4;
     */
    float getData(int key);

    void createFixture(b2FixtureDef &fixture, uintptr_t codeFixture);

    void verifyDoubleJump();

    void verifyTurbo();

    void modifyJumpedTwoTimes();

    int getId();

    void resetPosition();

    void verifyAcceleration();

    bool isLocal();

    void destroy(std::unique_ptr<b2World> &world);

    bool sameBody(const b2Body *pBody);

    void changeLastDirection(directions &direction);

    b2Vec2 forceInFlip();

    float forceInTorque();

    bool didFlip();

    void verifyFlip();

    int getGoals();

    int getAssists();

    int getSaves();

    bool isFacingLeft();

    float remainingTurbo();

    void addGoal();

    bool isJumping();

    void addAssist();

    void addSave();

    void punchedTheBall();

    void notPunchedTheBall();

    bool getHasPunchedTheBall();

    void verifyPunch();

    void setTurboForce(float force);

    float directionForce(int key);

    int directionFace();

    void setSecFlip(float secFlip);

    float getSecFlip() const;

    bool isMakeFlip() const;

    void setMakeFlip(bool makeFlip);
};

#endif  // SRC_LOGIC_CAR_H_
