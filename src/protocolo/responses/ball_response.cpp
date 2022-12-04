#include "ball_response.h"

std::vector<unsigned char> BallResponse::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeFloat(posX));
    this->serializer.merge(serialization, this->serializer.serializeFloat(posY));
    this->serializer.merge(serialization, this->serializer.serializeFloat(rotationAngle));
    this->serializer.merge(serialization, this->serializer.serializeBool(isMoving));
    this->serializer.merge(serialization, this->serializer.serializeBool(isFlying));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunchedNormal));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunchedFlipShot));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunchedRedShot));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunchedPurpleShot));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasBeenPunchedGoldShot));

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
    this->serializer.parse(hasBeenPunchedNormal, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasBeenPunchedFlipShot, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasBeenPunchedRedShot, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasBeenPunchedPurpleShot, serialized, firstPosition, lastPosition);
    this->serializer.parse(hasBeenPunchedGoldShot, serialized, firstPosition, lastPosition);
}

BallResponse::BallResponse(float posX, float posY, float rotationAngle, bool isMoving, bool isFlying,
                           bool hasBeenPunchedNormal, bool hasBeenPunchedFlipShot, bool hasBeenPunchedRedShot,
                           bool hasBeenPunchedPurpleShot, bool hasBeenPunchedGoldShot) :
                           serializer(), posX(posX), posY(posY), rotationAngle(rotationAngle),
                           isMoving(isMoving), isFlying(isFlying), hasBeenPunchedNormal(hasBeenPunchedNormal),
                           hasBeenPunchedFlipShot(hasBeenPunchedFlipShot), hasBeenPunchedRedShot(hasBeenPunchedRedShot),
                           hasBeenPunchedPurpleShot(hasBeenPunchedPurpleShot),
                           hasBeenPunchedGoldShot(hasBeenPunchedGoldShot) {}

int BallResponse::size() {
    return sizeof(BallResponse::posX)
    + sizeof(BallResponse::posY)
    + sizeof(BallResponse::rotationAngle)
    + 1 // isMoving
    + 1 // isFlying
    + 1 // hasBeenPunchedNormal
    + 1 // hasBeenPunchedFlipShot
    + 1 // hasBeenPunchedRedShot
    + 1 // hasBeenPunchedPurpleShot
    + 1 // hasBeenPunchedGoldShot
    ;
}

BallResponse::BallResponse() = default;