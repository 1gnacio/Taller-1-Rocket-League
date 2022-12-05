#ifndef SRC_LOGIC_BALL_H_
#define SRC_LOGIC_BALL_H_
#include "../../box2d/include/box2d/box2d.h"
#include "../../src/constants/logic_values.h"

/*
 * Clase perteneciente a la lógica del juego que se encarga de
 * la manipulación de la pelota.
 */

class Ball {
 private:
    b2Body* ballBody;
    bool wasPunchedNormal;
    bool wasPunchedFlipShot;
    bool wasPunchedRedShot;
    bool wasPunchedPurpleShot;
    bool wasPunchedGoldShot;
    int framesAfterPunched;
    float secAfterPunched;
    float forceInFlipShot;
    float forceInRedShot;
    float forceInPurpleShot;
    float forceInGoldShot;

 public:
    Ball();

    b2Body *getBallBody() const;

    bool isWasPunchedNormal() const;

    bool isWasPunchedFlipShot() const;

    bool isWasPunchedRedShot() const;

    bool isWasPunchedPurpleShot() const;

    bool isWasPunchedGoldShot() const;

    /*
     * Se setea el b2Body de la pelota, deberá ser el mismo
     * del creado por el mundo de box2D
     */
    void setBody(b2Body* ball);

    /*
     * Se setean los módulos de las fuerzas
     * en los golpes especiales.
     */
    void setForces(float forceFlip, float forceRed,
                   float forcePurple, float forceGold);

    /*
     * Modifica el estado correspondiente de la pelota sobre
     * el tipo de golpe que recibe.
     */
    void punch(int typeOfPunch);

    /*
     * Luego de cada paso del tiempo, se reseta el golpe a FALSE
     * en todos sus atributos de golpe.
     */
    void resetPunch();

    void createFixture(b2FixtureDef &fixture);

    bool isAwake();

    /*
     * Para el siguiente mètodo se utilizan como claves:
     *  POS_X = 0;
     *  POS_Y = 1;
     *  ANGLE = 2;
     *  X_VELOCITY = 3;
     *  Y_VELOCITY = 4;
     */
    float getData(int key);

    /*
     * Verifica si se realizó algún tipo de golpe especial contra la pelota
     * y si es correcto, se le aplica una fuerza extra correspondiente al tipo
     * de golpe
     */
    void verifyPunch();

    /*
     * Dependiendo a qué lado vaya el vector velocidad, se devolverá la velocidad normalizada.
     * Key:
     * X_VELOCITY = 3;
     * Y_VELOCITY = 4;
     */
    float directionForce(int key);

    bool isWasPunched();
};
#endif  // SRC_LOGIC_BALL_H_
