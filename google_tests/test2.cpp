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