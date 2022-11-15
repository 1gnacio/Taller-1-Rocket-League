#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/constants/logic_values.h"

const int FIRST_CAR = 1;
TEST(physics, SeCreaElMapaConGravedad10) {
    b2Vec2 v(0.0f,9.8f);
    BoxLogic physics;


    EXPECT_EQ(physics.getGravity(), v);
    physics.close(); // Sino queda el thread del tiempo corriendo
}

TEST(physics, SeCreanCorrectamenteLasParedes) {
    BoxLogic physics;

    EXPECT_EQ(physics.wallsAmount(), 4);
    physics.close();
}

TEST(physics, SeCreaCorrectamenteLaPelota) {
    BoxLogic physics;
    EXPECT_EQ(physics.ballIsAwake(), true);
    physics.close();
}

TEST(physics, movimientoCorrectoDePelota) {
    BoxLogic physics;
    physics.updateTime();

    EXPECT_EQ(physics.getBallData(LogicValues().POS_X), 0);
    EXPECT_TRUE(physics.getBallData(LogicValues().Y_VELOCITY) != 0);
    physics.close();
}

TEST(physics, seAgregaJugadorCorrectamente) {
    BoxLogic physics;
    physics.addPlayer();

    EXPECT_EQ(physics.playersAmount(), 1);
    physics.close();
}
TEST(physics, seAgreganVariosJugadoresCorrectamente) {
    BoxLogic physics;

    physics.addPlayer();
    physics.addPlayer();
    physics.addPlayer();
    physics.addPlayer();

    EXPECT_EQ(physics.playersAmount(), 4);
    physics.close();
}

TEST(physics, sePosicionaAutoCorrectamente) {
    BoxLogic physics;
    physics.addPlayer();
    physics.updateTime();

    EXPECT_EQ(physics.getCarData(FIRST_CAR,LogicValues().POS_X), 2);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) != 0);
    physics.close();
}

TEST(physics, aceleracionCorrectaConComando) {
    BoxLogic physics;
    physics.addPlayer();
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY) != 0);
    physics.close();
}

TEST(physics, FrenoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    physics.stopMove(FIRST_CAR); // Chequear velocidad lineal
    EXPECT_EQ(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY), 0);
    physics.close();
}

TEST(physics, SaltoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    for(int i = 0; i < 20; i++){ // Actualizo tiempo hasta que pueda saltar (Tiene que estar en el suelo y aparece cayendo)
        physics.updateTime();
    }
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) == 0);
    physics.jump(FIRST_CAR);
    physics.updateTime();

    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < 0);
    physics.close();
}