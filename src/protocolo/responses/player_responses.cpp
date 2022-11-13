#include "player_responses.h"

PlayerResponses::PlayerResponses(std::vector<PlayerResponse> &players) :
serializer(), players(players), count(players.size()) {}

PlayerResponses::PlayerResponses(std::vector<unsigned char> serialized) : serializer() {
    std::vector<unsigned char> serializedCount(serialized.begin(), serialized.begin() + 3);
    this->count = this->serializer.deserializeInt(serializedCount);

    if (this->count == 0) {
        return;
    }

    std::vector<unsigned char> serializedPlayers(serialized.begin() + 4, serialized.end());
    int playerSize = PlayerResponse::size();

    for (int i = 0; i < this->count; i++) {
        std::vector<unsigned char> serializedPlayer(serialized.begin() + i * playerSize,
                                                    serialized.begin() + (i + 1) * playerSize);

        this->players.emplace_back(serializedPlayer);
    }
}

std::vector<unsigned char> PlayerResponses::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeInt(this->count));

    for(auto& player : players) {
        this->serializer.merge(serialization, player.serialize());
    }

    return serialization;
}

PlayerResponses::PlayerResponses() : serializer(), players(), count(0) {}
