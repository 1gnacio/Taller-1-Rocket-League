#ifndef LOBBY_RESPONSE_H
#define LOBBY_RESPONSE_H

#include <vector>
#include <string>
#include "room_response.h"
#include "room_responses.h"
#include "action_result_response.h"

class LobbyResponse {
private:
    RoomResponses rooms;
    ActionResultResponse actionResult;
    bool dummy = false;
public:
    LobbyResponse();
    LobbyResponse(bool dummy);
    explicit LobbyResponse(RoomResponses &rooms);
    explicit LobbyResponse(ActionResultResponse &actionResult);
    LobbyResponse(RoomResponses &rooms, ActionResultResponse &result);
    void addRoom(RoomResponse &room);
    explicit LobbyResponse(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();
    std::string getStatus() { return actionResult.getStatus(); };
    std::string getMessage() { return actionResult.getMessage(); };
    std::vector<RoomResponse> roomResponses();
    bool isDummy() const {return this->dummy; };
    int getActionId();
};


#endif // LOBBY_RESPONSE_H
