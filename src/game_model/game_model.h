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
    std::vector<std::thread> gamesThread;
    ServerEndpoint & serverEndpoint;
    CommandValues commands;
    LobbyResponse listRooms(int playerId);

    LobbyResponse joinRoom(int playerId, const char* name);

    LobbyResponse leaveRoom(int playerId, const char* name);

    LobbyResponse createRoom(int ownerId, const char* name, int requiredPlayers);

    void applyCommand(Command& command);

    bool gameExists(const char* name);
 public:
    explicit GameModel(ServerEndpoint& serverEndpoint);

    void applyCommandToGame(Command &command);

    int gamesAmount();

    std::vector<Response> getResponse();

    void updateTime();

    void resetDataOfGames();

    void applyLogic(Command& command);

    std::thread initGame(std::unique_ptr<CompleteGame> *completeGame);

    void gameFlow(std::unique_ptr<CompleteGame> *completeGame);
    ~GameModel();
};


#endif // GAME_MODEL_H
