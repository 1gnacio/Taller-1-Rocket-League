#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"

void sendCommand(std::string& command) {
    Socket client("localhost", "8080");

    Command c = ProtocolCommands().createCommand(command);

    Protocolo().sendCommand(client, c);
}

void sendResponse(Response& response) {
    Socket server("8080");

    Socket connectedClient = server.accept();

    Protocolo().sendResponse(connectedClient, response);
}

TEST(Protocolo, ClienteEnviaIzquierdaPresionada) {
    Socket server("8080");

    std::string value = CommandValues().DESERIALIZED_LEFT_PUSHED;

    std::thread clientHandler(&sendCommand, std::ref(value));

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_LEFT_PUSHED);
}

TEST(Protocolo, ClienteEnviaNoOperation) {
    Socket server("8080");

    std::string value = CommandValues().DESERIALIZED_NOP;

    std::thread clientHandler(&sendCommand, std::ref(value));

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_NOP);
}

TEST(Protocolo, ServidorEnviaRespuestaDeJugadores) {
    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse matchResponse(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<MatchResponse> responses{matchResponse};
    MatchResponses matchResponses(responses);
    Response response(matchResponses);

    std::thread serverHandler(&sendResponse, std::ref(response));

    Socket client("localhost", "8080");

    Response r = Protocolo().receiveResponse(client);

    serverHandler.join();

    EXPECT_EQ(r.getStatus(), "");
}