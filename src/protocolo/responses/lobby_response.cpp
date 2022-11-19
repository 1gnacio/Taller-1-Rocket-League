#include "lobby_response.h"
#include "../serializer/serializer.h"

LobbyResponse::LobbyResponse(std::vector<unsigned char> &serialized) : rooms(serialized) {

}

std::vector<unsigned char> LobbyResponse::serialize() {
    return this->rooms.serialize();
}

LobbyResponse::LobbyResponse() : rooms() {}

void LobbyResponse::addRoom(RoomResponse &room) {
    this->rooms.addRoom(room);
}
