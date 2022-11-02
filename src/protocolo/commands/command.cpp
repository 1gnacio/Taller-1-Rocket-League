#include "command.h"

Command::Command(const char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter) :
        serialized(serialized),
        deserialized(deserialized),
        firstParameter(firstParameter) {}

Command::Command(const char serialized,
                 const std::string &deserialized) :
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(),
                 secondParameter() {}

Command::Command(const char serialized,
                 const std::string &deserialized,
                 const std::string &firstParameter,
                 const std::string &secondParameter) :
                 serialized(serialized),
                 deserialized(deserialized),
                 firstParameter(firstParameter),
                 secondParameter(secondParameter) {}

// por el momento serializar solo aplica a movimientos, donde la serializacion es el propio comando
char Command::serialize() {
    return this->serialized;
}

Command::Command(Command &&other) {
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;
}

Command &Command::operator=(Command &&other) {
    if (this == &other)
        return *this;

    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->firstParameter = other.firstParameter;
    this->secondParameter = other.secondParameter;

    return *this;
}