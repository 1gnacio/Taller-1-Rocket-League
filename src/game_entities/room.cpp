#include <iostream>
#include <algorithm>
#include "room.h"
#include "../src/protocolo/responses/room_response.h"
#include "../src/protocolo/responses/action_result_response.h"
#include "../src/constants/response_values.h"

Room::Room(int ownerId, int requiredPlayers, const char *name) :
players(),
requiredPlayers(requiredPlayers),
name(name),
isFinished(false) {
    players.push_back(ownerId);
    isWaiting = (int)players.size() < requiredPlayers;
    isStarted = (int)players.size() == requiredPlayers;
    if (isStarted) {
        std::cout << "Comenzando partida " + this->name + "..." << std::endl;
    }
}

ActionResultResponse Room::joinPlayer(int id) {
    if (std::find(this->players.begin(), this->players.end(), id) != this->players.end()) {
        return {id, ResponseValues().ERROR, ResponseValues().PLAYER_ALREADY_JOINED};
    }

    if ((int)this->players.size() < this->requiredPlayers) {
        players.push_back(id);
        if ((int)players.size() == this->requiredPlayers) {
            std::cout << "Comenzando partida " + this->name + "..." << std::endl;
            this->isStarted = true;
            this->isWaiting = false;
            this->isFinished = false;
        }
        return {id, ResponseValues().OK};
    }

    return {id, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_FULL};
}
bool Room::isInGame() {
    return this->isStarted;
}

bool Room::operator<(const Room &room) const {
    return (this->name < room.name);
}

bool Room::operator()(const Room &room) {
    return this->name == room.name;
}

RoomResponse Room::list() {
    RoomResponse r(this->name,
            this->requiredPlayers,
            static_cast<int>(this->players.size()),
            this->isWaiting,
            this->isStarted,
            this->isFinished);

    for (auto &client : this->players) {
        r.addClient(client);
    }

    return r;
}

ActionResultResponse Room::leaveRoom(int playerId) {
    if (std::find(this->players.begin(), this->players.end(), playerId) == this->players.end()) {
        return {playerId, ResponseValues().ERROR, ResponseValues().PLAYER_NOT_FOUND};
    }

    auto result = std::remove(this->players.begin(), this->players.end(), playerId);

    this->players.erase(result, this->players.end());

    return {playerId, ResponseValues().OK};
}

bool Room::playerInRoom(const int &id) {
    bool playerInRoom = false;
    for(auto &x: players) {
        if (x == id) {
            // cppcheck-suppress useStlAlgorithm
            playerInRoom = true;
        }
    }
    return playerInRoom;
}

bool Room::isStarted1() const {
    return isStarted;
}

bool Room::hasPlayers() {
    return !this->players.empty();
}
