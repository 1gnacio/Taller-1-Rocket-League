#include <iostream>
#include <algorithm>
#include "protocol_commands.h"

ProtocolCommands::ProtocolCommands() : values(),
        serializedCommands({
            {this->values.DESERIALIZED_UP_PUSHED, this->values.SERIALIZED_UP_PUSHED},
            {this->values.DESERIALIZED_UP_RELEASE, this->values.SERIALIZED_UP_RELEASE},
            {this->values.DESERIALIZED_DOWN_PUSHED, this->values.SERIALIZED_DOWN_PUSHED},
            {this->values.DESERIALIZED_DOWN_RELEASE, this->values.SERIALIZED_DOWN_RELEASE},
            {this->values.DESERIALIZED_LEFT_PUSHED, this->values.SERIALIZED_LEFT_PUSHED},
            {this->values.DESERIALIZED_LEFT_RELEASE, this->values.SERIALIZED_LEFT_RELEASE},
            {this->values.DESERIALIZED_RIGHT_PUSHED, this->values.SERIALIZED_RIGHT_PUSHED},
            {this->values.DESERIALIZED_RIGHT_RELEASE, this->values.SERIALIZED_RIGHT_RELEASE}
        }),
        deserializedCommands({
            {this->values.SERIALIZED_UP_PUSHED, this->values.DESERIALIZED_UP_PUSHED},
            {this->values.SERIALIZED_UP_RELEASE, this->values.DESERIALIZED_UP_RELEASE},
            {this->values.SERIALIZED_DOWN_PUSHED, this->values.DESERIALIZED_DOWN_PUSHED},
            {this->values.SERIALIZED_DOWN_RELEASE, this->values.DESERIALIZED_DOWN_RELEASE},
            {this->values.SERIALIZED_LEFT_PUSHED, this->values.DESERIALIZED_LEFT_PUSHED},
            {this->values.SERIALIZED_LEFT_RELEASE, this->values.DESERIALIZED_LEFT_RELEASE},
            {this->values.SERIALIZED_RIGHT_PUSHED, this->values.DESERIALIZED_RIGHT_PUSHED},
            {this->values.SERIALIZED_RIGHT_RELEASE, this->values.DESERIALIZED_RIGHT_RELEASE}
        }) {}

Command ProtocolCommands::createMovementCommand(std::string& value) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return Command(position->second, position->first);
}

Command ProtocolCommands::createMovementCommand(const char value) {
    auto position = this->deserializedCommands.find(value);

    if (position == this->deserializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return Command(position->first, position->second);
}

// en principio las secuencias de comandos solo se reciben mientras el jugador esta en partida
// manipulando el auto
std::vector <Command> ProtocolCommands::createCommandSequence(std::vector <std::string>& receivedInput) {
    std::vector<Command> result;

    if (!receivedInput.empty()) {
        std::transform(receivedInput.begin(),
                       receivedInput.end(),
                       result.begin(),
                       [this] (std::string& command) {
                           return this->createMovementCommand(command);
                       });
    }

    result.emplace_back(this->values.SERIALIZED_NOP, this->values.DESERIALIZED_NOP);

    return result;
}