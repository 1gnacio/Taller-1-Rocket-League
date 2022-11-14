#include "entity_serializer.h"

void EntitySerializer::parse(BallResponse &response, int size, std::vector<unsigned char> &serialization, int &beginPosition,
                       int &endPosition) {
    bool isFirstPosition = endPosition == 0;
    beginPosition = (endPosition + (isFirstPosition ? 0 : 1));
    endPosition += (size - (isFirstPosition ? 1 : 0));
    std::vector<unsigned char> serializedResponse(serialization.begin() + beginPosition, serialization.begin() + endPosition + 1);
    response = std::move(BallResponse(serializedResponse));
}

void EntitySerializer::parse(PlayerResponses &responses, int size, std::vector<unsigned char> &serialization, int &beginPosition,
                       int &endPosition) {
    bool isFirstPosition = endPosition == 0;
    beginPosition = (endPosition + (isFirstPosition ? 0 : 1));
    endPosition += (size - (isFirstPosition ? 1 : 0));
    std::vector<unsigned char> serializedResponse(serialization.begin() + beginPosition, serialization.begin() + endPosition + 1);
    responses = std::move(PlayerResponses(serializedResponse));
}