#include "player_responses.h"

PlayerResponses::PlayerResponses(std::vector<PlayerResponse> &players) :
serializer(), entitySerializer(), players(players) {}

PlayerResponses::PlayerResponses(std::vector<unsigned char> serialized) : serializer(), entitySerializer() {
    int count = 0;
    int begin = 0;
    int end = 0;

    this->serializer.parse(count, serialized, begin, end);

    if (count == 0) {
        return;
    }

    for (int i = 0; i < count; i++) {
        PlayerResponse p;
        this->entitySerializer.parse(p, serialized, begin, end);
        this->players.push_back(std::move(p));
    }
}

std::vector<unsigned char> PlayerResponses::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeInt(this->players.size()));

    for(auto& player : players) {
        this->serializer.merge(serialization, player.serialize());
    }

    return serialization;
}

PlayerResponses::PlayerResponses() : serializer(), players() {}

void PlayerResponses::addPlayer(PlayerResponse &player) {
    this->players.push_back(std::move(player));
}

std::vector<PlayerResponse> PlayerResponses::getPlayers() {
    return players;
}
