#ifndef LOBBY_RESPONSE_H
#define LOBBY_RESPONSE_H

#include <vector>
#include <string>
#include "room_response.h"
#include "room_responses.h"

class LobbyResponse {
private:
    RoomResponses rooms;
public:
    LobbyResponse();
    void addRoom(RoomResponse &room);
    explicit LobbyResponse(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();
};


#endif // LOBBY_RESPONSE_H
