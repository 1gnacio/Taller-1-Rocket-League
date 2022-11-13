#include "command.h"
#include "../serializer/serializer.h"

Command::Command(const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter) :
        serialized(serialized),
        deserialized(deserialized),
        firstParameter(firstParameter) {}

Command::Command(const unsigned char serialized,
                 const std::string &deserialized) :
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(),
                 secondParameter() {}

Command::Command(const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter,
                 const std::string &secondParameter) :
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(firstParameter),
                 secondParameter(secondParameter) {}

std::vector<unsigned char> Command::serialize() {
    Serializer serializer;
    std::vector<unsigned char> result;
    std::vector<unsigned char> serializedCommand;
    std::vector<unsigned char> serializedFirstParameter;
    std::vector<unsigned char> serializedSecondParameter;
    int size = 0;

    serializedCommand.push_back(this->serialized);
    size += serializedCommand.size();

    if (!this->firstParameter.empty()) {
        serializer.merge(serializedFirstParameter, serializer.serializeString(this->firstParameter));
        size += serializedFirstParameter.size();
        serializer.merge(serializedCommand, serializedFirstParameter);
    }

    if (!this->secondParameter.empty()) {
        serializer.merge(serializedSecondParameter, serializer.serializeString(this->secondParameter));
        size += serializedSecondParameter.size();
        serializer.merge(serializedCommand, serializedSecondParameter);
    }

    serializer.merge(result, serializer.serializeInt(size));
    serializer.merge(result, serializedCommand);

    return result;
}

Command::Command(Command &&other) noexcept {
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;
}

Command &Command::operator=(Command &&other) noexcept {
    if (this == &other)
        return *this;

    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;

    return *this;
}

Command::Command(std::vector<unsigned char> serialized) {
    // TODO
}
