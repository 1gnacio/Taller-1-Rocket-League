#ifndef PLAYERRESPONSES_H
#define PLAYERRESPONSES_H

#include <vector>
#include "../serializer/entity_serializer.h"

class PlayerResponses {
private:
    Serializer serializer;
    EntitySerializer entitySerializer;
    std::vector<PlayerResponse> players;
public:
    explicit PlayerResponses(std::vector<PlayerResponse> &players);
    explicit PlayerResponses(std::vector<unsigned char> serialized);
    PlayerResponses();

    void addPlayer(PlayerResponse &player);


    std::vector<unsigned char> serialize();
    [[nodiscard]] int getCount() const { return this->players.size(); };
    [[nodiscard]] int getSize() const { return this->players.size() * PlayerResponse::size(); };
    PlayerResponse getPlayer();
    bool isEmpty() {return this->players.empty();};
};


#endif // PLAYERRESPONSES_H
