#ifndef ROOM_RESPONSES_H
#define ROOM_RESPONSES_H

#include "room_response.h"

class RoomResponses {
private:
    std::vector<RoomResponse> rooms;
public:
    RoomResponses();
    void addRoom(RoomResponse &room);
    explicit RoomResponses(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();
};


#endif // ROOM_RESPONSES_H
