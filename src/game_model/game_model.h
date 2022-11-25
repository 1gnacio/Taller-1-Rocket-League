#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <set>
#include <string>
#include "../game_entities/room.h"
#include "../src/protocolo/responses/room_responses.h"
#include "../src/protocolo/responses/action_result_response.h"
#include "completeGame.h"

class GameModel {
 private:
    std::vector<std::unique_ptr<CompleteGame>> games;
 public:
    RoomResponses listRooms();

    ActionResultResponse joinRoom(int playerId, const char* name);

    ActionResultResponse leaveRoom(int playerId, const char* name);

    ActionResultResponse createRoom(int ownerId, const char* name, int requiredPlayers);

    std::unique_ptr<CompleteGame>* findGame(const char *name);

    void applyCommandToGame(Command &command);

    std::unique_ptr<CompleteGame> *findGame(int id);


    int gamesAmount();

    std::vector<Response> getResponse();

    void updateTime();

    void resetDataOfGames();
};


#endif // GAME_MODEL_H
