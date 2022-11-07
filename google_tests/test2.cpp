#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"
#include "../src/logic/boxLogic.h"
#include "../src/constants/logic_values.h"

const int FIRST_CAR = 1;
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

    EXPECT_EQ(physics.getBallData(LogicValues().POS_X), 0);
    EXPECT_TRUE(physics.getBallData(LogicValues().Y_VELOCITY) != 0);
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


    EXPECT_EQ(physics.getCarData(FIRST_CAR,LogicValues().POS_X), 2);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) != 0);
    physics.close();
}

TEST(logic, aceleracionCorrectaConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(1);
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    sleep(1);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY) != 0);
    physics.close();
}

TEST(logic, FrenoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(1);
    physics.startMove(FIRST_CAR,LogicValues().LEFT_DIRECTION);
    sleep(1);
    physics.stopMove(FIRST_CAR); // Chequear velocidad lineal
    sleep(1);
    EXPECT_EQ(physics.getCarData(FIRST_CAR,LogicValues().X_VELOCITY), 0);
    physics.close();
}

TEST(logic, SaltoCorrectoConComando) {
    BoxLogic physics;
    physics.addPlayer();
    sleep(5);
    physics.jump(FIRST_CAR);
    sleep(1);
    EXPECT_TRUE(physics.getCarData(FIRST_CAR,LogicValues().Y_VELOCITY) < 0);
    physics.close();
}