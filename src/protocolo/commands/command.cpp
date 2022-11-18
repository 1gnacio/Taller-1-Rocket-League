#include "command.h"
#include "../protocol_commands.h"

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter) :
                 id(id),
        serialized(serialized),
        deserialized(deserialized),
        firstParameter(firstParameter) {}

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized) :
                 id(id),
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(),
                 secondParameter() {}

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter,
                 const std::string &secondParameter) :
                 id(id),
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(firstParameter),
                 secondParameter(secondParameter) {}

std::vector<unsigned char> Command::serialize() {
    std::vector<unsigned char> serialized;
    serialized.push_back(this->serialized);

    this->serializer.merge(serialized, this->serializer.serializeInt(this->id));
    this->serializer.merge(serialized, this->serializer.serializeString(this->firstParameter));
    this->serializer.merge(serialized, this->serializer.serializeString(this->secondParameter));

    return serialized;
}

Command::Command(Command &&other) noexcept {
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;
    this->id = other.id;
}

Command &Command::operator=(Command &&other) noexcept {
    if (this == &other)
        return *this;

    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;
    this->id = other.id;

    return *this;
}

Command::Command(std::vector<unsigned char> &serialized) : serializer() {
    this->serialized = serialized.front();
    this->deserialized = ProtocolCommands().getDeserializedCommandValue(this->serialized);

    std::vector<unsigned char> serializedParameters(serialized.begin() + 1, serialized.end());

    int begin = 0;
    int end = 0;

    this->serializer.parse(this->id, serializedParameters, begin, end);
    this->serializer.parse(this->firstParameter, serializedParameters, begin, end);
    this->serializer.parse(this->secondParameter, serializedParameters, begin, end);

}
