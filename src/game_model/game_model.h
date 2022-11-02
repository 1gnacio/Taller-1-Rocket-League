#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include <vector>
#include <set>
#include <string>
#include "../game_entities/room.h"
#include "../common_src/response.h"

class GameModel {
 private:
    std::set<Room> rooms;
 public:
    std::vector<std::string> listRooms();

    std::string joinRoom(const char* name);

    std::string createRoom(const char* name, uint8_t requiredPlayers);
};


#endif // GAME_MODEL_H
