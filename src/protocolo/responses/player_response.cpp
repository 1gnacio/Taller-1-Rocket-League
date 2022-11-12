#include <algorithm>
#include "player_response.h"

// serializa en little endian
std::vector<unsigned char> PlayerResponse::serializeInt(int value) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);

    return {bytes, bytes + sizeof(int)};
}

// serializa en little endian
std::vector<unsigned char> PlayerResponse::serializeFloat(float value) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);

    return {bytes, bytes + sizeof(float)};
}

std::vector<unsigned char> PlayerResponse::serializeBool(bool value) {
    return value ? std::vector<unsigned char>{1} : std::vector<unsigned char>{0};
}

float PlayerResponse::deserializeFloat(const std::vector<unsigned char> &serializedFloat) const{
    auto* bytes = const_cast<unsigned char *>(&serializedFloat[0]);    // point to beginning of memory
    auto* result = reinterpret_cast<float*>(bytes);

    return *result;
}

// deserializa en little endian
int PlayerResponse::deserializeInt(const std::vector<unsigned char> &serializedInt) const {
    auto* bytes = const_cast<unsigned char *>(&serializedInt[0]);    // point to beginning of memory
    auto* result = reinterpret_cast<int*>(bytes);

    return *result;
}

bool PlayerResponse::deserializeBool(const std::vector<unsigned char> &serializedBool) const {
    return serializedBool.at(0) == 1;
}

PlayerResponse::PlayerResponse(int id, float posX, float posY, float rotationAngle,
                               bool isMoving, bool isFlying, bool isTurboActivated,
                               bool hasPunchedTheBall, bool isAccelerating, bool isLocalTeam)
                               : id(id), posX(posX), posY(posY), rotationAngle(rotationAngle),
                                 isMoving(isMoving), isFlying(isFlying), isTurboActivated(isTurboActivated),
                                 hasPunchedTheBall(hasPunchedTheBall), isAccelerating(isAccelerating),
                                 isLocalTeam(isLocalTeam) {}

PlayerResponse::PlayerResponse(std::vector<unsigned char> &serialized) {
    int firstPosition = 0;
    int lastPosition = 0;

    this->parse(id, serialized, firstPosition, lastPosition);
    this->parse(posX, serialized, firstPosition, lastPosition);
    this->parse(posY, serialized, firstPosition, lastPosition);
    this->parse(rotationAngle, serialized, firstPosition, lastPosition);
    this->parse(isMoving, serialized, firstPosition, lastPosition);
    this->parse(isFlying, serialized, firstPosition, lastPosition);
    this->parse(isTurboActivated, serialized, firstPosition, lastPosition);
    this->parse(hasPunchedTheBall, serialized, firstPosition, lastPosition);
    this->parse(isAccelerating, serialized, firstPosition, lastPosition);
    this->parse(isLocalTeam, serialized, firstPosition, lastPosition);
}

void PlayerResponse::merge(std::vector<unsigned char> &firstVector, std::vector<unsigned char> lastVector) {
    firstVector.insert(firstVector.end(), lastVector.begin(), lastVector.end());
}

std::vector<unsigned char> PlayerResponse::serialize() {
    std::vector<unsigned char> serialization;

    this->merge(serialization, this->serializeInt(id));
    this->merge(serialization, this->serializeFloat(posX));
    this->merge(serialization, this->serializeFloat(posY));
    this->merge(serialization, this->serializeFloat(rotationAngle));
    this->merge(serialization, this->serializeBool(isMoving));
    this->merge(serialization, this->serializeBool(isFlying));
    this->merge(serialization, this->serializeBool(isTurboActivated));
    this->merge(serialization, this->serializeBool(hasPunchedTheBall));
    this->merge(serialization, this->serializeBool(isAccelerating));
    this->merge(serialization, this->serializeBool(isLocalTeam));

    return serialization;
}

void PlayerResponse::parse(int &integer, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    bool isFirstPosition = endPosition == 0;
    beginPosition = (endPosition + (isFirstPosition ? 0 : 1));
    endPosition += (sizeof(integer) - (isFirstPosition ? 1 : 0));
    std::vector<unsigned char> serializedInt(serialization.begin() + beginPosition, serialization.begin() + endPosition + 1);
    integer = this->deserializeInt(serializedInt);
}

void PlayerResponse::parse(float &decimal, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    bool isFirstPosition = endPosition == 0;
    beginPosition = (endPosition + (isFirstPosition ? 0 : 1));
    endPosition += (sizeof(decimal) - (isFirstPosition ? 1 : 0));
    std::vector<unsigned char> serializedFloat(serialization.begin() + beginPosition, serialization.begin() + endPosition + 1);
    decimal = this->deserializeFloat(serializedFloat);
}

void PlayerResponse::parse(bool &boolean, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    bool isFirstPosition = endPosition == 0;
    beginPosition = (endPosition + (isFirstPosition ? 0 : 1));
    endPosition += (sizeof(boolean) - (isFirstPosition ? 1 : 0));
    std::vector<unsigned char> serializedBool{serialization.at(beginPosition)};
    boolean = this->deserializeBool(serializedBool);
}
