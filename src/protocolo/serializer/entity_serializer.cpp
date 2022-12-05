#include "entity_serializer.h"

void EntitySerializer::parse(BallResponse &response, std::vector<unsigned char> &serialization, int &beginPosition,
                       int &endPosition) {
    beginPosition = endPosition;
    endPosition += BallResponse::size();
    std::vector<unsigned char> serializedResponse(serialization.begin() + beginPosition, serialization.begin() + endPosition);
    response = BallResponse(serializedResponse);
}

void EntitySerializer::parse(PlayerResponse &response, std::vector<unsigned char> &serialization, int &beginPosition,
                             int &endPosition) {
    beginPosition = endPosition;
    endPosition += PlayerResponse::size();
    std::vector<unsigned char> serializedResponse(serialization.begin() + beginPosition, serialization.begin() + endPosition);
    response = PlayerResponse(serializedResponse);

}
