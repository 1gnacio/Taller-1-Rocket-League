#ifndef SRC_GAME_MODEL_GAME_MODEL_H_
#define SRC_GAME_MODEL_GAME_MODEL_H_

#include <vector>
#include <set>
#include <string>
#include <memory>
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

    std::unique_ptr<CompleteGame>* findGame(const char *name);

    std::vector<Response> getResponse();

    void updateTime();

    void applyLogic(Command& command);

    std::thread initGame(std::unique_ptr<CompleteGame> *completeGame);

    void gameFlow(std::unique_ptr<CompleteGame> *completeGame);
    ~GameModel();
};

#endif  // SRC_GAME_MODEL_GAME_MODEL_H_
