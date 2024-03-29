#include "lobby_response.h"
#include "../serializer/serializer.h"

LobbyResponse::LobbyResponse(std::vector<unsigned char> &serialized) {
    Serializer serializer;
    int begin = 0;
    int end = 0;
    int roomsSize = 0;
    int actionResultSize = 0;

    serializer.parse(roomsSize, serialized, begin, end);

    std::vector<unsigned char> serializedRooms(serialized.begin() + end,
                                               serialized.begin() + end + roomsSize);

    this->rooms = RoomResponses(serializedRooms);

    begin += roomsSize;
    end += roomsSize;

    serializer.parse(actionResultSize, serialized, begin, end);

    std::vector<unsigned char> serializedActionResult(serialized.begin() + end,
                                                      serialized.begin() + end + actionResultSize);

    this->actionResult = ActionResultResponse(serializedActionResult);
}

std::vector<unsigned char> LobbyResponse::serialize() {
    Serializer serializer;
    std::vector<unsigned char> serialization;
    std::vector<unsigned char> result;

    serializer.merge(serialization, this->rooms.serialize());
    serializer.merge(serialization, this->actionResult.serialize());

    serializer.merge(result, serializer.serializeInt(serialization.size()));
    serializer.merge(result, serialization);

    return result;
}

LobbyResponse::LobbyResponse() : rooms() {}

void LobbyResponse::addRoom(RoomResponse &room) {
    this->rooms.addRoom(room);
}

LobbyResponse::LobbyResponse(RoomResponses &rooms) : rooms(std::move(rooms)), actionResult() {}

LobbyResponse::LobbyResponse(RoomResponses &rooms, ActionResultResponse &result)
: rooms(rooms), actionResult(result) {}

LobbyResponse::LobbyResponse(ActionResultResponse &actionResult) : rooms(), actionResult(actionResult) {}

bool LobbyResponse::isRecipient(int i) {
    return (this->actionResult.getId() == i);

}

std::vector<RoomResponse> LobbyResponse::getRooms() {
    return this->rooms.getRooms();
}
