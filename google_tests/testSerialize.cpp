#include "gtest/gtest.h"
#include "../src/protocolo/responses/match_response.h"
#include "../src/protocolo/responses/response.h"
#include <iostream>

void printBytes(std::vector<char> &responseSerialized){
    for(auto x: responseSerialized){
        std::cout << std::hex << (int)x << std::endl;
    }
}

void serializeString(){
    std::vector<char> aux;
    std::string name = "exampleName";
    for(auto x: name){
        aux.push_back(x);
    }
}

/*
 * Por ahora se serializa...
 *  1 byte GolesLocal
 *  1 byte GolesVisitante
 *  1 byte JugadoresRequeridos
 *  1 byte JugadoresActuales
 *  1 byte Si esta esperandoJugadores
 *  1 byte Si la partida terminó
 *  1 byte si hay gol local
 *  1 byte si hay gol visitante
 *  1 byte si la replay está activada
 *  1 byte sobre el tamaño del string del nombre de la partida
 *  N bytes del nombre de la partida
 */

TEST(Serialize, seSeteanLosGoles) {
    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);

    EXPECT_EQ(response.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanLosJugadores) {

    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<unsigned char> responseSerialized = response.serialize();

    EXPECT_EQ(responseSerialized.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanLosEstados) {

    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<unsigned char> responseSerialized = response.serialize();
    serializeString();

    EXPECT_EQ(responseSerialized.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanTodosLosDatos) {

    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<unsigned char> responseSerialized = response.serialize();

    // printBytes(responseSerialized);
    EXPECT_EQ(responseSerialized.size(), 27 );
}

TEST(Serializacion, SerializePlayerId) {
    int test = 10;

    PlayerResponse response(test, 0, 0, 0, false, false, false, false, false, false);

    std::vector<unsigned char> serialized = response.serialize();

    int result = PlayerResponse(serialized).getId();

    EXPECT_EQ(test, result);
}

TEST(Serializacion, SerializePlayerPositionX) {
    float test = 10.93f;

    PlayerResponse response(0, test, 0, 0, false, false, false, false, false, false);

    std::vector<unsigned char> serialized = response.serialize();

    PlayerResponse responseDeserialized(serialized);

    EXPECT_EQ(test, responseDeserialized.getPosX());
}

TEST(Serializacion, SerializeBallResponse) {
    float test = 10.93f;

    BallResponse response(0, test, 0, false, false, false);

    std::vector<unsigned char> serialized = response.serialize();

    BallResponse responseDeserialized(serialized);

    EXPECT_EQ(test, responseDeserialized.getPosY());
    EXPECT_EQ(0, responseDeserialized.getPosX());
    EXPECT_EQ(0, responseDeserialized.getRotationAngle());
    EXPECT_EQ(false, responseDeserialized.getIsFlying());
    EXPECT_EQ(false, responseDeserialized.getHasBeenPunched());
    EXPECT_EQ(false, responseDeserialized.getIsMoving());
}

TEST(Serializacion, SerializarString) {
    std::string prueba = "nombre de prueba";

    Serializer serializer;

    std::vector<unsigned char> serializado = serializer.serializeString(prueba);

    std::string deserializado = serializer.deserializeString(serializado);

    EXPECT_EQ(prueba, deserializado);
}

TEST(Serializacion, SerializarStringConParse) {
    std::string prueba = "nombre de prueba";
    std::string resultado;
    int inicio = 0;
    int fin = 0;

    Serializer serializer;

    std::vector<unsigned char> serializado = serializer.serializeString(prueba);

    serializer.parse(resultado, serializado, inicio, fin);

    EXPECT_EQ(prueba, resultado);
}

TEST(Serializacion, SerializarPartida) {
    BallResponse ball(1, 0, 1, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false);
    PlayerResponses players;
    players.addPlayer(player);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    MatchResponses partidas;
    MatchResponses partidas2;
    partidas.addResponse(partida);
    partidas2.addResponse(partida);
    Response r(partidas);

    EXPECT_EQ(r.getSize(), partidas2.size());
}

TEST(Serializacion, SerializarYDeserializarPartida) {
    BallResponse ball(1, 0, 1, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false);
    PlayerResponses players;
    players.addPlayer(player);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    MatchResponses partidas;
    partidas.addResponse(partida);
    Response r(partidas);

    std::vector<unsigned char> serializacion = r.serialize();

    Response deserializada(serializacion);

    EXPECT_EQ(r.serialize().size(), deserializada.serialize().size());
}

TEST(Serializacion, SerializacionYDeserializacionConLobby) {
    LobbyResponse lobbyResponse;
    std::string nombre = "nombre";
    RoomResponse room(nombre, 3, 2, false, false, true);
    room.addClient(1);
    room.addClient(2);
    lobbyResponse.addRoom(room);
    BallResponse ball(1, 0, 1, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false);
    PlayerResponse player1(3, 0, 1, 0, false, false, false, true, false, false);
    PlayerResponses players;
    players.addPlayer(player);
    players.addPlayer(player1);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    MatchResponses partidas;
    partidas.addResponse(partida);
    Response r(partidas);
    r.addLobbyResponse(lobbyResponse);
    std::vector<unsigned char> serializacion = r.serialize();

    Response deserializada(serializacion);

    EXPECT_EQ(r.serialize().size(), deserializada.serialize().size());
}

