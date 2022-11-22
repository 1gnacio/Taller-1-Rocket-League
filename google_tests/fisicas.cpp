#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"

static const int PLAYER_ID = 1;
const int PLAYER_ID_2 = 2;
const int PLAYER_ID_3 = 3;
const int PLAYER_ID_4 = 4;


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
}

TEST(physics, SeCreanCorrectamenteLasParedes) {
    BoxLogic physics;

    EXPECT_EQ(physics.wallsAmount(), 4);
}

TEST(physics, SeCreaCorrectamenteLaPelota) {
    BoxLogic physics;
    EXPECT_EQ(physics.ballIsAwake(), true);
}

TEST(physics, movimientoCorrectoDePelota) {
    BoxLogic physics;
    physics.updateTime();

    EXPECT_EQ(physics.getBallData(LogicValues().POS_X), 0);
    EXPECT_TRUE(physics.getBallData(LogicValues().Y_VELOCITY) != 0);
}

TEST(physics, seAgregaJugadorCorrectamente) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);

    EXPECT_EQ(physics.playersAmount(), 1);
}
TEST(physics, seAgreganVariosJugadoresCorrectamente) {
    BoxLogic physics;

    physics.addPlayer(PLAYER_ID);
    physics.addPlayer(PLAYER_ID_2);
    physics.addPlayer(PLAYER_ID_3);
    physics.addPlayer(PLAYER_ID_4);

    EXPECT_EQ(physics.playersAmount(), 4);
}

TEST(physics, sePosicionaAutoCorrectamente) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    physics.updateTime();

    EXPECT_EQ(physics.getCarData(PLAYER_ID,LogicValues().POS_X), 2);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) != 0);
}

TEST(physics, aceleracionCorrectaConComando) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    for(int i = 0; i < 100; i++){ // Actualizo tiempo hasta que pueda saltar (Tiene que estar en el suelo y aparece cayendo)
        physics.updateTime();
    }
    EXPECT_TRUE(physics.getCarData(PLAYER_ID, LogicValues().X_VELOCITY) == 0);
    physics.startMove(PLAYER_ID,LogicValues().LEFT_DIRECTION); // Le aplica una fuerza, no le setea una velocidad.
    physics.updateTime();
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) != 0);
}

TEST(physics, FrenoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    physics.startMove(PLAYER_ID,LogicValues().LEFT_DIRECTION);
    physics.stopMove(PLAYER_ID);
    EXPECT_EQ(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY), 0);
}

TEST(physics, SaltoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    for(int i = 0; i < 100; i++){ // Actualizo tiempo hasta que pueda saltar (Tiene que estar en el suelo y aparece cayendo)
        physics.updateTime();
    }
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) == 0);
    physics.jump(PLAYER_ID);
    physics.updateTime();

    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) < 0);
}

TEST(physics, MueveAnguloEnElAire) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().ANGLE) == 0);
    physics.startMove(PLAYER_ID,LogicValues().LEFT_DIRECTION);
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().ANGLE) != 0);

}

TEST(physics, DobleSaltoCorrecto) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics, 100);

    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) == 0);

    physics.jump(PLAYER_ID);
    update(physics, 1);

    float vel1 = physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) < 0);
    physics.jump(PLAYER_ID);
    update(physics, 1);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) < vel1);
}

TEST(physics, RealizaTresSaltosYELUltimoNoCuenta) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics,100);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) == 0);
    physics.jump(PLAYER_ID);
    update(physics, 5);

    float vel1 = physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) < 0);
    physics.jump(PLAYER_ID);
    update(physics,5);

    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) < vel1);
    float vel2 = physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY);
    physics.jump(PLAYER_ID);
    update(physics,5);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) > vel2);
}

TEST(physics, RealizaUnTurbo) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics,100);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) == 0);

    physics.startMove(PLAYER_ID,LogicValues().LEFT_DIRECTION);
    update(physics,1);
    float vel1 = physics.getCarData(PLAYER_ID, LogicValues().X_VELOCITY);
    physics.applyTurbo(PLAYER_ID);

    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) < vel1);
}

TEST(physics, RealizaUnTurboPorVariosSegundos) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics,100);

    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) == 0);
    for(int i = 0; i < 30; i++) {
        physics.startMove(PLAYER_ID,LogicValues().LEFT_DIRECTION);
        update(physics,1);
    }
    for(int i = 0; i < 40; i++) {
        physics.applyTurbo(PLAYER_ID);
        update(physics,1);
    }
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().TURBO_TANK) < 1);
}

TEST(physics, ElAutoTieneAcelearacion) {
    BoxLogic physics;
    physics.addPlayer(PLAYER_ID);
    update(physics,100);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) == 0);
    physics.startMove(PLAYER_ID, LogicValues().LEFT_DIRECTION);
    EXPECT_TRUE(physics.getCarData(PLAYER_ID,LogicValues().ACCELERATING));
    update(physics,1);
    EXPECT_FALSE(physics.getCarData(PLAYER_ID,LogicValues().ACCELERATING));
}


TEST(response, RespuestaCorrecta) {
    GameLogic logic;
    logic.updateTime();
    Response response = logic.getResponse();
    EXPECT_TRUE(response.getBallPositionY() > -2.8); // PosY inicial pelota
}
