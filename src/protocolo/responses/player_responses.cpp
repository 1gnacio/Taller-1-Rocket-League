#include "player_responses.h"
#include <algorithm>

PlayerResponses::PlayerResponses(std::vector<PlayerResponse> &players) :
serializer(), entitySerializer(), players(players) {}

PlayerResponses::PlayerResponses(std::vector<unsigned char> serialized) : serializer(), entitySerializer() {
    int count = 0;
    int begin = 0;
    int end = 0;

    this->serializer.parse(count, serialized, begin, end);

    for (int i = 0; i < count; i++) {
        int size = PlayerResponse::size();
        std::vector<unsigned char> player(serialized.begin() + end + 1,
                                          serialized.begin() + end + size + 1);
        this->players.emplace_back(player);
        begin += size;
        end += size;
    }
}

std::vector<unsigned char> PlayerResponses::serialize() {
    std::vector<unsigned char> serialization;

    int count = this->players.size();

    this->serializer.merge(serialization, this->serializer.serializeInt(count));

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

bool PlayerResponses::hasPlayer(int i) {

    auto found = std::find_if(this->players.begin(),
                              this->players.end(),
                              [&i](PlayerResponse &player)
                              {return player.getId() == i;});

    return (found != this->players.end());
}
