#include "command.h"
#include "../protocol_commands.h"

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter) :
                 id(id),
        deserialized(deserialized),
        firstParameter(firstParameter) {}

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized) :
                 id(id),
                 deserialized(deserialized),
                 firstParameter(),
                 secondParameter() {}

Command::Command(int id, const unsigned char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter,
                 const std::string &secondParameter) :
                 id(id),
                 deserialized(deserialized),
                 firstParameter(firstParameter),
                 secondParameter(secondParameter) {}

std::vector<unsigned char> Command::serialize() {
    Serializer serializer;
    std::vector<unsigned char> serialized;
    serialized.push_back(this->serialized);

    serializer.merge(serialized, serializer.serializeInt(this->id));
    serializer.merge(serialized, serializer.serializeString(this->firstParameter));
    serializer.merge(serialized, serializer.serializeString(this->secondParameter));

    return serialized;
}

Command::Command(Command &&other) noexcept {
    this->id = other.id;
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;
}

Command &Command::operator=(Command &&other) noexcept {
    if (this == &other)
        return *this;

    this->id = other.id;
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;

    return *this;
}

Command::Command(std::vector<unsigned char> &serialized) {
    Serializer serializer;
    this->serialized = serialized.front();
    this->deserialized = ProtocolCommands().getDeserializedCommandValue(this->serialized);

    std::vector<unsigned char> serializedParameters(serialized.begin() + 1, serialized.end());

    int begin = 0;
    int end = 0;

    serializer.parse(this->id, serializedParameters, begin, end);
    serializer.parse(this->firstParameter, serializedParameters, begin, end);
    serializer.parse(this->secondParameter, serializedParameters, begin, end);

}
