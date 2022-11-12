#include <algorithm>
#include "player_response.h"

PlayerResponse::PlayerResponse(int id, float posX, float posY, float rotationAngle,
                               bool isMoving, bool isFlying, bool isTurboActivated,
                               bool hasPunchedTheBall, bool isAccelerating, bool isLocalTeam)
                               : serializer(), id(id), posX(posX), posY(posY), rotationAngle(rotationAngle),
                                 isMoving(isMoving), isFlying(isFlying), isTurboActivated(isTurboActivated),
                                 hasPunchedTheBall(hasPunchedTheBall), isAccelerating(isAccelerating),
                                 isLocalTeam(isLocalTeam) {}

PlayerResponse::PlayerResponse(std::vector<unsigned char> &serialized) : serializer() {
    int firstPosition = 0;
    int lastPosition = 0;

    this->serializer.parse(id, serialized, firstPosition, lastPosition);
    this->serializer.parse(posX, serialized, firstPosition, lastPosition);
    this->serializer.parse(posY, serialized, firstPosition, lastPosition);
    this->serializer.parse(rotationAngle, serialized, firstPosition, lastPosition);
    this->serializer.parse(isMoving, serialized, firstPosition, lastPosition);
    this->serializer.parse(isFlying, serialized, firstPosition, lastPosition);
    this->serializer.parse(isTurboActivated, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasPunchedTheBall, serialized, firstPosition, lastPosition);
    this->serializer.parse(isAccelerating, serialized, firstPosition, lastPosition);
    this->serializer.parse(isLocalTeam, serialized, firstPosition, lastPosition);
}

std::vector<unsigned char> PlayerResponse::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeInt(id));
    this->serializer.merge(serialization, this->serializer.serializeFloat(posX));
    this->serializer.merge(serialization, this->serializer.serializeFloat(posY));
    this->serializer.merge(serialization, this->serializer.serializeFloat(rotationAngle));
    this->serializer.merge(serialization, this->serializer.serializeBool(isMoving));
    this->serializer.merge(serialization, this->serializer.serializeBool(isFlying));
    this->serializer.merge(serialization, this->serializer.serializeBool(isTurboActivated));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasPunchedTheBall));
    this->serializer.merge(serialization, this->serializer.serializeBool(isAccelerating));
    this->serializer.merge(serialization, this->serializer.serializeBool(isLocalTeam));

    return serialization;
}