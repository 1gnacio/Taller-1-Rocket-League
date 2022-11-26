#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"
#include "../src/constants/logic_values.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/game_model/game_model.h"

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

TEST(logic, EnviarComandoQuitMatchBorraAlJugador) {
    ServerEndpoint endpoint;
    GameModel model(endpoint);
    std::string createValue = CommandValues().DESERIALIZED_CREATE;
    std::string maxPlayers = std::to_string(2);
    std::string name = "ABC";
    Command create = ProtocolCommands().createCommand(1, createValue, maxPlayers, name);
    model.applyLogic(create);
    Response r0 = model.getResponse().front();

    EXPECT_EQ(r0.isRecipient(1), true);

    std::string quitValue = CommandValues().DESERIALIZED_QUIT_MATCH;
    Command quit = ProtocolCommands().createCommand(1, quitValue, name);
    model.applyLogic(quit);
    Response r = model.getResponse().front();

    EXPECT_EQ(r.isRecipient(1), false);
}

TEST(logic, EnviarComandoQuitMatchBorraAlJugadorEnPartidaDeDosJugadores) {
    ServerEndpoint endpoint;
    GameModel model(endpoint);
    std::string createValue = CommandValues().DESERIALIZED_CREATE;
    std::string maxPlayers = std::to_string(2);
    std::string name = "ABC";
    Command create = ProtocolCommands().createCommand(1, createValue, maxPlayers, name);
    model.applyLogic(create);
    Response r0 = model.getResponse().front();

    EXPECT_EQ(r0.isRecipient(1), true);
    EXPECT_EQ(r0.isRecipient(2), false);

    std::string joinValue = CommandValues().DESERIALIZED_JOIN;
    Command join = ProtocolCommands().createCommand(2, joinValue, name);
    model.applyLogic(join);
    Response r1 = model.getResponse().front();

    EXPECT_EQ(r1.isRecipient(1), true);
    EXPECT_EQ(r1.isRecipient(2), true);

    std::string quitValue = CommandValues().DESERIALIZED_QUIT_MATCH;
    Command quit = ProtocolCommands().createCommand(1, quitValue, name);
    model.applyLogic(quit);
    Response r = model.getResponse().front();

    EXPECT_EQ(r.isRecipient(1), false);
    EXPECT_EQ(r.isRecipient(2), true);
}
