#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include "../src/protocolo/responses/room_response.h"
#include "../src/protocolo/responses/action_result_response.h"

class Room {
 private:
    std::vector<int> players;
    int requiredPlayers;
    std::string name;
    bool isFinished;
    bool isWaiting;
    bool isStarted;

 public:
    Room(int ownerId, int requiredPlayers, const char *name);
    ActionResultResponse joinPlayer(int id);
    RoomResponse list();
    ActionResultResponse leaveRoom(int playerId);

    int playersAmount();
    bool playerInRoom(const int &id);

    bool operator<(const Room &room) const;
    bool operator()(const Room& room);

    std::string getName() const { return this->name; };

    bool isInGame();

    bool hasPlayers();

    bool isWaiting1() const;

    bool isFinished1() const;

    bool isStarted1() const;
};


#endif // ROOM_H
