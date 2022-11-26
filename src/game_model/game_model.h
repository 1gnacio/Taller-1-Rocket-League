#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <set>
#include <string>
#include "../game_entities/room.h"
#include "../src/protocolo/responses/room_responses.h"
#include "../src/protocolo/responses/action_result_response.h"
#include "completeGame.h"
#include "../src/handlers/server_endpoint.h"

class GameModel {
 private:
    std::vector<std::unique_ptr<CompleteGame>> games;
    ServerEndpoint & serverEndpoint;
    CommandValues commands;
    LobbyResponse listRooms(int playerId);

    LobbyResponse joinRoom(int playerId, const char* name);

    LobbyResponse leaveRoom(int playerId, const char* name);

    LobbyResponse createRoom(int ownerId, const char* name, int requiredPlayers);
 public:
    GameModel(ServerEndpoint& serverEndpoint);

    std::unique_ptr<CompleteGame>* findGame(const char *name);

    void applyCommandToGame(Command &command);

    std::unique_ptr<CompleteGame> *findGame(int id);


    int gamesAmount();

    std::vector<Response> getResponse();

    void updateTime();

    void resetDataOfGames();

    void applyLogic(Command& command);
};


#endif // GAME_MODEL_H
