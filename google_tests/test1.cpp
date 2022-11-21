#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"

const char* serv = "8080";

void sendCommand(std::string& command) {
    Socket client("localhost", serv);

    Command c = ProtocolCommands().createCommand(1, command);

    Protocolo().sendCommand(client, c);
}

void receiveId(int &receivedId) {
    Socket client("localhost", serv);

    receivedId = Protocolo().receiveId(client);
}

void sendResponse(Response& response) {
    Socket server(serv);

    Socket connectedClient = server.accept();

    Protocolo().sendResponse(connectedClient, response);
}

TEST(Protocolo, ClienteEnviaIzquierdaPresionada) {
    Socket server(serv);

    std::string value = CommandValues().DESERIALIZED_LEFT_PUSHED;

    std::thread clientHandler(&sendCommand, std::ref(value));

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_LEFT_PUSHED);
}

TEST(Protocolo, ClienteEnviaNoOperation) {
    Socket server(serv);

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

    Socket client("localhost", serv);

    Response r = Protocolo().receiveResponse(client);

    serverHandler.join();

    EXPECT_EQ(r.getSize(), response.getSize());
}

TEST(Protocolo, ClienteSeConectaYRecibeId) {
    Socket server(serv);

    int receivedId = 0;

    std::thread clientHandler(&receiveId, std::ref(receivedId));

    Socket connectedClient = server.accept();

    int id = 3;

    Protocolo().sendId(connectedClient, id);

    clientHandler.join();

    EXPECT_EQ(receivedId, id);
}