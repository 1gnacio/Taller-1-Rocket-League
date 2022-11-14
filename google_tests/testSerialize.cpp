#include "gtest/gtest.h"
#include "../src/protocolo/responses/match_response.h"
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


