#include <thread>
#include <vector>
#include <sys/socket.h>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"
#include "../src/constants/response_values.h"
#include "../src/exceptions/socket_closed_exception.h"

const char* serv = "8080";

void receiveCommand(std::condition_variable &cv, Command &c, bool &isServerUp) {
    Socket server(serv);
    isServerUp = true;
    cv.notify_all();

    Socket client = server.accept();
    Protocolo p;
    for (int i = 0; i < 3; ++i) {
        try {
            c = p.receiveCommand(client);
        } catch (SocketClosedException &e) {
            //
        }
    }
}

void receiveResponse(Response &response) {
    Socket client("localhost", serv);
    Protocolo p;

    for (int i = 0; i < 3; ++i) {
        try {
            response = p.receiveResponse(client);
        } catch (SocketClosedException &e) {
            //
        }
    }
}

void sendCommands(std::vector<std::string> &values) {
    Socket client("localhost", serv);
    Protocolo p;

    for (auto &value : values) {
        Command command = ProtocolCommands().createCommand(1, value);
        try {
            p.sendCommand(client, command);
        } catch (SocketClosedException &e) {
            break;
        }
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
    BallResponse ball(0, 0, 0, false, false, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse matchResponse(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response response(matchResponse);
    response.addLobbyResponse(lobbyResponse);

    Socket server(serv);

    Response receivedResponse;
    std::thread clientThread(&receiveResponse, std::ref(receivedResponse));

    Socket connectedClient = server.accept();

    for (int i = 0; i < 3; i++) {
        Protocolo().sendResponse(connectedClient, response);
    }

    clientThread.join();

    EXPECT_EQ(receivedResponse.serialize().size(), response.serialize().size());
    EXPECT_EQ(receivedResponse.getMatchResponse().getPlayersResponse().getPlayers().front().getRemainingTurbo(),
              response.getMatchResponse().getPlayersResponse().getPlayers().front().getRemainingTurbo());
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

TEST(Protocolo, DesconectoAlClienteYSeEsperaExcepcionAlIntentarEnviarRespuesta) {
    Protocolo p;
    ActionResultResponse actionResult(ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyResponse(actionResult);
    std::string nombre = "nombre";
    RoomResponse room(nombre, 3, 2, false, false, true);
    room.addClient(1);
    room.addClient(2);
    lobbyResponse.addRoom(room);
    BallResponse ball(0, 0, 0, false, false, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse matchResponse(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response response(matchResponse);
    response.addLobbyResponse(lobbyResponse);

    Socket server(serv);

    Response receivedResponse;
    std::thread clientThread(&receiveResponse, std::ref(receivedResponse));

    Socket connectedClient = server.accept();

    for (int i = 0; i < 3; i++) {
        p.sendResponse(connectedClient, response);
    }

    clientThread.join();

    connectedClient.shutdown(SHUT_RDWR);
    connectedClient.close();
    try {
        p.sendResponse(connectedClient, response);
    } catch (SocketClosedException &e) {
        //
    }

    p.sendResponse(connectedClient, response);

    Command c = p.receiveCommand(connectedClient);

    EXPECT_TRUE(p.isConnectionClosed());
}

TEST(Protocolo, DesconectoElServidorYSeEsperaExcepcionAlRecibirComando) {
    Socket server(serv);
    std::vector<std::string> values{
        CommandValues().DESERIALIZED_LEFT_RELEASE,
        CommandValues().DESERIALIZED_LEFT_RELEASE,
        CommandValues().DESERIALIZED_LEFT_RELEASE
    };

    std::thread clientThread(&sendCommands, std::ref(values));

    Socket client = server.accept();

    Protocolo p;
    for (int i = 0; i < 3; ++i) {
        if (i == 1) {
            client.shutdown(SHUT_RDWR);
            client.close();
            try {
                Command c = p.receiveCommand(client);
            } catch (SocketClosedException &e) {
                //
            }
            continue;
        }
        Command c = p.receiveCommand(client);
    }

    clientThread.join();

    EXPECT_TRUE(p.isConnectionClosed());
}

TEST(Protocolo, ClienteSeDesconectaDelServidorySeEsperaExcepcionAlEnviarComando) {
    bool serverUp = false;
    std::condition_variable cv; // server up?
    std::mutex m;
    std::string value = CommandValues().DESERIALIZED_NOP;
    unsigned char serialized = CommandValues().SERIALIZED_NOP;
    Command c(0, serialized, value);

    std::thread serverThread(&receiveCommand, std::ref(cv), std::ref(c), std::ref(serverUp));

    std::unique_lock<std::mutex> l(m);

    while (!serverUp) {
        cv.wait(l);
    }

    Socket client("localhost", serv);

    Protocolo p;
    std::string value1 = CommandValues().DESERIALIZED_LEFT_RELEASE;
    unsigned char serialized1 = CommandValues().SERIALIZED_LEFT_RELEASE;
    Command c1(0, serialized1, value1);
    for (int i = 0; i < 3; ++i) {
        if (i == 1) {
            client.shutdown(SHUT_RDWR);
            client.close();
            try {
                p.sendCommand(client, c1);
            } catch (SocketClosedException &e) {
                //
            }
            continue;
        }
        p.sendCommand(client, c1);
    }

    serverThread.join();

    Response r = p.receiveResponse(client);

    EXPECT_EQ(r.getStatus(), ResponseValues().ERROR);

    EXPECT_TRUE(p.isConnectionClosed());
}