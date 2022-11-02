#include <iostream>
#include "room.h"

Room::Room(uint8_t requiredPlayers, const char *name)
: currentPlayers(1), requiredPlayers(requiredPlayers), name(name) {}

std::string Room::joinPlayer() const {
    if (this->currentPlayers < this->requiredPlayers) {
        this->currentPlayers++;
        if (this->currentPlayers == this->requiredPlayers) {
            std::cout << "Comenzando partida " + this->name + "..." << std::endl;
        }
        return "OK";
    }

    return "ERROR";
}

bool Room::operator<(const Room &room) const {
    return (this->name < room.name);
}

bool Room::operator()(const Room &room) const {
    return this->name == room.name;
}

std::string Room::serialize() const {
    return std::string(this->name + " " +
                       std::to_string(this->currentPlayers) + "/" +
                       std::to_string(this->requiredPlayers));
}
