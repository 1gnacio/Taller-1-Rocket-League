#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"
#include "../src/constants/logic_values.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/protocol_commands.h"

static const int PLAYER_ID = 50;

static void update(GameLogic &logic, int frames) {
    for (int i = 0; i < frames; i ++) {
        logic.updateTime();
    }
}

TEST(logic, SeCreaElMapaCorrectamente) {
    GameLogic logic;
    logic.getResponse().getBallPositionY();
    EXPECT_EQ(logic.getResponse().getBallPositionY(), -2.8f);
    logic.updateTime();
    EXPECT_TRUE(logic.getResponse().getBallPositionY() > -2.8f);
}

TEST(logic, SeAñadeAutoCorrectamente) {
    GameLogic logic;
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.updateModel(c);
    update(logic, 100);
    EXPECT_EQ(logic.playersAmount(), 1);
}

TEST(logic, SeMueveElAutoCorrectamente) {
    GameLogic logic;
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.updateModel(c);
    update(logic, 100);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) == 0);
    deserialized = CommandValues().DESERIALIZED_RIGHT_PUSHED;
    c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.updateModel(c);
    update(logic, 1);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().X_VELOCITY) != 0);
}

TEST(logic, elAutoSaltaCorrectamente) {
    GameLogic logic;
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_TURBO_RELEASE;
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.updateModel(c);
    update(logic, 100);


    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) == 0);
    deserialized = CommandValues().DESERIALIZED_JUMP_PUSHED;
    c = makeCommands.createCommand(PLAYER_ID, deserialized);
    logic.updateModel(c);
    update(logic, 1);

    EXPECT_TRUE(logic.getCarData(PLAYER_ID,LogicValues().Y_VELOCITY) != 0);
}


