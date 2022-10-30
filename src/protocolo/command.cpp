#include "command.h"

Command::Command(const char serialized, const std::string &deserialized)
: serialized(serialized), deserialized(deserialized) {}

Command::Command(const char serialized, const std::string &deserialized, const std::string &parameters)
: serialized(serialized), deserialized(deserialized), parameters(parameters) {}

// por el momento serializar solo aplica a movimientos, donde la serializacion es el propio comando
char Command::serialize() {
    return this->serialized;
}

Command::Command(Command &&other) {
    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->parameters = other.parameters;
}

Command &Command::operator=(Command &&other) {
    if (this == &other)
        return *this;

    this->serialized = other.serialized;
    this->deserialized = other.deserialized;
    this->parameters = other.parameters;

    return *this;
}