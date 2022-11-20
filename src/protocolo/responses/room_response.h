#ifndef ROOM_RESPONSE_H
#define ROOM_RESPONSE_H

#include <string>
#include <vector>
#include "connected_clients.h"

class RoomResponse {
private:
    ConnectedClients clients;
    std::string name;
    int requiredPlayers;
    int currentPlayers;
    bool waitingPlayers;
    bool isStarted;
    bool isFinished;

public:
    RoomResponse(std::string &name,
                 int requiredPlayers,
                 int currentPlayers,
                 bool waitingPlayers,
                 bool isStarted,
                 bool isFinished);

    explicit RoomResponse(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();
    void addClient(int id);
    std::string getName() { return this->name; };
    int getCurrentPlayers() { return this->currentPlayers; };
    bool getWaitingForPlayers() { return this->waitingPlayers; };

};


#endif // ROOM_RESPONSE_H
