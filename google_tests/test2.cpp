#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"
#include "../src/constants/logic_values.h"

const int FIRST_CAR = 1;


void update(BoxLogic & physics, int frames) {
    for (int i = 0; i < frames; i ++) {
        physics.updateTime();
        physics.updateStatus();
    }
}
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
    for(int i = 0; i < 100; i++){ // Actualizo tiempo hasta que pueda saltar (Tiene que estar en el suelo y aparece cayendo)
        physics.updateTime();
    }
    EXPECT_TRUE(physics.getCarData(FIRST_CAR, LogicValues().X_VELOCITY) == 0);
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION); // Le aplica una fuerza, no le setea una velocidad.
    physics.updateTime();
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY) != 0);
    physics.close();
}

TEST(physics, FrenoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    physics.stopMove(FIRST_CAR);
    EXPECT_EQ(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY), 0);
    physics.close();
}

TEST(physics, SaltoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    for(int i = 0; i < 100; i++){ // Actualizo tiempo hasta que pueda saltar (Tiene que estar en el suelo y aparece cayendo)
        physics.updateTime();
    }
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) == 0);
    physics.jump(FIRST_CAR);
    physics.updateTime();

    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < 0);
    physics.close();
}

TEST(physics, MueveAnguloEnElAire) {
    BoxLogic physics;
    physics.addPlayer();
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().ANGLE) == 0);
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().ANGLE) != 0);

}

TEST(physics, DobleSaltoCorrecto) {
    BoxLogic physics;
    physics.addPlayer();
    update(physics, 100);

    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) == 0);

    physics.jump(FIRST_CAR);
    update(physics, 1);

    float vel1 = physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < 0);
    physics.jump(FIRST_CAR);
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < vel1);
}

TEST(physics, RealizaTresSaltosYELUltimoNoCuenta) {
    BoxLogic physics;
    physics.addPlayer();
    update(physics,100);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) == 0);
    physics.jump(FIRST_CAR);
    update(physics, 5);

    float vel1 = physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < 0);
    physics.jump(FIRST_CAR);
    update(physics,5);

    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < vel1);
    float vel2 = physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY);
    physics.jump(FIRST_CAR);
    update(physics,5);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) > vel2);
}

TEST(physics, RealizaUnTurbo) {
    BoxLogic physics;
    physics.addPlayer();
    update(physics,100);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY) == 0);

    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    update(physics,1);
    float vel1 = physics.getCarData(FIRST_CAR, LogicValues().X_VELOCITY);
    physics.applyTurbo(FIRST_CAR);

    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY) < vel1);

}







TEST(response, RespuestaCorrecta) {
    GameLogic logic;
    logic.updateTime();
    Response response = logic.getResponse();
    EXPECT_TRUE(response.getBallPositionY() > -2.8); // PosY inicial pelota
}
