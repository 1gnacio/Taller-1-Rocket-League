#include <thread>
#include <vector>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"
#include "../src/constants/response_values.h"

const char* serv = "8080";

void receiveResponse(Response &response) {
    Socket client("localhost", serv);

    for (int i = 0; i < 3; i++) {
        response = Protocolo().receiveResponse(client);
    }
}

void sendCommands(std::vector<std::string> &values) {
    Socket client("localhost", serv);

    for (auto &value : values) {
        Command command = ProtocolCommands().createCommand(1, value);

        Protocolo().sendCommand(client, command);
    }
}

void receiveId(int &id) {
    Socket client("localhost", serv);

    for (int i = 0; i < 3; i++) {
        id = Protocolo().receiveId(client);
    }
}

TEST(Protocolo, ClienteEnviaTodosLosComandosDisponiblesYElServidorLosRecibe) {
    Socket server(serv);
    CommandValues values;
    std::vector<std::string> deserializedCommands({
                               values.DESERIALIZED_NOP,
                               values.DESERIALIZED_UP_PUSHED,
                               values.DESERIALIZED_UP_RELEASE,
                               values.DESERIALIZED_DOWN_PUSHED,
                               values.DESERIALIZED_DOWN_RELEASE,
                               values.DESERIALIZED_LEFT_PUSHED,
                               values.DESERIALIZED_LEFT_RELEASE,
                               values.DESERIALIZED_RIGHT_PUSHED,
                               values.DESERIALIZED_RIGHT_RELEASE,
                               values.DESERIALIZED_TURBO_RELEASE,
                               values.DESERIALIZED_TURBO_PUSHED,
                               values.DESERIALIZED_JUMP_RELEASE,
                               values.DESERIALIZED_JUMP_PUSHED,
                               values.DESERIALIZED_LIST,
                               values.DESERIALIZED_CREATE,
                               values.DESERIALIZED_JOIN,
                               values.DESERIALIZED_QUIT_MATCH,
                               values.DESERIALIZED_QUIT_GAME
                       });

    std::thread clientThread(&sendCommands, std::ref(deserializedCommands));

    std::vector<std::string> receivedValues;

    Socket connectedClient = server.accept();

    for (auto &value : deserializedCommands) {
        Command c = Protocolo().receiveCommand(connectedClient);

        receivedValues.push_back(c.getValue());

        EXPECT_EQ(receivedValues.back(), value);
    }

    clientThread.join();
}

TEST(Protocolo, ServidorEnviaRespuestaDeJugadoresYElClienteLaRecibe) {
    ActionResultResponse actionResult(ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyResponse(actionResult);
    std::string nombre = "nombre";
    RoomResponse room(nombre, 3, 2, false, false, true);
    room.addClient(1);
    room.addClient(2);
    lobbyResponse.addRoom(room);
    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse matchResponse(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<MatchResponse> responses{matchResponse};
    MatchResponses matchResponses(responses);
    Response response(matchResponses);
    response.addLobbyResponse(lobbyResponse);

    Socket server(serv);

    Response receivedResponse;
    std::thread clientThread(&receiveResponse, std::ref(receivedResponse));

    Socket connectedClient = server.accept();

    for (int i = 0; i < 3; i++) {
        Protocolo().sendResponse(connectedClient, response);
    }

    clientThread.join();

    EXPECT_EQ(receivedResponse.serialize(), response.serialize());
}

TEST(Protocolo, ClienteSeConectaYRecibeId) {
    int id = 3;
    int receivedId = 0;
    Socket server(serv);

    std::thread clientThread(&receiveId, std::ref(receivedId));

    Socket connectedClient = server.accept();

    for (int i = 0; i < 3; i++) {
        Protocolo().sendId(connectedClient, id);
    }

    clientThread.join();

    EXPECT_EQ(receivedId, id);

}