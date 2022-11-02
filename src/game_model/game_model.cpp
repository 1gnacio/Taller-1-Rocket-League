#include <algorithm>
#include "game_model.h"

std::vector<std::string> GameModel::listRooms() {
    std::vector<std::string> roomsSerialized;

    std::transform(
            this->rooms.begin(),
            this->rooms.end(),
            std::back_inserter(roomsSerialized),
            [](const Room& room){ return room.serialize(); });

    return roomsSerialized;
}

std::string GameModel::createRoom(const char* name, uint8_t requiredPlayers) {
    bool roomExists =
            this->rooms.find(Room(0, name)) != this->rooms.end();

    if (!roomExists) {
        this->rooms.emplace(requiredPlayers, name);

        return "OK";
    }

    return "ERROR";
}

std::string GameModel::joinRoom(const char* name) {
    auto room =
            this->rooms.find(Room(0, name));

    if (room != this->rooms.end()) {
        return room->joinPlayer();
    }

    return "ERROR";
}
