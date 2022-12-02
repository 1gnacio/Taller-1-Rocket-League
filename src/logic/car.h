#include <memory>
#include "../../box2d/include/box2d/box2d.h"

#ifndef SRC_LOGIC_CAR_H_
#define SRC_LOGIC_CAR_H_
//#include"stateMachine.h"

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
    float turboTank;
    int id;
    b2Body* carBody;
    bool canJump();
    bool isJumping();
    int secondJump;
    int usingTurbo;
    bool isAccelerating;
    bool isLocalTeam;
    directions lastDirection;
    float secFlip;
public:
    void setSecFlip(float secFlip);

public:
    float getSecFlip() const;

    bool isMakeFlip() const;

private:
    bool makeFlip;
public:
    void setMakeFlip(bool makeFlip);
private:
    bool punched;

 public:
    /*
     * Se crea el objeto a partir de un b2Body de la librera de box2D
     */
    Car(b2Body* carBody, int id);

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
    bool jumpedTwoTimes();

    b2Vec2 getVelocity();

    int getId();

    void resetPosition();

    void verifyAcceleration();

    bool isLocal();

    void destroy(std::unique_ptr<b2World> &world);

    bool sameBody(b2Body *pBody);

    void changeLastDirection(directions &direction);

    directions getLastDirection();

    void verifyLastMovement();

    b2Vec2 forceInFlip();

    float forceInTorque();

    bool didFlip();

    bool verifyFlip();

    bool punchedBall() const;

    void SetPunchedBall(bool set);
};


#endif  // SRC_LOGIC_CAR_H_
