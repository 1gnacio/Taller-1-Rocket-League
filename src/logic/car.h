#include <memory>
#include "../../box2d/include/box2d/box2d.h"

#ifndef SRC_LOGIC_CAR_H_
#define SRC_LOGIC_CAR_H_

/*
 * Objeto que simula auto en el juego,
 * el cual puede moverse y realizar golpes especiales.
 */

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

    void createFixture(b2FixtureDef &fixture);

    void verifyDoubleJump();

    void verifyTurbo();

    void modifyJumpedTwoTimes();
    bool jumpedTwoTimes();

    b2Vec2 getVelocity();

    int getId();

    void resetPosition();

    void verifyAcceleration();

    void destroy(std::unique_ptr<b2World> &world);
};


#endif  // SRC_LOGIC_CAR_H_
