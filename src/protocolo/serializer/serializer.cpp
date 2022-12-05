#include "serializer.h"

// serializa en little endian
std::vector<unsigned char> Serializer::serializeInt(int value) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);

    return {bytes, bytes + sizeof(int)};
}

// serializa en little endian
std::vector<unsigned char> Serializer::serializeFloat(float value) {
    const auto* bytes = reinterpret_cast<const unsigned char*>(&value);

    return {bytes, bytes + sizeof(float)};
}

std::vector<unsigned char> Serializer::serializeBool(bool value) {
    return value ? std::vector<unsigned char>{1} : std::vector<unsigned char>{0};
}

float Serializer::deserializeFloat(const std::vector<unsigned char> &serializedFloat) const{
    auto* bytes = const_cast<unsigned char *>(&serializedFloat[0]);    // point to beginning of memory
    auto* result = reinterpret_cast<float*>(bytes);

    return *result;
}

// deserializa en little endian
int Serializer::deserializeInt(const std::vector<unsigned char> &serializedInt) const {
    auto* bytes = const_cast<unsigned char *>(&serializedInt[0]);    // point to beginning of memory
    auto* result = reinterpret_cast<int*>(bytes);

    return *result;
}

bool Serializer::deserializeBool(const std::vector<unsigned char> &serializedBool) const {
    return serializedBool.at(0) == 1;
}

void Serializer::parse(int &integer, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    beginPosition = endPosition;
    endPosition += sizeof(integer);
    std::vector<unsigned char> serializedInt(serialization.begin() + beginPosition, serialization.begin() + endPosition);
    integer = this->deserializeInt(serializedInt);
}

void Serializer::parse(float &decimal, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    beginPosition = endPosition;
    endPosition += sizeof(decimal);
    std::vector<unsigned char> serializedFloat(serialization.begin() + beginPosition, serialization.begin() + endPosition);
    decimal = this->deserializeFloat(serializedFloat);
}

void Serializer::parse(bool &boolean, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition) {
    beginPosition = endPosition;
    std::vector<unsigned char> serializedBool{serialization.at(endPosition)};
    boolean = this->deserializeBool(serializedBool);
    beginPosition += 1;
    endPosition += 1;
}

void Serializer::merge(std::vector<unsigned char> &firstVector, std::vector<unsigned char> lastVector) {
    firstVector.insert(firstVector.end(), lastVector.begin(), lastVector.end());
}

void Serializer::parse(std::string &string, std::vector<unsigned char> &serialization, int &beginPosition,
                       int &endPosition) {
    int size = 0;
    this->parse(size, serialization, beginPosition, endPosition);
    beginPosition = endPosition;
    endPosition += size;
    std::vector<unsigned char> serializedString(serialization.begin() + beginPosition,
                                                serialization.begin() + endPosition);
    string = std::string(serializedString.begin(), serializedString.end());
}

std::vector<unsigned char> Serializer::serializeString(std::string &value) {
    std::vector<unsigned char> serialization;

    this->merge(serialization, this->serializeInt(value.size()));
    if(value.size() == 0) {
        return serialization;
    }

    this->merge(serialization, std::vector<unsigned char>(value.begin(), value.end()));

    return serialization;
}

std::string Serializer::deserializeString(const std::vector<unsigned char> &serializedString) const {
    std::vector<unsigned char> serializedSize(serializedString.begin(), serializedString.begin() + 4);
    int size = this->deserializeInt(serializedSize);

    if(size == 0) {
        return std::string();
    }

    return std::string(serializedString.begin() + 4, serializedString.begin() + 4 + size);
}
