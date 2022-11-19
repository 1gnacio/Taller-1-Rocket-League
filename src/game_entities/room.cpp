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
    isWaiting = players.size() < requiredPlayers;
    isStarted = players.size() == requiredPlayers;
    if (isStarted) {
        std::cout << "Comenzando partida " + this->name + "..." << std::endl;
    }
}

ActionResultResponse Room::joinPlayer(int id) {
    if (std::find(this->players.begin(), this->players.end(), id) != this->players.end()) {
        return {id, ResponseValues().ERROR, ResponseValues().PLAYER_ALREADY_JOINED};
    }

    if (this->players.size() < this->requiredPlayers) {
        players.push_back(id);
        if (players.size() == this->requiredPlayers) {
            std::cout << "Comenzando partida " + this->name + "..." << std::endl;
            this->isStarted = true;
            this->isWaiting = false;
            this->isFinished = false;
        }
        return {id, ResponseValues().OK};
    }

    return {id, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_FULL};
}

bool Room::operator<(const Room &room) const {
    return (this->name < room.name);
}

bool Room::operator()(Room &room) {
    return this->name == room.name;
}

RoomResponse Room::list() {
    return {this->name,
            this->requiredPlayers,
            static_cast<int>(this->players.size()),
            this->isWaiting,
            this->isStarted,
            this->isFinished};
}

ActionResultResponse Room::leaveRoom(int playerId) {
    if (std::find(this->players.begin(), this->players.end(), playerId) == this->players.end()) {
        return {playerId, ResponseValues().ERROR, ResponseValues().PLAYER_NOT_FOUND};
    }

    auto result = std::remove(this->players.begin(), this->players.end(), playerId);

    return {playerId, ResponseValues().OK};
}
