#include "command.h"
#include "../../constants/serialize_delimeter.h"

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



void Command::insertParameter(std::vector<char> &serialization, std::string &parameter) const {
    serialization.push_back(SerializerDelimeter().SEPARATOR);
    std::vector<char> parameterSerialized(this->firstParameter.begin(), this->firstParameter.end());
    serialization.insert(serialization.end(), parameter.begin(), parameter.end());
}

std::vector<char> Command::serialize() const {
    std::vector<char> result;
    result.push_back(this->serialized);

    if (!this->firstParameter.empty()) {
        std::string parameter = this->firstParameter;
        this->insertParameter(result, parameter);
    }

    if (!this->secondParameter.empty()) {
        std::string parameter = this->secondParameter;
        this->insertParameter(result, parameter);
    }

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
