#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"
#include "../src/constants/logic_values.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/protocol_commands.h"

static const int PLAYER_ID = 50;

static void update(BoxLogicMonitor &logic, int frames) {
    for (int i = 0; i < frames; i ++) {
        logic.updateTime();
    }
}

TEST(logic, SeCreaElMapaCorrectamente) {
    BoxLogicMonitor logic;
    logic.getBallResponse().getPosY();
    EXPECT_EQ(logic.getBallResponse().getPosY(), -2.8f);
    logic.updateTime();
    EXPECT_TRUE(logic.getBallResponse().getPosY() > -2.8f);
}

TEST(logic, SeAñadeAutoCorrectamente) {
    GameLogic logic(1, "nombre");
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.push(c);
    EXPECT_EQ(logic.playersAmount(), 1);
}

TEST(logic, SeMueveElAutoCorrectamente) {
    GameLogic logic(1, "nombre");
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.push(c);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) == 0);
    deserialized = CommandValues().DESERIALIZED_RIGHT_PUSHED;
    c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.push(c);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) != 0);
}

TEST(logic, elAutoSaltaCorrectamente) {
    GameLogic logic(1, "nombre");
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.push(c);


    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) == 0);
    deserialized = CommandValues().DESERIALIZED_JUMP_PUSHED;
    c = makeCommands.createCommand(1, deserialized);
    logic.push(c);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) != 0);
}


