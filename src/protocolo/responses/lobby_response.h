#ifndef LOBBY_RESPONSE_H
#define LOBBY_RESPONSE_H

#include <vector>
#include <string>
#include "room_response.h"

class LobbyResponse {
private:
    std::vector<RoomResponse> rooms;
public:
    std::vector<char> serialize();
};


#endif // LOBBY_RESPONSE_H
