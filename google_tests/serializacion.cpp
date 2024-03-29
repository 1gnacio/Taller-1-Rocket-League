#include "gtest/gtest.h"
#include "../src/protocolo/responses/match_response.h"
#include "../src/protocolo/responses/response.h"
#include "../src/constants/response_values.h"

TEST(Serialize, seSeteanLosGoles) {
    BallResponse ball(0, 0, 0, false, false, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response r(response);

    std::vector<unsigned char> serializada = r.serialize();

    Response deserializada(serializada);

    EXPECT_EQ(r.getMatchResponse().getLocalGoals(),
              deserializada.getMatchResponse().getLocalGoals());
    EXPECT_EQ(r.getMatchResponse().getVisitorsGoals(),
              deserializada.getMatchResponse().getVisitorsGoals());
}

TEST(Serialize, seSeteanLosJugadores) {

    BallResponse ball(0, 0, 0, false, false, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response r(response);

    std::vector<unsigned char> responseSerialized = r.serialize();

    Response deserializada(responseSerialized);

    EXPECT_EQ(r.getMatchResponse().getPlayersResponse().getPlayers().front().getId(),
              deserializada.getMatchResponse().getPlayersResponse().getPlayers().front().getId());
    EXPECT_EQ(r.getMatchResponse().getPlayersResponse().getPlayers().front().getPosY(),
              deserializada.getMatchResponse().getPlayersResponse().getPlayers().front().getPosY());
    EXPECT_EQ(r.getMatchResponse().getPlayersResponse().getPlayers().front().getRotationAngle(),
              deserializada.getMatchResponse().getPlayersResponse().getPlayers().front().getRotationAngle());
    EXPECT_EQ(r.getMatchResponse().getPlayersResponse().getPlayers().front().getPosX(),
              deserializada.getMatchResponse().getPlayersResponse().getPlayers().front().getPosX());

}

TEST(Serialize, seSeteanLosEstadosDeLaPelota) {

    BallResponse ball(0, 0, 0, false, true, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse match(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response serializar(match);
    std::vector<unsigned char> responseSerialized = serializar.serialize();

    Response deserializada(responseSerialized);

    EXPECT_EQ(deserializada.getMatchResponse().getBall().getIsMoving(), false);
    EXPECT_EQ(deserializada.getMatchResponse().getBall().getIsFlying(), true);
    EXPECT_EQ(deserializada.getMatchResponse().getBall().getHasBeenPunched(), true);
}

TEST(Serialize, seSeteanTodosLosDatos) {

    BallResponse ball(0, 0, 0, false, false, false, true, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse response(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    Response r(response);

    std::vector<unsigned char> responseSerialized = r.serialize();

    Response deserializada(responseSerialized);

    EXPECT_EQ(r.serialize().size(), deserializada.serialize().size() );
}

TEST(Serializacion, SerializePlayerId) {
    int test = 10;

    PlayerResponse response(test, 0, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);

    std::vector<unsigned char> serialized = response.serialize();

    int result = PlayerResponse(serialized).getId();

    EXPECT_EQ(test, result);
}

TEST(Serializacion, SerializePlayerPositionX) {
    float test = 10.93f;

    PlayerResponse response(0, test, 0, 0, false, false, false, false, false, false, 0, 1, 0, false, 0.5f);

    std::vector<unsigned char> serialized = response.serialize();

    PlayerResponse responseDeserialized(serialized);

    EXPECT_EQ(test, responseDeserialized.getPosX());
}

TEST(Serializacion, SerializeBallResponse) {
    float test = 10.93f;

    BallResponse response(0, test, 0, false, false, false, true, false, false, false);

    std::vector<unsigned char> serialized = response.serialize();

    BallResponse responseDeserialized(serialized);

    EXPECT_EQ(test, responseDeserialized.getPosY());
    EXPECT_EQ(0, responseDeserialized.getPosX());
    EXPECT_EQ(0, responseDeserialized.getRotationAngle());
    EXPECT_EQ(false, responseDeserialized.getIsFlying());
    EXPECT_EQ(true, responseDeserialized.getHasBeenPunched());
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
    BallResponse ball(1, 0, 1, false, false, false, true, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponses players;
    players.addPlayer(player);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    MatchResponses partidas;
    MatchResponses partidas2;
    partidas.addResponse(partida);
    partidas2.addResponse(partida);

    EXPECT_EQ(partidas.serialize(), partidas2.serialize());
}

TEST(Serializacion, SerializarYDeserializarPartida) {
    BallResponse ball(1, 0, 1, false, false, false, true, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponses players;
    players.addPlayer(player);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    Response r(partida);

    std::vector<unsigned char> serializacion = r.serialize();

    Response deserializada(serializacion);

    EXPECT_EQ(r.serialize(), deserializada.serialize());
}

TEST(Serializacion, SerializacionYDeserializacionConLobby) {
    LobbyResponse lobbyResponse;
    std::string nombre = "nombre";
    RoomResponse room(nombre, 3, 2, false, false, true);
    room.addClient(1);
    room.addClient(2);
    lobbyResponse.addRoom(room);
    BallResponse ball(1, 0, 1, false, false, false, true, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponse player1(3, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponses players;
    players.addPlayer(player);
    players.addPlayer(player1);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    Response r(partida);
    r.addLobbyResponse(lobbyResponse);
    std::vector<unsigned char> serializacion = r.serialize();

    Response deserializada(serializacion);

    EXPECT_EQ(r.serialize().size(), deserializada.serialize().size());
}

TEST(Serializacion, SerializacionYDeserializacionConLobbyYResultadoDeAccion) {
    ActionResultResponse actionResult(ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyResponse(actionResult);
    std::string nombre = "nombre";
    RoomResponse room(nombre, 3, 2, false, false, true);
    room.addClient(1);
    room.addClient(2);
    lobbyResponse.addRoom(room);
    BallResponse ball(1, 0, 1, false, false, false, true, false, false, false);
    PlayerResponse player(1, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponse player1(3, 0, 1, 0, false, false, false, true, false, false, 0, 1, 0, false, 0.5f);
    PlayerResponses players;
    players.addPlayer(player);
    players.addPlayer(player1);
    std::string prueba = "nombre de prueba";
    MatchResponse partida(0, 2, 0, ball, players, 0, 0, prueba, true, false, true, false, false);
    Response r(partida);
    r.addLobbyResponse(lobbyResponse);
    std::vector<unsigned char> serializacion = r.serialize();

    Response deserializada(serializacion);

    EXPECT_EQ(r.serialize().size(), deserializada.serialize().size());
}

TEST(Serializacion, SerializarBoolYFloat) {
    Serializer serializer;
    bool testBool = false;
    bool testBool1 = true;
    float testFloat = 0.5f;
    float testFloat1 = 1.323f;
    int testInt = 32;
    int testInt1 = 32121;
    std::string testString = "asdasasd";

    std::vector<unsigned char> serializacion;
    serializer.merge(serializacion, serializer.serializeBool(testBool));
    serializer.merge(serializacion, serializer.serializeFloat(testFloat1));
    serializer.merge(serializacion, serializer.serializeBool(testBool1));
    serializer.merge(serializacion, serializer.serializeFloat(testFloat));
    serializer.merge(serializacion, serializer.serializeInt(testInt));
    serializer.merge(serializacion, serializer.serializeInt(testInt1));
    serializer.merge(serializacion, serializer.serializeString(testString));

    bool resultBool = true;
    bool resultBool1 = true;
    float resultFloat = 0;
    float resultFloat1 = 0;
    std::string resultString;
    int resultInt = 0;
    int resultInt1 = 0;

    int begin = 0;
    int end = 0;

    serializer.parse(resultBool, serializacion, begin, end);
    serializer.parse(resultFloat1, serializacion, begin, end);
    serializer.parse(resultBool1, serializacion, begin, end);
    serializer.parse(resultFloat, serializacion, begin, end);
    serializer.parse(resultInt, serializacion, begin, end);
    serializer.parse(resultInt1, serializacion, begin, end);
    serializer.parse(resultString, serializacion, begin, end);

    EXPECT_EQ(testFloat, resultFloat);
    EXPECT_EQ(testFloat1, resultFloat1);
    EXPECT_EQ(testBool, resultBool);
    EXPECT_EQ(testBool1, resultBool1);
    EXPECT_EQ(testInt, resultInt);
    EXPECT_EQ(testInt1, resultInt1);
    EXPECT_EQ(testString, resultString);
}