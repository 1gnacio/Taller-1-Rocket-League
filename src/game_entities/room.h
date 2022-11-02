#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "../common_src/response.h"

class Room {
 private:
    mutable uint8_t currentPlayers;
    uint8_t requiredPlayers;
    std::string name;
 public:
    Room(uint8_t requiredPlayers, const char *name);
    std::string joinPlayer() const;
    std::string serialize() const;

    bool operator<(const Room &room) const;
    bool operator()(const Room& room) const;

    // hago las salas de las partidas no copiables
    Room(const Room&) = delete;
    Room& operator=(const Room&) = delete;
};


#endif // ROOM_H
