#ifndef PLAYERRESPONSES_H
#define PLAYERRESPONSES_H

#include <vector>
#include "player_response.h"
#include "../serializer/serializer.h"

class PlayerResponses {
private:
    Serializer serializer;
    std::vector<PlayerResponse> players;
    int count;
public:
    explicit PlayerResponses(std::vector<PlayerResponse> &players);
    explicit PlayerResponses(std::vector<unsigned char> serialized);
    PlayerResponses();

    std::vector<unsigned char> serialize();
    [[nodiscard]] int getCount() const { return this->count; };
    [[nodiscard]] int getSize() const { return this->count * PlayerResponse::size() + this->count; };
};


#endif // PLAYERRESPONSES_H
