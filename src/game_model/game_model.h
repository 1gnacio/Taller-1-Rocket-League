#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <set>
#include <string>
#include "../game_entities/room.h"
#include "../src/protocolo/responses/room_responses.h"
#include "../src/protocolo/responses/action_result_response.h"

class GameModel {
 private:
    std::vector<Room> rooms;
 public:
    RoomResponses listRooms();

    ActionResultResponse joinRoom(int playerId, const char* name);

    ActionResultResponse leaveRoom(int playerId, const char* name);

    ActionResultResponse createRoom(int ownerId, const char* name, int requiredPlayers);
};


#endif // GAME_MODEL_H
