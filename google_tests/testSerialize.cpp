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

MatchResponse response;
std::string name = "nombre";
response.setGoals(2,3);
response.setName(name);
std::vector<char> responseSerialized = response.serialize();

EXPECT_EQ(responseSerialized.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanLosJugadores) {

    MatchResponse response;
    std::string name = "nombre";
    response.setName(name);
    response.setPlayers(4,3);
    std::vector<char> responseSerialized = response.serialize();

    EXPECT_EQ(responseSerialized.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanLosEstados) {

    MatchResponse response;
    std::string name = "nombre";
    response.setName(name);
    response.setStates(0,0,0,0,0);
    std::vector<char> responseSerialized = response.serialize();
    serializeString();

    EXPECT_EQ(responseSerialized.size(), 16 ); // Cada gol es 1 byte (uint8_t)
}

TEST(Serialize, seSeteanTodosLosDatos) {

    MatchResponse response;
    std::string name = "nombre de partida";
    response.setName(name);
    response.setStates(0,0,0,0,0);
    response.setPlayers(4,3);
    response.setGoals(0,0);

    std::vector<char> responseSerialized = response.serialize();
    // printBytes(responseSerialized);
    EXPECT_EQ(responseSerialized.size(), 27 );
}


