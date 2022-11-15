#ifndef ENTITY_SERIALIZER_H
#define ENTITY_SERIALIZER_H

#include "../responses/ball_response.h"
#include "../responses/player_response.h"

class EntitySerializer {
public:
    void parse(BallResponse &response, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(PlayerResponse &response, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
};


#endif // ENTITY_SERIALIZER_H
