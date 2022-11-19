#include "ball_response.h"

std::vector<unsigned char> BallResponse::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeFloat(posX));
    this->serializer.merge(serialization, this->serializer.serializeFloat(posY));
    this->serializer.merge(serialization, this->serializer.serializeFloat(rotationAngle));
    this->serializer.merge(serialization, this->serializer.serializeBool(isMoving));
    this->serializer.merge(serialization, this->serializer.serializeBool(isFlying));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunched));

    return serialization;
}

BallResponse::BallResponse(std::vector<unsigned char> serialized) : serializer() {
    int firstPosition = 0;
    int lastPosition = 0;

    this->serializer.parse(posX, serialized, firstPosition, lastPosition);
    this->serializer.parse(posY, serialized, firstPosition, lastPosition);
    this->serializer.parse(rotationAngle, serialized, firstPosition, lastPosition);
    this->serializer.parse(isMoving, serialized, firstPosition, lastPosition);
    this->serializer.parse(isFlying, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasBeenPunched, serialized, firstPosition, lastPosition);
}

BallResponse::BallResponse(float posX, float posY, float rotationAngle, bool isMoving, bool isFlying,
                           bool hasBeenPunched) : serializer(), posX(posX), posY(posY), rotationAngle(rotationAngle),
                           isMoving(isMoving), isFlying(isFlying), hasBeenPunched(hasBeenPunched) {}

int BallResponse::size() {
    return sizeof(BallResponse::posX)
    + sizeof(BallResponse::posY)
    + sizeof(BallResponse::rotationAngle)
    + 1 // isMoving
    + 1 // isFlying
    + 1 // hasBeenPunched
    ;
}

BallResponse::BallResponse() = default;