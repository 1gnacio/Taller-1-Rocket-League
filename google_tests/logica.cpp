#include <thread>
#include "gtest/gtest.h"
#include "../src/protocolo/commands/command.h"
#include "../src/logic/boxLogic.h"
#include "../src/logic/gameLogic.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/game_model/game_model.h"

static const int PLAYER_ID = 50;

TEST(logic, SeCreaElMapaCorrectamente) {
    GameLogic logic(1, "nombre");
    logic.getResponse().getBallPositionY();
    EXPECT_EQ(logic.getResponse().getBallPositionY(), -2.8f);
    logic.updateTime();
    EXPECT_TRUE(logic.getResponse().getBallPositionY() > -2.8f);
}

TEST(logic, SeAniadeAutoCorrectamente) {
    ServerEndpoint endpoint;
    CompleteGame game(1, 2, "prueba", endpoint);
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_JOIN;
    std::string name = "prueba";
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized, name);
    game.applyCommand(c);
    game.updateTime();
    EXPECT_EQ(game.list().getPlayers(), "1");
}

TEST(logic, SeMueveElAutoCorrectamente) {
    ServerEndpoint endpoint;
    CompleteGame game(1, 2, "prueba", endpoint);
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_JOIN;
    std::string name = "prueba";
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized, deserialized, name);
    game.applyCommand(c);
    game.updateTime();

    ASSERT_TRUE(game.getResponse().getMatchResponse().getPlayersResponse().getPlayers().front().moving());
    deserialized = CommandValues().DESERIALIZED_RIGHT_PUSHED;
    c = makeCommands.createCommand(PLAYER_ID, deserialized);
    game.applyCommand(c);
    game.updateTime();

    ASSERT_TRUE(game.getResponse().getMatchResponse().getPlayersResponse().getPlayers().front().moving());
}

TEST(logic, elAutoSaltaCorrectamente) {
    ServerEndpoint endpoint;
    CompleteGame game(1, 2, "prueba", endpoint);
    ProtocolCommands makeCommands;
    std::string deserialized = CommandValues().DESERIALIZED_JOIN;
    std::string name = "prueba";
    Command c = makeCommands.createCommand(PLAYER_ID, deserialized, name);
    game.applyCommand(c);
    game.updateTime();

    ASSERT_TRUE(game.getResponse().getMatchResponse().getPlayersResponse().getPlayers().front().flying());
    deserialized = CommandValues().DESERIALIZED_JUMP_PUSHED;
    c = makeCommands.createCommand(PLAYER_ID, deserialized);
    game.applyCommand(c);
    game.updateTime();

    ASSERT_TRUE(game.getResponse().getMatchResponse().getPlayersResponse().getPlayers().front().flying());
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
