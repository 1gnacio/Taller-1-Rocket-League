#ifndef ENTITY_SERIALIZER_H
#define ENTITY_SERIALIZER_H

#include "../responses/ball_response.h"
#include "../responses/player_responses.h"

class EntitySerializer {
public:
    void parse(BallResponse &response, int size, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(PlayerResponses &playerResponses, int size, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
};


#endif // ENTITY_SERIALIZER_H
