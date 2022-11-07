#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"
#include "../src/logic/boxLogic.h"
#include <iostream>


TEST(logic, SeCreaElMapaConGravedad10) {
    b2Vec2 v(0.0f,9.8f);
    BoxLogic physics;


    EXPECT_EQ(physics.getGravity(), v);
    physics.close(); // Sino queda el thread del tiempo corriendo
}

TEST(logic, SeCreanCorrectamenteLasParedes) {
    BoxLogic physics;

    EXPECT_EQ(physics.wallsAmount(), 4);
    physics.close();
}

TEST(logic, SeCreaCorrectamenteLaPelota) {
    BoxLogic physics;
    EXPECT_EQ(physics.ballIsAwake(), true);
    physics.close();
}

TEST(logic, movimientoCorrectoDePelota) {
    BoxLogic physics;

    sleep(1); // Simulo el paso del tiempo

    EXPECT_EQ(physics.getBallData(0), 0);
    EXPECT_TRUE(physics.getBallData(4) != 0);
    physics.close();
}

TEST(logic, seAgregaJugadorCorrectamente) {
    BoxLogic physics;

    physics.addPlayer();
    sleep(1);
    EXPECT_EQ(physics.playersAmount(), 1);
    physics.close();
}
TEST(logic, seAgreganVariosJugadoresCorrectamente) {
    BoxLogic physics;

    physics.addPlayer();
    sleep(1);
    physics.addPlayer();
    sleep(1);
    physics.addPlayer();
    sleep(1);
    physics.addPlayer();
    sleep(1);

    EXPECT_EQ(physics.playersAmount(), 4);
    physics.close();
}

TEST(logic, sePosicionaAutoCorrectamente) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(1);


    EXPECT_EQ(physics.getCarData(1,0), 2);
    EXPECT_TRUE(physics.getCarData(1,4) != 0);
    physics.close();
}

TEST(logic, aceleracionCorrectaConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(1);
    physics.startMove(1,0);
    sleep(1);
    EXPECT_TRUE(physics.getCarData(1,3) != 0);
    physics.close();
}

TEST(logic, FrenoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(1);
    physics.startMove(1,0);
    sleep(1);
    physics.stopMove(1); // Chequear velocidad lineal
    sleep(1);
    EXPECT_TRUE(physics.getCarData(1,3) == 0);
    physics.close();
}

TEST(logic, SaltoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(5);
    physics.jump(1);
    sleep(1);
    EXPECT_TRUE(physics.getCarData(1,4) < 0);
    physics.close();
}