#include <algorithm>
#include "game_model.h"
#include "../constants/response_values.h"

RoomResponses GameModel::listRooms() {
    RoomResponses responses;

    for (auto& room : this->rooms) {
        RoomResponse r = room.list();
        responses.addRoom(r);
    }

    return responses;
}

ActionResultResponse GameModel::createRoom(int ownerId, const char* name, int requiredPlayers) {
    std::string roomName = name;
    bool roomExists = std::find_if(this->rooms.begin(),
                                   this->rooms.end(),
                                   [&roomName](const Room& room)
                                   {return room.getName() == roomName;}) != this->rooms.end();

    if (!roomExists) {
        this->rooms.emplace_back(ownerId, requiredPlayers, name);

        return {ownerId, ResponseValues().OK};
    }

    return {ownerId, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_EXISTS};
}

ActionResultResponse GameModel::joinRoom(int playerId, const char* name) {
    std::string roomName = name;
    auto room = std::find_if(this->rooms.begin(),
                                   this->rooms.end(),
                                   [&roomName](const Room& room)
                                   {return room.getName() == roomName;});

    if (room != this->rooms.end()) {
        return room->joinPlayer(playerId);
    }

    return {playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND};
}

ActionResultResponse GameModel::leaveRoom(int playerId, const char *name) {
    std::string roomName = name;
    auto room = std::find_if(this->rooms.begin(),
                             this->rooms.end(),
                             [&roomName](const Room& room)
                             {return room.getName() == roomName;});

    if (room != this->rooms.end()) {
        return room->leaveRoom(playerId);
    }

    return {playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND};
}
