#ifndef ROOM_RESPONSE_H
#define ROOM_RESPONSE_H

#include <string>
#include <vector>

class RoomResponse {
private:
    std::string name;
    int requiredPlayers;
    int currentPlayers;
    bool waitingPlayers;
    bool isStarted;
    bool isFinished;

public:
    std::vector<char> serialize();
};


#endif // ROOM_RESPONSE_H
